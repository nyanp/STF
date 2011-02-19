/**
 * @file   NJGyro.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_NJGyro_NJGyro_h
#define stf_core_devicedriver_NJGyro_NJGyro_h

#include "../../core/devicedriver/gyro/GyroBase.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace gyro {

template<class T>
class NJGyro : public GyroBase<T> {
public:
	NJGyro(){}
	//Sigma =0.02, tau(ECRV)=1000sec
	NJGyro(int instance_id, const datatype::DCM &angle) : GyroBase(instance_id, angle,0.02,GYROECRV){}
	~NJGyro(){}
	virtual void doUpdate(){}
private:
};



} /* End of namespace stf::core::devicedriver::gyro */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_NJGyro_NJGyro_h
