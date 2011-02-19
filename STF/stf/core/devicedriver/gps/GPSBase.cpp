#include "GPSBase.h"
#include "../../datapool/Datapool.h"
#include "../../../environment/Simulator.h"
#include "../../../util/math.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace gps {

template <>
void GPSBase<environment::Simulator>::doUpdate(){
	this->setValue(inputFilter(this->environment_->getTrueSatellitePosition()));

	if(this->datapool_ != 0){
		datapool_->set<GPSBase<environment::Simulator>>(datapool_hold_index_,this->value_);
	}
}
//
template <>
datatype::PositionInfo GPSBase<environment::Simulator>::inputFilter(const datatype::PositionInfo& value){
	return value;
}

} /* End of namespace stf::core::devicedriver::gps */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */