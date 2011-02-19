#include "Bdot.h"
#include "../../../datatype/Time.h"
#include "../../../util/Ostream.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {


Bdot::Bdot(int instance_id,double k, 
		devicedriver::OutputPort<datatype::MagneticField>* mag_source,
		devicedriver::InputPort<datatype::MagneticMoment>* torque_out
		) : StrategyBase(instance_id, "Bdot"), k_(k)
{
	this->connectSource<0>(mag_source);
	if(torque_out != 0){
		torque_out->connectSource_(this);
	}
}

void Bdot::do_compute(const datatype::Time& t) {
	if(t <= this->last_update_) return; //既に別のブロック経由で更新済みなら再計算しない
	util::cout << "compute: bdot" << util::endl;
	this->source<0,datatype::MagneticField>().getValueInBodyFrame(t);

	for(int i = 0; i < 3; i++){
		this->value_b_[i] = - this->k_ * (this->source<0,datatype::MagneticField>().value_b_[i] - this->mag_before_[i]);
	}

	this->mag_before_ = this->source<0,datatype::MagneticField>().value_b_;

	this->last_update_ = t;
}

} /* End of namespace core::mode::strategy::input */
} /* End of namespace core::mode::strategy */
} /* End of namespace core::mode */
} /* End of namespace core */
