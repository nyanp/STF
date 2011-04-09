/**
 * @file   NJRMMEKF.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_control_NJRMMEKF_h
#define stf_core_strategy_control_NJRMMEKF_h

#include "../../../core/strategy/control/RMMEKF.h"
#include "../../../interface/Iterator.h"

namespace stf {
namespace interface {
template<int U> class NJRMMEKFIterator;
}
namespace core {
namespace strategy {
namespace control {
	
class NJRMMEKF : public RMMEKF
{
public:
	NJRMMEKF(){}
	NJRMMEKF( 
		OutputPort<datatype::MagneticField>* mag_source, OutputPort<datatype::StaticVector<3>>* omega_source,
		InputPort<datatype::MagneticMoment>* mag_out = 0) : RMMEKF(mag_source, omega_source, mag_out){}
	virtual ~NJRMMEKF(){}
private:
	template<int U>friend class interface::NJRMMEKFIterator;
};


} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_strategy_control_input_NJRMMEKF_h
