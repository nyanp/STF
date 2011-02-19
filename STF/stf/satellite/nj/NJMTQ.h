#ifndef stf_core_devicedriver_NJMTQ_NJMTQ_h
#define stf_core_devicedriver_NJMTQ_NJMTQ_h

#include "../../core/devicedriver/mtq/MTQBase.h"
#include "../../interface/Iterator.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace mtq {

template<class T>
class NJMTQ : public MTQBase<T> {
public:
	~NJMTQ(){}
	//1NmèoóÕÅCê¸å`ê´åÎç∑5Åì
	NJMTQ(int instance_id, const datatype::DCM &angle) : MTQBase(instance_id, angle, 1, -1, 5){}
	virtual void doUpdate(){}
private:
	NJMTQ(){}
};


} /* End of namespace stf::core::devicedriver::mtq */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_NJMTQ_NJMTQ_h
