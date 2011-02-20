/**
 * @file   IControlStrategy.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_control_IControlStorategy_h
#define stf_core_strategy_control_IControlStorategy_h
#include "../../../datatype/IAocsData.h"

namespace stf {
namespace datatype {
class Time;
}
namespace core {
namespace strategy {
namespace control {

class IControlStrategy {
public:
    virtual void compute_torque(const datatype::Time& t)  = 0;
	//virtual void changeTarget(const datatype::IAocsData& newtarget) = 0;
    virtual ~IControlStrategy() { }
};

} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_strategy_control_IControlStorategy_h
