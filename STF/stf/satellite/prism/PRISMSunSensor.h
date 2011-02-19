#ifndef stf_core_devicedriver_PRISMSunSensor_PRISMSunSensor_h
#define stf_core_devicedriver_PRISMSunSensor_PRISMSunSensor_h

#include "../../core/devicedriver/sunsensor/SunSensorBase.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace sunsensor {
template <class T>
class PRISMSunSensor : public SunSensorBase<T>{
public:  
	// 3-SigmaÇ≈1ìxê∏ìx
	PRISMSunSensor(int instance_id, const datatype::DCM &angle) : SunSensorBase(instance_id,angle,1,3){}
	~PRISMSunSensor(){}
	virtual void doUpdate(){}
private:
	PRISMSunSensor(){}
};

} /* End of namespace stf::core::devicedriver::sunsensor */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_PRISMSunSensor_PRISMSunSensor_h
