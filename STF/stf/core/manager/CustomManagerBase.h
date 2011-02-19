/**
 * @file   CustomManagerBase.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_manager_CustomManagerBase_h
#define stf_core_manager_CustomManagerBase_h

#include "ManagerBase.h"

namespace stf {
namespace core {
namespace manager {

class CustomManagerBase : public ManagerBase
{
public:
	CustomManagerBase(int instance_id) : ManagerBase(instance_id, "CustomManager"){}
	virtual ~CustomManagerBase(){}
protected:

};

} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_manager_CustomManagerBase_h