#ifndef stf_core_devicedriver_magnetometer_TAM_h
#define stf_core_devicedriver_magnetometer_TAM_h

#include "TAMBase.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace magnetometer {
template <class T>
class TAM : public TAMBase<T>{
public:  
	// 3-SigmaÇ≈1ìxê∏ìx
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
