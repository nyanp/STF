/**
 * @file   GPIO.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_environment_SH_GPIO_h
#define stf_core_environment_SH_GPIO_h

#include "../IODriverBase.h"
#include "iodefine.h"

namespace stf {
namespace core {
namespace environment {
namespace SH {

class GPIOBase {
public:
	GPIOBase(){}
private:
	
};

template<struct ST>
class GPIO{

};


} /* End of namespace stf::core::environment::SH */
} /* End of namespace stf::core::environment */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_environment_SH_GPIO_h_h