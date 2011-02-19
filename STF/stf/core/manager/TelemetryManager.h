#ifndef stf_core_manager_TelemetryManager_h
#define stf_core_manager_TelemetryManager_h

#include "TelemetryManagerBase.h"

namespace stf {
namespace core {
namespace manager {

class TelemetryManager : public TelemetryManagerBase { 
public:
	TelemetryManager(int instance_id) : TelemetryManagerBase(instance_id){}
	~TelemetryManager(){}
};

} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif //stf_core_manager_TelemetryManager_h