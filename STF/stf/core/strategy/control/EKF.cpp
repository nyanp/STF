/**
 * @file   EKF.cpp
 * @brief  ジャイロバイアス推定を行う拡張カルマンフィルタ制御ブロック．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "EKF.h"
#include "../../../util/math.h"
#include "../../../util/math/Exp.h"
#include "../../../util/math/RungeKutta.h"
#include "../../../util/Trace.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {

EKF::EKF(int instance_id, const EKFParameters &params) : StrategyBase(instance_id, "EKF")
{	
    this->params_ = params;//copy
    init();   
}

EKF::EKF(int instance_id, const EKFParameters &params, 
		devicedriver::OutputPort<datatype::Quaternion>* q_source, OutputPort<datatype::StaticVector<3>>* omega_source,
		devicedriver::InputPort<datatype::Quaternion>* q_out, InputPort<datatype::StaticVector<3>>* omega_out
		) : StrategyBase(instance_id, "EKF")
{
    this->params_ = params;//copy
	this->connect_source<0>(q_source);
	this->connect_source<1>(omega_source);
	if(q_out != 0){
		q_out->connect_source_(this);
	}
	if(omega_out != 0){
		omega_out->connect_source_(this);
	}
    init();  
}

EKF::EKF(int instance_id) : StrategyBase(instance_id, "EKF")
{
	params_.tau = 1000;
	params_.timestep = 0.1;
	params_.w_b = params_.w_q = 0.01;
	params_.v = 0;
	params_.MinimunGain = 0;
	params_.calcSensorGap = false;
	for(int i = 0; i < 6; i++)
		params_.P0[i][i] = 1.0;
    init();
}


void EKF::init(const EKFParameters &params)
{
    this->params_ = params;//copy
    init();   
}


void EKF::init()
{
	//全ての値を初期化する．コンストラクタから呼ぶほか，大マニューバ後やセンサ異常時のリセットにも使える
    stf_assert(tau_ != 0);

    this->P_ = params_.P0;
    this->q_ = params_.q0;
    this->bref_ = params_.b0;
    this->dt_ = params_.timestep;
    this->tau_ = params_.tau;
    //w, vからQ,Rを生成
    for(int i = 0; i < 3; i++)
	{
        Q_[i][i] = params_.w_q * params_.w_q;
		Q_[i+3][i+3] = params_.w_b * params_.w_b;
        R_[i][i] = params_.v * params_.v;
	}
    //固定値の行列や初期値が必要な行列に値を代入
    //B
    B_[0][0] = B_[1][1] = B_[2][2] = -0.5;
    B_[3][3] = B_[4][4] = B_[5][5] = 1;
    //H 計算負荷削減のため，転置行列も持っておく
    H_[0][0] = H_[1][1] = H_[2][2] = 1;
	Ht_[0][0] = Ht_[1][1] = Ht_[2][2] = 1;
    //A(時変であるΩ以外を初期化しておく)
    A_[0][3] = A_[1][4] = A_[2][5] = -0.5;
    A_[3][3] = A_[4][4] = A_[5][5] = -1 / this->tau_;
    //F
    F_ = util::math::exp(A_ * dt_, 4);
}


void EKF::do_compute(const datatype::Time& t)
{
	if(this->getLastOutputtime<1>() >= t) return; //伝搬済みなので何もしない

	util::Trace trace(util::Trace::kControlBlock, name_);

	if(this->getLastOutputtime<0>() < t && this->get_lastinput<0>() >= this->getLastOutputtime<0>()){
		update_( this->source<0, datatype::Quaternion>().get_value(t), t );
		//util::cout << "update:" << util::endl;
	}
	//util::cout << "propagate:" << util::endl;
	propagate_( this->source<1, datatype::StaticVector<3>>().get_value(t), t );

}


void EKF::update_(const datatype::Quaternion &input, const datatype::Time& t)
{
    q_.normalize();
    //カルマンゲインの計算
    this->K_ = P_ * Ht_ * ( H_ * P_ * Ht_ + R_ ).inverse();
    //共分散行列の更新
    P_ = P_ - K_ * H_ * P_;
    //観測量微小量yの計算．観測されたqにモデルから伝搬したqrefの共役を左から掛ける
    datatype::StaticVector<3> y;
    datatype::Quaternion q_tmp = q_.conjugate() * input;

    //q_tmp[0](～1)を省略した3要素で状態量を構成
    y[0] = q_tmp[1];
    y[1] = q_tmp[2];
    y[2] = q_tmp[3];
    //xの推定値を更新
    x_ = K_ * y;
    //基準状態量の更新
    datatype::Quaternion q_update;
    q_update[0] = 1 - x_[0] * x_[0] - x_[1] * x_[1] - x_[2] * x_[2];
    q_update[1] = x_[0];
    q_update[2] = x_[1];
    q_update[3] = x_[2];
    q_update.normalize();

    q_ = q_ * q_update;
    q_.normalize();//更新のタイミングで正規化もしておく(TBD)

    bref_[0] += x_[3];
    bref_[1] += x_[4];
    bref_[2] += x_[5];

	this->outputport<0, datatype::Quaternion>().value_ = this->q_;
	//this->setLastOutputtime<0>(t);
	this->setLastOutputtime<0>(t);
}


void EKF::propagate_(const datatype::StaticVector<3>& omega, const datatype::Time& t)
{
    //現時点での推定角速度でΩ，Aを更新
    this->omega_[0] = omega[0] - this->bref_[0] ;//- this->x_[3];
    this->omega_[1] = omega[1] - this->bref_[1] ;//- this->x_[4];
    this->omega_[2] = omega[2] - this->bref_[2] ;//- this->x_[5];

    //状態変数の伝搬
    //ファイルスコープのstatic変数Omegaを現在のインスタンスで更新
    Omega_[0][1] = -this->omega_[0];
    Omega_[0][2] = -this->omega_[1];
    Omega_[0][3] = -this->omega_[2];
    Omega_[1][2] =  this->omega_[2];
    Omega_[1][3] = -this->omega_[1];
    Omega_[2][3] =  this->omega_[0];
    for(int i = 0; i < 4; i++)
      for(int j = 0; j < 4; j++)
        if(i > j) Omega_[i][j] = -Omega_[j][i];

    //A, F,Gの更新
    A_[0][1] =  this->omega_[2];
    A_[0][2] = -this->omega_[1];
    A_[1][0] = -this->omega_[2];
    A_[1][2] =  this->omega_[0];
    A_[2][0] =  this->omega_[1];
    A_[2][1] = -this->omega_[0];
    F_ = util::math::exp(A_ * dt_, 3);//TBD:expのマクローリン展開を3次まで取る．t>1のときは粗い近似になってしまう
    G_ = B_ * dt_ + 0.5 * A_ * B_ * dt_ * dt_;//exp(A(t-tau))を3次まで展開して積分

    //RKでq, bの基準値を伝搬(微小状態量は伝搬しない)
    this->q_ += util::math::RungeKutta::slope(q_, 0.5 * Omega_, dt_);
    this->bref_ += util::math::RungeKutta::slope(bref_,-1 / tau_, dt_);

    //共分散行列の伝搬
    this->P_ = F_ * P_ * F_.trans() + G_ * Q_ * G_.trans();

	this->outputport<0, datatype::Quaternion>().value_ = this->q_;
	this->outputport<1, datatype::StaticVector<3>>().value_ = this->omega_;
	this->setLastOutputtime<1>(t);
}


void EKF::reset()
{
	//誤差共分散行列のみ初期化する
	this->P_ = this->params_.P0; 
}

} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */
