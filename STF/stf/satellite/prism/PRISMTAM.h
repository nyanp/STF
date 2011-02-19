#ifndef stf_core_devicedriver_magnetometer_PRISMTAM_h
#define stf_core_devicedriver_magnetometer_PRISMTAM_h

#include "../../core/devicedriver/magnetometer/TAMBase.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace magnetometer {
template <class T>
class PRISMTAM : public TAMBase<T>{
public:  
	// 3-SigmaÇ≈1ìxê∏ìx
	PRISMTAM(int instance_id, const datatype::DCM &angle) : TAMBase(instance_id,angle){}
	~PRISMTAM(){}
	virtual void doUpdate(){}
private:
	PRISMTAM(){}
};

} /* End of namespace stf::core::devicedriver::magnetometer */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_magnetometer_PRISMTAM_h
