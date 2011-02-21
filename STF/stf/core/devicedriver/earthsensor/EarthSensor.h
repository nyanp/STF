/**
 * @file   EarthSensor.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_earthsensor_EarthSensor_h
#define stf_core_devicedriver_earthsensor_EarthSensor_h

#include "EarthSensorBase.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace earthsensor {


template <class T>
class EarthSensor : public EarthSensorBase<T>{
public:  
	// 3-Sigmaで1度精度
	EarthSensor(int instance_id, const datatype::DCM &angle) : EarthSensorBase(instance_id,angle,1,3){}
	~EarthSensor(){}
private:
	EarthSensor(){}
};

} /* End of namespace stf::core::devicedriver::earthsensor */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_earthsensor_EarthSensor_h
