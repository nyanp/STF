/**
 * @file   EarthSensorBase.h
 * @brief  地球センサの基底クラス
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_earthsensor_EarthSensorBase_h
#define stf_core_devicedriver_earthsensor_EarthSensorBase_h

#include "../../../util/stfassert.h"
#include "../../../util/Macros.h"
#include "../AOCSSensor.h"
#include "../../../datatype/StaticVector.h"
#include "../../environment/Envfwd.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace earthsensor {

//! 地球センサの基底クラス．
/*! 
	@tparam Env コンポーネントの環境クラス．
*/
template <class Env>
class EarthSensorBase : public AOCSSensor<Env, datatype::StaticVector<2>, datatype::StaticVector<2>>{
public:
	EarthSensorBase(const datatype::DCM &angle, double err_deg, int sigma = 3);
	virtual ~EarthSensorBase(){}
	virtual datatype::StaticVector<2> filter(const datatype::StaticVector<2>& value); 
private:

	DO_UPDATE_SIMULATOR(){
		this->value_ = filter(this->environment_->getEarthDirection(*this));
		if(this->datapool_ != 0){
			datapool_->set<EarthSensorBase<environment::Simulator<App> >>(datapool_hold_index_, this->value_);
		}
	}

    EarthSensorBase();
	double err_deg_;
	int sigma_;
};

template <class Env>
EarthSensorBase<Env>::EarthSensorBase(const datatype::DCM& dcm, double err_deg, int sigma)
	: AOCSSensor<datatype::StaticVector<2>, datatype::StaticVector<2>, T>("EarthSensor", dcm), err_deg_(err_deg), sigma_(sigma)
{

}

template <class Env>
datatype::StaticVector<2> EarthSensorBase<Env>::filter(const datatype::StaticVector<2>& value){
	datatype::StaticVector<3> earthvector_true = datatype::TypeConverter::toRectangular(value);

	datatype::EulerAngle angle;
	angle[0] = util::math::WhiteNoise(this->err_deg_ * util::math::DEG2RAD , 0) / 3;
	angle[1] = util::math::WhiteNoise(this->err_deg_ * util::math::DEG2RAD, 0) / 3;
	angle[2] = util::math::WhiteNoise(this->err_deg_ * util::math::DEG2RAD, 0) / 3;

	datatype::StaticVector<3> earthvector = datatype::TypeConverter::toDCM(angle) * earthvector_true;

	return datatype::TypeConverter::toPolar(earthvector);
}

} /* End of namespace stf::core::devicedriver::earthsensor */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_earthsensor_EarthSensorBase_h
