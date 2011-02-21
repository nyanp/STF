/**
 * @file   SunSensor.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_sunsensor_SunSensor_h
#define stf_core_devicedriver_sunsensor_SunSensor_h

#include "SunSensorBase.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace sunsensor {
template <class T>
class SunSensor : public SunSensorBase<T>{
public:  
	// 3-Sigmaで1度精度
	SunSensor(int instance_id, const datatype::DCM &angle) : SunSensorBase(instance_id,angle,1,3){}
	~SunSensor(){}
private:
	SunSensor(){}
};

} /* End of namespace stf::core::devicedriver::sunsensor */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_sunsensor_SunSensor_h
