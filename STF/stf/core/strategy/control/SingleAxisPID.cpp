#include "SingleAxisPID.h"
#include "../../../datatype/TypeConverter.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {


SingleAxisPID::SingleAxisPID(int instance_id, double kp, double ki, double kd, double dt, const datatype::Scalar &target)
	: kp_(kp), kd_(kd), ki_(ki), dt_(dt), target_(target), StrategyBase(instance_id, "SingleAxisPID")
{
}

SingleAxisPID::SingleAxisPID(int instance_id, double kp, double ki, double kd, double dt, const datatype::Scalar &target, 
		devicedriver::OutputPort<datatype::Scalar>* source, 
		devicedriver::InputPort<datatype::Scalar>* out)
	: kp_(kp), kd_(kd), ki_(ki), dt_(dt), target_(target), StrategyBase(instance_id, "SingleAxisPID")
{
	this->connectSource<0>(source);
	out->connectSource_(this);
}

void SingleAxisPID::do_compute(const datatype::Time& t)
{
	assert(this->prevholder_ != 0);//input sourceが無い
	if(t > this->last_update_){//既に別のブロック経由で更新済みなら再計算しない
		util::cout << "compute: SingleAxisPID" << util::endl;
		this->value_b_ = computeTorque_(this->source<0,datatype::Scalar>().getValueInBodyFrame(t));
		this->last_update_ = t;
	}
}


datatype::Scalar SingleAxisPID::computeTorque_(const datatype::Scalar &x)
{
	this->dx_total_ += (x - target_) * this->dt_;

	//オイラー角がZ-Y-X表現なのに対してトルクはX-Y-Zの順．順番に注意
	datatype::Scalar output;	
	output = this->kp_ * (x - target_)
		      + this->kp_ * ( x - x_old_) / this->dt_ 
			  + this->ki_ * dx_total_;

	this->x_old_ = x;

	return output;
}



} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */