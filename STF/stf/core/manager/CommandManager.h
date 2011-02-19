#ifndef core_manager_CommandManager_h
#define core_manager_CommandManager_h

#include "CommandManagerBase.h"

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

class CommandManager : public CommandManagerBase {
public:
	CommandManager(int instance_id) : CommandManagerBase(instance_id) {}
	~CommandManager(){}
private:
	//strategy::control::IControlStrategy* strategy_;
};


} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // core_manager_CommandManager_h
