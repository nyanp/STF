/**
 * @file   EarthSensor.h
 * @brief  ソフトウェアシミュレーションレベルで動作する地球センサドライバ．
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

//! ソフトウェアシミュレーションレベルで動作する地球センサドライバ．
/*! 
	@tparam Env コンポーネントの環境クラス．
*/
template <class Env>
class EarthSensor : public EarthSensorBase<Env>{
public:  
	// 3-Sigmaで1度精度
	EarthSensor(const datatype::DCM &angle) : EarthSensorBase(angle, 1, 3){}
	~EarthSensor(){}
private:
	EarthSensor(){}
};

} /* End of namespace stf::core::devicedriver::earthsensor */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_earthsensor_EarthSensor_h
