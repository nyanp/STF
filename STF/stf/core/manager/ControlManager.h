#ifndef core_manager_ControlManager_h
#define core_manager_ControlManager_h

#include "ControlManagerBase.h"

namespace stf {
namespace core {
namespace mode {
namespace strategy {
namespace control {
class IControlStrategy;
}
}
}

namespace manager {

class ControlManager : public ControlManagerBase {
public:
	ControlManager(int instance_id) : ControlManagerBase(instance_id) {}
	~ControlManager(){}
private:
	//strategy::control::IControlStrategy* strategy_;
};


} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // core_manager_ControlManager_h
