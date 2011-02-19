/**
 * @file   PRISMRMMEKF.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_control_PRISMRMMEKF_h
#define stf_core_strategy_control_PRISMRMMEKF_h

#include "../../core/strategy/control/RMMEKF.h"
#include "../../interface/Iterator.h"

namespace stf {
namespace interface {
template<int U> class PRISMRMMEKFIterator;
}
namespace core {
namespace strategy {
namespace control {
	
class PRISMRMMEKF : public RMMEKF
{
public:
	PRISMRMMEKF(int instance_id) : RMMEKF(instance_id){}
	PRISMRMMEKF(int instance_id, 
		OutputPort<datatype::MagneticField>* mag_source, OutputPort<datatype::StaticVector<3>>* omega_source,
		InputPort<datatype::MagneticMoment>* mag_out = 0) : RMMEKF(instance_id,mag_source,omega_source,mag_out){}
	virtual ~PRISMRMMEKF(){}
private:
	template<int U>friend class interface::PRISMRMMEKFIterator;
};


} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_strategy_control_input_PRISMRMMEKF_h
