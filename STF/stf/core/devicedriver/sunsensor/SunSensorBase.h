/**
 * @file   SunSensorBase.h
 * @brief  太陽センサの基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_sunsensor_SunSensorBase_h
#define stf_core_devicedriver_sunsensor_SunSensorBase_h

#include "../../../util/stfassert.h"
#include "../../../util/Macros.h"
#include "../AOCSSensor.h"
#include "../../../datatype/StaticVector.h"
#include "../../environment/Envfwd.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace sunsensor {

//! 太陽センサの基底クラス．
/*! 
	@tparam Env コンポーネントの環境クラス．
*/
template <class Env>
class SunSensorBase : public AOCSSensor<Env, datatype::StaticVector<2>, datatype::StaticVector<2>>{
public:
	SunSensorBase(const datatype::DCM &angle, double err_deg, int sigma = 3);
	virtual ~SunSensorBase(){}
	virtual datatype::StaticVector<2> filter(const datatype::StaticVector<2>& value); 
private:

	DO_UPDATE_SIMULATOR(){
		this->value_ = filter(this->environment_->getSunDirection(*this));
		if(this->datapool_ != 0){
			datapool_->set<SunSensorBase<environment::Simulator<App> >>(datapool_hold_index_, this->value_);
		}
	}

    SunSensorBase();
	double err_deg_;
	int sigma_;
};

template <class Env>
SunSensorBase<Env>::SunSensorBase(const datatype::DCM& dcm, double err_deg, int sigma)
	: AOCSSensor<Env, datatype::StaticVector<2>, datatype::StaticVector<2>>("SS", dcm), err_deg_(err_deg), sigma_(sigma)
{

}

template <class Env>
datatype::StaticVector<2> SunSensorBase<Env>::filter(const datatype::StaticVector<2>& value){
	datatype::StaticVector<3> sunvector_true = datatype::TypeConverter::toRectangular(value);

	datatype::EulerAngle angle;
	//angle[0] = util::math::WhiteNoise(this->err_deg_ * util::math::DEG2RAD , 0) / 3;
	//angle[1] = util::math::WhiteNoise(this->err_deg_ * util::math::DEG2RAD, 0) / 3;
	//angle[2] = util::math::WhiteNoise(this->err_deg_ * util::math::DEG2RAD, 0) / 3;

	datatype::StaticVector<3> sunvector = datatype::TypeConverter::toDCM(angle) * sunvector_true;

	return datatype::TypeConverter::toPolar(sunvector);
}
} /* End of namespace stf::core::devicedriver::sunsensor */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_sunsensor_SunSensorBase_h
