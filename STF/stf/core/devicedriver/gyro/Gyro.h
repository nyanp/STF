#ifndef stf_core_devicedriver_gyro_Gyro_h
#define stf_core_devicedriver_gyro_Gyro_h

#include "GyroBase.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace gyro {

template<class T>
class Gyro : public GyroBase<T> {
public:
	Gyro(){}
	//Sigma =0.02, tau(ECRV)=1000sec
	Gyro(int instance_id, const datatype::DCM &angle) : GyroBase(instance_id, angle,0.02,GYROECRV){}
	~Gyro(){}
private:
};



} /* End of namespace stf::core::devicedriver::gyro */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_gyro_Gyro_h
