/**
 * @file   GPIO.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef aocs_environment_SH_GPIO_h
#define aocs_environment_SH_GPIO_h

#include "../IODriverBase.h"
#include "iodefine.h"

namespace stf {
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


} /* End of namespace stf::environment::SH */
} /* End of namespace stf::environment */
} /* End of namespace stf */

#endif // aocs_environment_SH_GPIO_h_h