/**
 * @file   Gyro.h
 * @brief  ソフトウェアシミュレーションレベルで動作するジャイロセンサドライバ．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_gyro_Gyro_h
#define stf_core_devicedriver_gyro_Gyro_h

#include "GyroBase.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace gyro {

//! ソフトウェアシミュレーションレベルで動作するジャイロセンサドライバ．
/*! 
	@tparam T コンポーネントの環境クラス．
*/
template<class T>
class Gyro : public GyroBase<T> {
public:
	//Sigma =0.02, tau(ECRV)=1000sec
	Gyro(const datatype::DCM &angle) : GyroBase(angle, 0.02, 1000){}
	~Gyro(){}
private:
};



} /* End of namespace stf::core::devicedriver::gyro */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_gyro_Gyro_h
