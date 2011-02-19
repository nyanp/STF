/**
 * @file   GyroBase.h
 * @brief  
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

template <class T>
class GyroBase : public AOCSSensor<datatype::StaticVector<3>, datatype::Scalar, T>{
public:
    GyroBase();
	GyroBase(int instance_id, const datatype::DCM &angle, double sigma, double tau);
	~GyroBase();
	virtual void doUpdate();
	virtual datatype::Scalar inputFilter(const datatype::Scalar& value); 
private:
    double sigma_;
	datatype::Scalar bias_rate_; 
    //ECRVÇÃéûíËêî
    double tau_;
};

template <class T>
GyroBase<T>::GyroBase()
{
}

template <class T>
GyroBase<T>::~GyroBase()
{
}


template <class T>
GyroBase<T>::GyroBase(int instance_id, const datatype::DCM &dcm,double sigma, double tau)
	: AOCSSensor<datatype::StaticVector<3>, datatype::Scalar, T>(instance_id, "Gyro", dcm), sigma_(sigma), tau_(tau), bias_rate_(0.0)
{

}

template <class T>
void GyroBase<T>::doUpdate(){

}

template <>
void GyroBase<environment::Simulator>::doUpdate();
template <>
datatype::Scalar GyroBase<environment::Simulator>::inputFilter(const datatype::Scalar& value); 
} /* End of namespace stf::core::devicedriver::gyro */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_gyro_GyroBase_h
