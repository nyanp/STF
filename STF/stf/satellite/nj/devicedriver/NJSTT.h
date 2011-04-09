/**
 * @file   NJSTT.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_stt_NJSTT_h
#define stf_core_devicedriver_stt_NJSTT_h

#include "../../../core/devicedriver/stt/STTBase.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace stt {

template <class T>
class NJSTT : public STTBase<T>{
public:  
	//10arcsecê∏ìx(3-Sigma)ÇÃSTTÅD
	NJSTT( const datatype::DCM &angle) : STTBase( angle, 10){}
	~NJSTT(){}
private:
	NJSTT(){}
};

} /* End of namespace stf::core::devicedriver::stt */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_stt_STT_h
