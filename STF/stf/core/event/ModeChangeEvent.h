/**
 * @file   ModeChangeEvent.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_event_ModeChangeEvent_h
#define stf_core_event_ModeChangeEvent_h
#include "EventBase.h"
#include "../../datatype/Time.h"
#include "../../InstanceID.h"

namespace stf {
namespace core {
namespace manager {
class ModeManagerBase;
}
namespace mode {
class ModeBase;
}

namespace event {

class ModeChangeEvent : public EventBase{
public:
	typedef manager::ModeManagerBase SubjectClass; 
	typedef mode::ModeBase Target;
	ModeChangeEvent() : EventBase("ModeChangeEvent") {}
	virtual ~ModeChangeEvent(){}
	virtual int instance_id(){ return 0; }// TBD
private:

};

} /* End of namespace stf::core::event */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_event_ModeChangeEvent_h
