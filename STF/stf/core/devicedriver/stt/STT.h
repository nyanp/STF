/**
 * @file   STT.h
 * @brief  ソフトウェアシミュレーションレベルで動作するスターセンサドライバ．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_stt_STT_h
#define stf_core_devicedriver_stt_STT_h

#include "STTBase.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace stt {

//! ソフトウェアシミュレーションレベルで動作するスターセンサドライバ．
/*! 
	@tparam Env コンポーネントの環境クラス．
*/
template <class Env>
class STT : public STTBase<Env>{
public:  
	//10arcsec精度(3-Sigma)のSTT．
	STT(const datatype::DCM &angle) : STTBase(angle, 10){}
	~STT(){}
private:
	STT(){}
};

} /* End of namespace stf::core::devicedriver::stt */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_stt_STT_h
