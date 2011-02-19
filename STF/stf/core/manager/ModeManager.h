#ifndef stf_core_manager_ModeManager_h
#define stf_core_manager_ModeManager_h

#include "ModeManagerBase.h"

namespace stf {
namespace core {
namespace manager {

class ModeManager : public ModeManagerBase { 
public:
	ModeManager(int instance_id) : ModeManagerBase(instance_id){}
	~ModeManager(){}
};

} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif //stf_core_manager_ModeManager_h
