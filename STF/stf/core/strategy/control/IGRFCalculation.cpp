#include "IGRFCalculation.h"
#include "../../../datatype/Time.h"

namespace scube {
namespace core {
namespace strategy {
namespace control {


IGRFCalculation::IGRFCalculation(int instance_id, 
		devicedriver::OutputPort<datatype::MagneticField>* mag_source,
		devicedriver::OutputPort<datatype::PositionInfo>* orbitinfo_source,
		devicedriver::InputPort<datatype::StaticVector<2>>* earthvec_out
		) : StrategyBase(instance_id, "IGRFCalculation")
{
	this->connectSource<0>(mag_source);
	this->connectSource<1>(orbitinfo_source);
	if(earthvec_out != 0){
		earthvec_out->connectSource_(this);
	}
}

void IGRFCalculation::doCompute(const datatype::Time& t) {
	if(t <= this->last_update_) return; //既に別のブロック経由で更新済みなら再計算しない
	util::cout << "compute: IGRF" << util::endl;
	this->last_update_ = t;
}

} /* End of namespace core::mode::strategy::input */
} /* End of namespace core::mode::strategy */
} /* End of namespace core::mode */
} /* End of namespace core */
