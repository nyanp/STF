/**
 * @file   EKF.h
 * @brief  ジャイロバイアス推定を行う拡張カルマンフィルタ制御ブロック．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_control_EKF_h
#define stf_core_strategy_control_EKF_h

#include "../StrategyBase.h"
#include "../../devicedriver/IOPort.h"

#include "../../../datatype/StaticVector.h"
#include "../../../datatype/StaticMatrix.h"
#include "../../../datatype/Quaternion.h"

#include "EKFParameters.h"

namespace stf {
namespace datatype {
class Time;
}
namespace core {
namespace devicedriver {
template<class T, class U, class Env> class AOCSComponent;
}
namespace strategy {
namespace control {

//! ジャイロバイアス推定を行う拡張カルマンフィルタ制御ブロック．
/*! 
	カルマンフィルタの初期パラメータは，EKFParametersによって纏めて与える．ジャイロバイアスはECRVでモデル化されている．
	参考：宇宙科学研究所報告第102号　天文観測用科学衛星の姿勢決定系におけるカルマンフィルタ
	入力:姿勢情報, 角速度
	出力:姿勢情報，角速度（推定値）
*/
class EKF : public StrategyBase,
	public devicedriver::InputPorts< TYPELIST_2( datatype::Quaternion, datatype::StaticVector<3> ) >,
	public devicedriver::OutputPorts< TYPELIST_2( datatype::Quaternion, datatype::StaticVector<3> ) >
{
public:
    EKF(int instance_id, const EKFParameters &params);
	EKF(int instance_id, const EKFParameters &params, 
		OutputPort<datatype::Quaternion>* q_source, OutputPort<datatype::StaticVector<3>>* omega_source,
		InputPort<datatype::Quaternion>* q_out = 0, InputPort<datatype::StaticVector<3>>* omega_out = 0
		);
    EKF(int instance_id);
	virtual ~EKF(){}	
	virtual void init(const EKFParameters &params);//!< 与えられたEKFParametersを用いて推定値と各伝搬行列を全て初期化する．
    virtual void init();  //!< ローカルのparams_を用いて推定値と各伝搬行列を全て初期化する．
	virtual void reset(); //!< 誤差共分散行列を初期化する．
	virtual void do_compute(const datatype::Time& t);//伝搬，更新処理
protected:
    virtual void update_(const datatype::Quaternion &input, const datatype::Time& t);
    virtual void propagate_(const datatype::StaticVector<3>& omega, const datatype::Time& t);
    EKFParameters params_; //!< リセット時のために保存される，各初期値セット
	datatype::StaticVector<3> omega_; //!< 角速度推定値
    datatype::Quaternion q_; //!< オイラーパラメータ推定値
    datatype::StaticVector<3> bref_; //!< ジャイロバイアス推定値
	//伝搬頻度(sec)
	double dt_;
    datatype::StaticMatrix<6, 6> A_;
    datatype::StaticMatrix<6, 6> B_;
    datatype::StaticMatrix<6, 6> G_;
    datatype::StaticMatrix<6, 6> F_;
    datatype::StaticMatrix<3, 6> H_;
    datatype::StaticMatrix<6, 6> P_; //!< 共分散行列
    datatype::StaticMatrix<6, 3> K_; //!< カルマンゲイン
    datatype::StaticMatrix<6, 6> Q_;
    datatype::StaticMatrix<3, 3> R_;
    datatype::StaticVector<6> x_; //!< 状態量ベクトル
    datatype::StaticMatrix<6, 3> Ht_;
    datatype::StaticMatrix<4, 4> Omega_;
    double tau_; //!< ジャイロECRV時定数(s)
};


} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_strategy_control_input_EKF_h
