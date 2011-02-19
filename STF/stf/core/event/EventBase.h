#ifndef stf_core_event_EventBase_h
#define stf_core_event_EventBase_h
#include <iostream>
#include "../../datatype/String.h"
#include "../../datatype/Time.h"

namespace stf {
namespace core {
namespace event {
//全イベントの基底クラス．
// T: イベント変数．
// Holder: イベントのSubjectとなるクラス．機能マネージャなどシングルトンでなければならない
class EventBase {
public:
	//typedef U SubjectClass; 
	//typedef T Target;
	EventBase(const datatype::String& name) : name_(name){}
	virtual ~EventBase(){}
	virtual int instance_id() = 0;
	virtual EventBase& operator=(const EventBase &rhs){
		this->name_ = rhs.name_;
		return *this;
	}
	virtual const datatype::String& name() const{ return name_; }
private:
	datatype::String name_;
	//datatype::Time time_;
};

} /* End of namespace stf::core::event */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_event_EventBase_h
