/**
 * @file   NJRW.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_rw_NJRW_h
#define stf_core_devicedriver_rw_NJRW_h

#include "../../../core/devicedriver/rw/RWBase.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace rw {

template<class T>
class NJRW : public RWBase<T> {
public:
	~NJRW(){}
	// 1Nm, 500Nms
	NJRW(int instance_id, const datatype::DCM &angle) : RWBase(instance_id, angle, 1, -1, 500){}
private:

};

} /* End of namespace stf::core::devicedriver::rw */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_mtq_RW_h
