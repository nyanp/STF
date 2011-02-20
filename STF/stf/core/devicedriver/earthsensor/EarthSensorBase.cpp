/**
 * @file   EarthSensorBase.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "EarthSensorBase.h"
#include "../../../datatype/TypeConverter.h"
#include "../../../environment/Simulator.h"
#include "../../datapool/Datapool.h"
#include "../../../util/math.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace earthsensor {

//STT本体のQuaternion
//シミュレータ環境ではSTT座標系での真値を取得する
template <>
void EarthSensorBase<environment::Simulator>::do_update(){
	this->set_value(filter(this->environment_->getEarthDirection(*this)));
	if(this->datapool_ != 0){
		datapool_->set<EarthSensorBase<environment::Simulator>>(datapool_hold_index_,this->value_);
	}
}

template <>
datatype::StaticVector<2> EarthSensorBase<environment::Simulator>::filter(const datatype::StaticVector<2>& value){
	datatype::StaticVector<3> earthvector_true = datatype::TypeConverter::toRectangular(value);

	datatype::EulerAngle angle;
	angle[0] = util::math::WhiteNoise(this->err_deg_ * util::math::DEG2RAD ,0) / 3;
	angle[1] = util::math::WhiteNoise(this->err_deg_ * util::math::DEG2RAD, 0) / 3;
	angle[2] = util::math::WhiteNoise(this->err_deg_ * util::math::DEG2RAD, 0) / 3;

	datatype::StaticVector<3> earthvector = datatype::TypeConverter::toDCM(angle) * earthvector_true;

	return datatype::TypeConverter::toPolar(earthvector);
}

} /* End of namespace stf::core::devicedriver::stt */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */
