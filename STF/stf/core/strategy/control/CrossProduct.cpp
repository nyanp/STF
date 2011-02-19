#include "CrossProduct.h"
#include "../../../datatype/DCM.h"
#include "../../../datatype/OrbitCalc.h"
#include "../../../datatype/TypeConverter.h"
#include "../../../GlobalObject.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {


CrossProduct::CrossProduct(int instance_id, 
		devicedriver::OutputPort<datatype::StaticVector<3>>* torquer_source,
		devicedriver::OutputPort<datatype::MagneticField>* b_source,
		devicedriver::InputPort<datatype::MagneticMoment>* mag_out
		) : StrategyBase(instance_id, "CrossProduct")
{
	this->connectSource<0>(torquer_source);
	this->connectSource<1>(b_source);
	if(mag_out != 0){
		mag_out->connectSource_(this);
	}
}

void CrossProduct::do_compute(const datatype::Time& t) {
	if(t <= this->last_update_) return; //既に別のブロック経由で更新済みなら再計算しない
	util::cout << "compute: crossproduct" << util::endl;	
	// M = B * T / |B|2
	datatype::MagneticField B = this->source<1,datatype::MagneticField>().getValueInBodyFrame(t);
	datatype::StaticVector<3> T = this->source<0,datatype::StaticVector<3>>().getValueInBodyFrame(t);

	this->value_b_ = (B % T) / (B.norm(2) * B.norm(2));

	this->last_update_ = t;
}


} /* End of namespace core::mode::strategy::control */
} /* End of namespace core::mode::strategy */
} /* End of namespace core::mode */
} /* End of namespace core */
