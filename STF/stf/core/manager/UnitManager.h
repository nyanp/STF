/**
 * @file   UnitManager.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_manager_UnitManager_h
#define stf_core_manager_UnitManager_h

#include "UnitManagerBase.h"

namespace stf {
namespace core {
namespace manager {

class UnitManager : public UnitManagerBase 
{
public:
	UnitManager(int instance_id) : UnitManagerBase(instance_id){}
	~UnitManager(){}
};

} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_manager_UnitManager_h