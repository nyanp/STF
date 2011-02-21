/**
 * @file   MTQ.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_mtq_MTQ_h
#define stf_core_devicedriver_mtq_MTQ_h

#include "MTQBase.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace mtq {

template<class T>
class MTQ : public MTQBase<T> {
public:
	~MTQ(){}
	//1Nm出力，線形性誤差5％
	MTQ(int instance_id, const datatype::DCM &angle) : MTQBase(instance_id, angle, 1, -1, 5){}
private:
	MTQ(){}
};

} /* End of namespace stf::core::devicedriver::mtq */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_mtq_MTQ_h
