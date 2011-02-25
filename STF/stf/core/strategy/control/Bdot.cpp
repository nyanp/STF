/**
 * @file   Bdot.cpp
 * @brief  B-Dot則を計算する制御ブロック．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "Bdot.h"
#include "../../../datatype/Time.h"
#include "../../../util/Trace.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {

Bdot::Bdot(int instance_id,double k, 
		devicedriver::OutputPort<datatype::MagneticField>* mag_source,
		devicedriver::InputPort<datatype::MagneticMoment>* torque_out
		) : StrategyBase(instance_id, "Bdot"), k_(k)
{
	this->connect_source<0>(mag_source);
	if(torque_out != 0){
		torque_out->connect_source_(this);
	}
}

void Bdot::do_compute(const datatype::Time& t) {
	if(t <= this->last_update_) return; //既に別のブロック経由で更新済みなら再計算しない
	util::Trace trace(util::Trace::kControlBlock,name_);
	this->source<0,datatype::MagneticField>().get_value(t);

	for(int i = 0; i < 3; i++){
		this->value_b_[i] = - this->k_ * (this->source<0,datatype::MagneticField>().value_b_[i] - this->mag_before_[i]);
	}
	trace.debug(value_b_);
	this->mag_before_ = this->source<0,datatype::MagneticField>().value_b_;

	this->last_update_ = t;
}

} /* End of namespace core::mode::strategy::input */
} /* End of namespace core::mode::strategy */
} /* End of namespace core::mode */
} /* End of namespace core */
