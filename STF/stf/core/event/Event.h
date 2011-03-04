/**
 * @file   Event.h
 * @brief  全イベントの基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_event_Event_h
#define stf_core_event_Event_h

#include "../../datatype/String.h"

namespace stf {
namespace core {
namespace mode {
class ModeBase;
}
namespace event {

enum EventType {
	NoEvent,
	Unknowmn,
	ModeChange,
	Switch,
};

class EventBase {
public:

};

struct ModeChangeEvent : public EventBase {
	typedef mode::ModeBase Target;
	enum { EventId = ModeChange };
	static int get_eventid(){ return EventId; }
};

struct SwitchEvent : public EventBase {
	typedef mode::ModeBase Target;
	enum { EventId = Switch };
	static int get_eventid(){ return EventId; }
};

} /* End of namespace stf::core::event */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_event_Event_h
