/**
 * @file   PID.h
 * @brief  PID制御を行う制御ブロック群．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_control_PID_h
#define stf_core_strategy_control_PID_h
#include "../../../util/stfassert.h"
#include "../../devicedriver/IOPort.h"
#include "../StrategyBase.h"


#include "../../../datatype/StaticVector.h"
#include "../../../datatype/Quaternion.h"
#include "../../../datatype/EulerAngle.h"
#include "../../../datatype/OrbitInfo.h"

namespace stf {
namespace datatype {
class Time;
}
namespace core {
namespace strategy {
namespace control {

//! Quaternionと角速度からフィードバック制御を行う3軸PID制御ブロック．目標Quaternionは慣性系に対して固定
/*! 
	入力:姿勢情報，角速度
	出力:3軸トルク
*/
class PID : public devicedriver::InputPorts< TYPELIST_2(datatype::Quaternion, datatype::StaticVector<3>) >, 
		public devicedriver::OutputPorts < TYPELIST_1(datatype::StaticVector<3>) > ,
		public StrategyBase
{
public:
    PID( double kp, double ki, double kd, double dt, const datatype::Quaternion &target);
	PID( double kp, double ki, double kd, double dt, const datatype::Quaternion &target, 
		devicedriver::OutputPort<datatype::Quaternion>* q_source, 
		devicedriver::OutputPort<datatype::StaticVector<3>>* omega_source, 
		devicedriver::InputPort<datatype::StaticVector<3>>* torque_out);
	~PID(){}
	void setPIDGain(double kp, double ki, double kd){
		kp_ = kp;
		ki_ = ki;
		kd_ = kd;
	}
	virtual void do_compute(const datatype::Time& t);
protected:
	datatype::StaticVector<3> compute_torque_(const datatype::EulerAngle& x, const datatype::EulerAngle& x_delta, const datatype::EulerAngle& x_total);
    double kp_;
    double ki_;
    double kd_;
	double dt_;
    //目標quaternion.
    datatype::Quaternion q_target_;
    //1ステップ前のオイラー角誤差(微分制御に使用)
    datatype::EulerAngle e_before_;
    //姿勢角の誤差積分値（積分制御に使用）．
    datatype::EulerAngle e_total_;
};

//! Quaternionだけからフィードバック制御を行う3軸PID制御ブロック．目標Quaternionは慣性系に対して固定．角速度はQuaternionの差から算出
/*! 
	入力:姿勢情報
	出力:3軸トルク
*/
class QuaternionPID : public PID
{
public:
    QuaternionPID( double kp, double ki, double kd, double dt, const datatype::Quaternion &target);
	QuaternionPID( double kp, double ki, double kd, double dt, const datatype::Quaternion &target, 
		devicedriver::OutputPort<datatype::Quaternion>* q_source, 
		devicedriver::InputPort<datatype::StaticVector<3>>* torque_out);
	~QuaternionPID(){}
	virtual void do_compute(const datatype::Time& t);
private:
};

//! 地球指向のポインティング制御を行う3軸PID制御ブロック．
/*! 
	衛星のどの面を地球に指向するかは，コンストラクタのパラメータで与えられる．
	入力:姿勢情報，角速度，軌道情報
	出力:3軸トルク
*/
class EarthPointingPID : public devicedriver::InputPorts< TYPELIST_3(datatype::Quaternion, datatype::StaticVector<3>, datatype::PositionInfo) >, 
		public devicedriver::OutputPorts < TYPELIST_1(datatype::StaticVector<3>) > ,
		public StrategyBase
{
public:
	EarthPointingPID( double kp, double ki, double kd, double dt, const datatype::StaticVector<3>& target);
	EarthPointingPID( double kp, double ki, double kd, double dt, const datatype::StaticVector<3>& target,
		devicedriver::OutputPort<datatype::Quaternion>* q_source, 
		devicedriver::OutputPort<datatype::StaticVector<3>>* omega_source, 
		devicedriver::OutputPort<datatype::PositionInfo>* position_source,
		devicedriver::InputPort<datatype::StaticVector<3>>* torque_out);

	~EarthPointingPID(){}
	void setPIDGain(double kp, double ki, double kd){
		kp_ = kp;
		ki_ = ki;
		kd_ = kd;
	}
	virtual void do_compute(const datatype::Time& t);
protected:
    double kp_;
    double ki_;
    double kd_;
	double dt_;
	//期待座標系における目標の地球方向ベクトル。
	datatype::StaticVector<3> target_earthvector_;
	//現在の地球方向ベクトル．
	datatype::StaticVector<3> earthvector_;
    //1ステップ前のオイラー角誤差(微分制御に使用)
    datatype::EulerAngle e_before_;
    //姿勢角の誤差積分値（積分制御に使用）．
    datatype::EulerAngle e_total_;
};

//! 目標Quaternionを外部から逐次入力するPID制御ブロック．
/*! 
	慣性座標系での目標が時変である場合（地上の特定地点へのポインティングなど）に使用するPID．
	入力:姿勢情報，角速度，目標姿勢情報
	出力:3軸トルク
*/
class DynamicPID : public devicedriver::InputPorts< TYPELIST_3(datatype::Quaternion, datatype::StaticVector<3>, datatype::Quaternion) >, 
		public devicedriver::OutputPorts < TYPELIST_1(datatype::StaticVector<3>) > ,
		public StrategyBase
{
public:
	DynamicPID( double kp, double ki, double kd, double dt);
	DynamicPID( double kp, double ki, double kd, double dt,
		devicedriver::OutputPort<datatype::Quaternion>* q_source, 
		devicedriver::OutputPort<datatype::StaticVector<3>>* omega_source, 
		devicedriver::OutputPort<datatype::Quaternion>* reference_source,
		devicedriver::InputPort<datatype::StaticVector<3>>* torque_out);

	~DynamicPID(){}
	void setPIDGain(double kp, double ki, double kd){
		kp_ = kp;
		ki_ = ki;
		kd_ = kd;
	}
	virtual void do_compute(const datatype::Time& t);
protected:
    double kp_;
    double ki_;
    double kd_;
	double dt_;
    //1ステップ前のオイラー角誤差(微分制御に使用)
    datatype::EulerAngle e_before_;
    //姿勢角の誤差積分値（積分制御に使用）．
    datatype::EulerAngle e_total_;
};

} /* End of namespace stf::core::mode::strategy::control */
} /* End of namespace stf::core::mode::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_mode_storategy_control_PID_h
