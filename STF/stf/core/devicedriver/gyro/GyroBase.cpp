#include "GyroBase.h"
#include "../../datapool/Datapool.h"
#include "../../../environment/Simulator.h"
#include "../../../util/math.h"
#include "../../../util/math/RungeKutta.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace gyro {

template <>
void GyroBase<environment::Simulator>::doUpdate(){
	this->setValue(inputFilter(this->environment_->getAngularVelocity(*this)));
	if(this->datapool_ != 0){
		datapool_->set<GyroBase<environment::Simulator>>(datapool_hold_index_,this->value_);
	}
}
//
template <>
datatype::Scalar GyroBase<environment::Simulator>::inputFilter(const datatype::Scalar& value){
    for(int i = 0; i < 3; i++){
		datatype::Scalar noise = util::math::WhiteNoise(this->sigma_,0);
		this->bias_rate_ += util::math::RungeKutta::slope(bias_rate_, -1 / tau_, noise, 0.1);
    }

	return value + bias_rate_;
}

} /* End of namespace stf::core::devicedriver::gyro */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */