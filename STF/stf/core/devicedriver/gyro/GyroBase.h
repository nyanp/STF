/**
 * @file   GyroBase.h
 * @brief  ジャイロセンサの基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_gyro_GyroBase_h
#define stf_core_devicedriver_gyro_GyroBase_h

#include "../../../util/stfassert.h"
#include "../../../util/Macros.h"
#include "../../../util/math/Rand.h"
#include "../../../util/math/RungeKutta.h"
#include "../../../datatype/Scalar.h"
#include "../../../datatype/StaticVector.h"
#include "../../environment/Envfwd.h"
#include "../AOCSSensor.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace gyro {

//! ジャイロセンサの基底クラス．
/*! 
	@tparam Env コンポーネントの環境クラス．
*/
template <class Env>
class GyroBase : public AOCSSensor<Env, datatype::StaticVector<3>, datatype::Scalar>{
public:
	GyroBase(const datatype::DCM &angle, double sigma, double tau);
	~GyroBase(){}
	virtual datatype::Scalar filter(const datatype::Scalar& value); 

private:

	DO_UPDATE_SIMULATOR(){
		this->value_ = filter(this->environment_->getAngularVelocity(*this));
		if(this->datapool_ != 0)
			datapool_->set<GyroBase<environment::Simulator<App> >>(datapool_hold_index_, this->value_);
	}

	//! バイアス分散
    double sigma_;
	//! バイアスレートの真値
	datatype::Scalar bias_rate_; 
    //! ECRVの時定数
    double tau_;
};

template <class Env>
GyroBase<Env>::GyroBase(const datatype::DCM &dcm, double sigma, double tau)
	: AOCSSensor<Env, datatype::StaticVector<3>, datatype::Scalar>( "Gyro", dcm), sigma_(sigma), tau_(tau), bias_rate_(0.0)
{

}

template <class Env>
datatype::Scalar GyroBase<Env>::filter(const datatype::Scalar& value){
    for(int i = 0; i < 3; i++){
		double noise = util::math::WhiteNoise(this->sigma_, 0);
		//slope計算は高速化のためScalarではなくdoubleで行う
		this->bias_rate_ += util::math::RungeKutta::slope(bias_rate_.value(), -1 / tau_, noise, 0.1);
    }
	return value + bias_rate_;
}

} /* End of namespace stf::core::devicedriver::gyro */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_gyro_GyroBase_h
