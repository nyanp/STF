/**
 * @file   TelemetryManagerBase.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_manager_TelemetryManagerBase_h
#define stf_core_manager_TelemetryManagerBase_h

#include "ManagerBase.h"
#include "../../datatype/List.h"
#include "../event/ModeChangeEvent.h"
#include "../event/SubjectBase.h"
#include "../../util/loki/TypeManip.h"

namespace stf {
namespace core {
namespace strategy {
namespace telemetry {
class ITelemetryStrategy;
}
}
namespace datapool {
template<class T>class Tuple;
}
namespace manager {

class TelemetryManagerBase : public ManagerBase, virtual public event::Observer<event::ModeChangeEvent> {
public:	
	typedef core::strategy::telemetry::ITelemetryStrategy HotSpot;
	typedef Loki::Type2Type<core::strategy::telemetry::ITelemetryStrategy> SpotType;

	TelemetryManagerBase(int instance_id) : ManagerBase(instance_id, "TelemetryManager"), telem_(0) {}
	virtual ~TelemetryManagerBase(){}
    virtual void run();
	virtual bool runnable() const { return true; };
	virtual void notify(const mode::ModeBase* value);
    //interface::ITelemetryStoragable *storage_;
protected:
	const datatype::List<HotSpot>* telem_;
    //std::vector< interface::ITelemetable* > telem_list_;
	//datatype::List<>
};

} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_manager_TelemetryManagerBase_h
