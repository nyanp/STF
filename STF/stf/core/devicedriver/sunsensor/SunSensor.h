/**
 * @file   SunSensor.h
 * @brief  ソフトウェアシミュレーションレベルで動作する太陽センサドライバ．
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

//! ソフトウェアシミュレーションレベルで動作する太陽センサドライバ．
/*! 
	@tparam Env コンポーネントの環境クラス．
*/
template <class Env>
class SunSensor : public SunSensorBase<Env>{
public:  
	// 3-Sigmaで1度精度
	SunSensor(const datatype::DCM &angle) : SunSensorBase(angle, 1, 3){}
	~SunSensor(){}
private:
	SunSensor(){}
};

} /* End of namespace stf::core::devicedriver::sunsensor */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_sunsensor_SunSensor_h
