/**
 * @file   PID.cpp
 * @brief  PID制御を行う制御ブロック群．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "PID.h"
#include "../../../datatype/TypeConverter.h"
#include "../../../datatype/Time.h"
#include "../../../datatype/OrbitCalc.h"
#include "../../../util/Trace.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {


PID::PID(int instance_id, double kp, double ki, double kd, double dt, const datatype::Quaternion &target)
	: kp_(kp), kd_(kd), ki_(ki), dt_(dt), q_target_(target), StrategyBase(instance_id, "PID")
{
}

PID::PID(int instance_id, double kp, double ki, double kd, double dt, const datatype::Quaternion &target, 
		devicedriver::OutputPort<datatype::Quaternion>* q_source, 
		devicedriver::OutputPort<datatype::StaticVector<3>>* omega_source, 
		devicedriver::InputPort<datatype::StaticVector<3>>* torque_out)
	: kp_(kp), kd_(kd), ki_(ki), dt_(dt), q_target_(target), StrategyBase(instance_id, "PID")
{
	if(q_source != 0) this->connect_source<0>(q_source);
	if(omega_source != 0) this->connect_source<1>(omega_source);
	torque_out->connect_source_(this);
}

QuaternionPID::QuaternionPID(int instance_id, double kp, double ki, double kd, double dt, const datatype::Quaternion &target)
 : PID(instance_id,kp,ki,kd,dt,target)
{
}

QuaternionPID::QuaternionPID(int instance_id, double kp, double ki, double kd, double dt, const datatype::Quaternion &target, 
		devicedriver::OutputPort<datatype::Quaternion>* q_source, 
		devicedriver::InputPort<datatype::StaticVector<3>>* torque_out)
		: PID(instance_id,kp,ki,kd,dt,target,q_source,0,torque_out)
{
}

EarthPointingPID::EarthPointingPID(int instance_id, double kp, double ki, double kd, double dt,const datatype::StaticVector<3>& target)
	: kp_(kp), kd_(kd), ki_(ki), dt_(dt), target_earthvector_(target), StrategyBase(instance_id, "EarthPointingPID")
{
}

EarthPointingPID::EarthPointingPID(int instance_id, double kp, double ki, double kd, double dt,const datatype::StaticVector<3>& target,
		devicedriver::OutputPort<datatype::Quaternion>* q_source, 
		devicedriver::OutputPort<datatype::StaticVector<3>>* omega_source, 
		devicedriver::OutputPort<datatype::PositionInfo>* position_source,
		devicedriver::InputPort<datatype::StaticVector<3>>* torque_out)
	: kp_(kp), kd_(kd), ki_(ki), dt_(dt), target_earthvector_(target), StrategyBase(instance_id, "EarthPointingPID")
{
	if(q_source != 0) this->connect_source<0>(q_source);
	if(omega_source != 0) this->connect_source<1>(omega_source);
	if(position_source != 0) this->connect_source<2>(position_source);
	torque_out->connect_source_(this);
}

DynamicPID::DynamicPID(int instance_id, double kp, double ki, double kd, double dt)
	: kp_(kp), kd_(kd), ki_(ki), dt_(dt), StrategyBase(instance_id, "DynamicPID")
{
}

DynamicPID::DynamicPID(int instance_id, double kp, double ki, double kd, double dt,
		devicedriver::OutputPort<datatype::Quaternion>* q_source, 
		devicedriver::OutputPort<datatype::StaticVector<3>>* omega_source, 
		devicedriver::OutputPort<datatype::Quaternion>* reference_source,
		devicedriver::InputPort<datatype::StaticVector<3>>* torque_out)
	: kp_(kp), kd_(kd), ki_(ki), dt_(dt), StrategyBase(instance_id, "DynamicPID")
{
	if(q_source != 0) this->connect_source<0>(q_source);
	if(omega_source != 0) this->connect_source<1>(omega_source);
	if(reference_source != 0) this->connect_source<2>(reference_source);
	torque_out->connect_source_(this);
}


void PID::do_compute(const datatype::Time& t)
{
	if(t > this->last_update_){//既に別のブロック経由で更新済みなら再計算しない
		util::Trace trace(util::Trace::kControlBlock,name_);
		//Quaternion観測値
		datatype::Quaternion q = this->source<0,datatype::Quaternion>().get_in_bodyframe(t);
		datatype::EulerAngle e = datatype::TypeConverter::toEulerAngle(q.conjugate() * this->q_target_);
		datatype::EulerAngle e_diff = this->source<1,datatype::StaticVector<3>>().get_in_bodyframe(t);
		this->e_total_ += e * this->dt_;

		this->value_b_ = compute_torque_(e,e_diff,e_total_);

		this->e_before_ = e;

		this->last_update_ = t;
	}
}

datatype::StaticVector<3> PID::compute_torque_(const datatype::EulerAngle& x, const datatype::EulerAngle& x_delta, const datatype::EulerAngle& x_total)
{
	//オイラー角がZ-Y-X表現なのに対してトルクはX-Y-Zの順．順番に注意
	datatype::StaticVector<3> output;	
	output[2] = this->kp_ * x[0] + this->kd_ * x_delta[0] + this->ki_ * x_total[0];
	output[1] = this->kp_ * x[1] + this->kd_ * x_delta[1] + this->ki_ * x_total[1];
	output[0] = this->kp_ * x[2] + this->kd_ * x_delta[2] + this->ki_ * x_total[2];
	return output;
}

void QuaternionPID::do_compute(const datatype::Time& t)
{
	if(t > this->last_update_){//既に別のブロック経由で更新済みなら再計算しない
		util::Trace trace(util::Trace::kControlBlock,name_);

		//Quaternion観測値
		datatype::Quaternion q = this->source<0,datatype::Quaternion>().get_in_bodyframe(t);
		datatype::EulerAngle e = datatype::TypeConverter::toEulerAngle(q.conjugate() * this->q_target_);
		//角速度センサではなくQの差分で微分値を計算
		datatype::EulerAngle e_diff = (e - this->e_before_) / this->dt_;
		this->e_total_ += e * this->dt_;

		this->value_b_ = compute_torque_(e,e_diff,e_total_);

		this->e_before_ = e;

		this->last_update_ = t;
	}
}

void EarthPointingPID::do_compute(const datatype::Time& t)
{
	if(t > this->last_update_){//既に別のブロック経由で更新済みなら再計算しない
		util::Trace trace(util::Trace::kControlBlock,name_);

		//Quaternion観測値
		datatype::Quaternion q = this->source<0,datatype::Quaternion>().get_in_bodyframe(t);
		this->earthvector_ = datatype::OrbitCalc::getEarthDirection3D(this->source<2,datatype::PositionInfo>().get_in_bodyframe(t));
		datatype::StaticVector<3> v = this->earthvector_ - this->target_earthvector_;
		
		//角速度センサではなくQの差分で微分値を計算
		datatype::EulerAngle e_diff = (v - this->e_before_) / this->dt_;
		this->e_total_ += v * this->dt_;

		this->value_b_[2] = this->kp_ * v[0] + this->kd_ * e_diff[0] + this->ki_ * e_total_[0];
		this->value_b_[1] = this->kp_ * v[1] + this->kd_ * e_diff[1] + this->ki_ * e_total_[1];
		this->value_b_[0] = this->kp_ * v[2] + this->kd_ * e_diff[2] + this->ki_ * e_total_[2];

		this->e_before_ = v;

		this->last_update_ = t;
	}
}


void DynamicPID::do_compute(const datatype::Time& t){
	if(t > this->last_update_){//既に別のブロック経由で更新済みなら再計算しない
		util::Trace trace(util::Trace::kControlBlock,name_);

		//Quaternion観測値
		datatype::Quaternion q = this->source<0,datatype::Quaternion>().get_in_bodyframe(t);
		//Quaternion目標値
		datatype::Quaternion q_target = this->source<2,datatype::Quaternion>().get_in_bodyframe(t);
		//目標までのオイラー角
		datatype::EulerAngle e = datatype::TypeConverter::toEulerAngle( q.conjugate() * q_target );
		
		//角速度センサではなくQの差分で微分値を計算
		datatype::EulerAngle e_diff = (e - this->e_before_) / this->dt_;
		this->e_total_ += e * this->dt_;

		this->value_b_[2] = this->kp_ * e[0] + this->kd_ * e_diff[0] + this->ki_ * e_total_[0];
		this->value_b_[1] = this->kp_ * e[1] + this->kd_ * e_diff[1] + this->ki_ * e_total_[1];
		this->value_b_[0] = this->kp_ * e[2] + this->kd_ * e_diff[2] + this->ki_ * e_total_[2];

		this->e_before_ = e;

		this->last_update_ = t;
	}
}
} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */