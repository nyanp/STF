/**
 * @file   STT.h
 * @brief  
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

template <class T>
class STT : public STTBase<T>{
public:  
	//10arcsec精度(3-Sigma)のSTT．
	STT(int instance_id, const datatype::DCM &angle) : STTBase(instance_id, angle,10){}
	~STT(){}
private:
	STT(){}
};

} /* End of namespace stf::core::devicedriver::stt */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_stt_STT_h
