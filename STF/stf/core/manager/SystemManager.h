#ifndef stf_core_manager_SystemManager_h
#define stf_core_manager_SystemManager_h

#include "SystemManagerBase.h"

namespace stf {
namespace core {
namespace manager {

class SystemManager : public SystemManagerBase { 
public:
	SystemManager(int instance_id) : SystemManagerBase(instance_id){}
	~SystemManager(){}
};

} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif //stf_core_manager_SystemManager_h
