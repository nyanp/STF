/**
 * @file   NJMC.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_NJMC_NJMC_h
#define stf_core_devicedriver_NJMC_NJMC_h

#include "../../core/devicedriver/MTQ/MTQBase.h"
#include "../../interface/Iterator.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace mtq {

template<class T>
class NJMC : public MTQBase<T> {
public:
	~NJMC(){}
	//1NmèoóÕÅCê¸å`ê´åÎç∑5Åì
	NJMC(int instance_id, const datatype::DCM &angle) : MTQBase(instance_id, angle, 1, -1, 5){}
	virtual void doUpdate(){}
private:
	NJMC(){}
};


} /* End of namespace stf::core::devicedriver::mtq */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_NJMC_NJMC_h
