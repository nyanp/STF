/**
 * @file   PRISMEKF.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_control_PRISMEKF_h
#define stf_core_strategy_control_PRISMEKF_h

#include "../../core/strategy/control/EKF.h"
#include "../../datatype/ITelemetable.h"
#include "../../interface/Iterator.h"


namespace stf {
namespace interface {
template<int U> class PRISMEKFIterator;
}
namespace core {
namespace strategy {
namespace control {

template<int U> class PRISMEKFIterator;

class PRISMEKF : public EKF
{
public:
	PRISMEKF(int instance_id) : EKF(instance_id){}
	virtual ~PRISMEKF(){}
private:
	template<int U>friend class interface::PRISMEKFIterator;
};


} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_strategy_control_input_PRISMEKF_h
