#ifndef stf_core_devicedriver_mtq_SmallMTQ_h
#define stf_core_devicedriver_mtq_SmallMTQ_h

#include "MTQBase.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace mtq {

template<class T>
class SmallMTQ : public MTQBase<T> {
public:
	~SmallMTQ(){}
	//50mNmo—ÍCüŒ`«Œë·1“
	SmallMTQ(int instance_id, const datatype::DCM &angle) : MTQBase(instance_id, angle, 0.05, 1){}
private:
	SmallMTQ(){}
};

} /* End of namespace stf::core::devicedriver::mtq */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_mtq_MTQ_h
