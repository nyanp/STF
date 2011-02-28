/**
 * @file   GyroBase.h
 * @brief  ジャイロセンサの基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_gyro_GyroBase_h
#define stf_core_devicedriver_gyro_GyroBase_h

#include "../../../datatype/DCM.h"
#include "../../../datatype/Quaternion.h"
#include "../../../datatype/Scalar.h"
#include "../../../datatype/StaticVector.h"
#include "../AOCSSensor.h"

namespace stf {
namespace environment {
class Simulator;
}
namespace core {
namespace devicedriver {
namespace gyro {

//! ジャイロセンサの基底クラス．
/*! 
	@tparam T コンポーネントの環境クラス．
*/
template <class T>
class GyroBase : public AOCSSensor<datatype::StaticVector<3>, datatype::Scalar, T>{
public:
	GyroBase(){}
	GyroBase(int instance_id, const datatype::DCM &angle, double sigma, double tau);
	~GyroBase(){}
	virtual void do_update();
	virtual datatype::Scalar filter(const datatype::Scalar& value); 
private:
	//! バイアス分散
    double sigma_;
	//! バイアスレートの真値
	datatype::Scalar bias_rate_; 
    //! ECRVの時定数
    double tau_;
};

template <class T>
GyroBase<T>::GyroBase(int instance_id, const datatype::DCM &dcm, double sigma, double tau)
	: AOCSSensor<datatype::StaticVector<3>, datatype::Scalar, T>(instance_id, "Gyro", dcm), sigma_(sigma), tau_(tau), bias_rate_(0.0)
{

}

template <class T>
void GyroBase<T>::do_update(){

}

template <>
void GyroBase<environment::Simulator>::do_update();
template <>
datatype::Scalar GyroBase<environment::Simulator>::filter(const datatype::Scalar& value); 
} /* End of namespace stf::core::devicedriver::gyro */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_gyro_GyroBase_h
