/**
 * @file   NJRoughTAM.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_magnetometer_NJRoughTAM_h
#define stf_core_devicedriver_magnetometer_NJRoughTAM_h

#include "../../core/devicedriver/magnetometer/TAMBase.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace magnetometer {
template <class T>
class NJRoughTAM : public TAMBase<T>{
public:  
	// 3-SigmaÇ≈1ìxê∏ìx
	NJRoughTAM(int instance_id, const datatype::DCM &angle) : TAMBase(instance_id, angle){}
	~NJRoughTAM(){}
	virtual void do_update(){}
private:
	NJRoughTAM(){}
};

} /* End of namespace stf::core::devicedriver::magnetometer */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_magnetometer_NJRoughTAM_h
