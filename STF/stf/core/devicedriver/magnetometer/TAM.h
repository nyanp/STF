/**
 * @file   TAM.h
 * @brief  ソフトウェアシミュレーションレベルで動作する磁気センサドライバ．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_magnetometer_TAM_h
#define stf_core_devicedriver_magnetometer_TAM_h

#include "TAMBase.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace magnetometer {

//! ソフトウェアシミュレーションレベルで動作する磁気センサドライバ．
/*! 
	@tparam T コンポーネントの環境クラス．
*/
template <class T>
class TAM : public TAMBase<T>{
public:  
	// 3-Sigmaで1度精度
	TAM(int instance_id, const datatype::DCM &angle) : TAMBase(instance_id,angle){}
	~TAM(){}
private:
	TAM(){}
};

} /* End of namespace stf::core::devicedriver::magnetometer */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_magnetometer_TAM_h
