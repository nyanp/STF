/**
 * @file   GyroBase.cpp
 * @brief  ジャイロセンサの基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
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
void GyroBase<environment::Simulator>::do_update(){
	this->set_value(filter(this->environment_->getAngularVelocity(*this)));
	if(this->datapool_ != 0){
		datapool_->set<GyroBase<environment::Simulator>>(datapool_hold_index_,this->value_);
	}
}

template <>
datatype::Scalar GyroBase<environment::Simulator>::filter(const datatype::Scalar& value){
    for(int i = 0; i < 3; i++){
		double noise = util::math::WhiteNoise(this->sigma_,0);
		//slope計算は高速化のためScalarではなくdoubleで行う
		this->bias_rate_ += util::math::RungeKutta::slope(bias_rate_.value(), -1 / tau_, noise, 0.1);
    }
	return value + bias_rate_;
}

} /* End of namespace stf::core::devicedriver::gyro */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */