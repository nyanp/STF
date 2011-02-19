#ifndef stf_core_devicedriver_magnetometer_NJCoarseTAM_h
#define stf_core_devicedriver_magnetometer_NJCoarseTAM_h

#include "../../core/devicedriver/magnetometer/TAMBase.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace magnetometer {
template <class T>
class NJCoarseTAM : public TAMBase<T>{
public:  
	// 3-SigmaÇ≈1ìxê∏ìx
	NJCoarseTAM(int instance_id, const datatype::DCM &angle) : TAMBase(instance_id,angle){}
	~NJCoarseTAM(){}
	virtual void doUpdate(){}
private:
	NJCoarseTAM(){}
};

} /* End of namespace stf::core::devicedriver::magnetometer */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_magnetometer_NJCoarseTAM_h
