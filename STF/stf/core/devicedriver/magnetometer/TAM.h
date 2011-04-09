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
	@tparam Env コンポーネントの環境クラス．
*/
template <class Env>
class TAM : public TAMBase<Env>{
public:  
	// 3-Sigmaで1度精度
	TAM(const datatype::DCM &angle) : TAMBase(angle){}
	~TAM(){}
private:
};

} /* End of namespace stf::core::devicedriver::magnetometer */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_magnetometer_TAM_h
