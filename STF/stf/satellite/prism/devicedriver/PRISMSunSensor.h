/**
 * @file   PRISMSunSensor.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_PRISMSunSensor_PRISMSunSensor_h
#define stf_core_devicedriver_PRISMSunSensor_PRISMSunSensor_h

#include "../../../core/devicedriver/sunsensor/SunSensorBase.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace sunsensor {

template <class Env>
class PRISMSunSensor : public SunSensorBase<Env>{
public:  
	// 3-SigmaÇ≈1ìxê∏ìx
	PRISMSunSensor( const datatype::DCM &angle) : SunSensorBase(angle, 1, 3){}
	~PRISMSunSensor(){}
	virtual void do_update(){}
private:
	PRISMSunSensor(){}
};

} /* End of namespace stf::core::devicedriver::sunsensor */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_PRISMSunSensor_PRISMSunSensor_h
