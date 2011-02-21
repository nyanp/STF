/**
 * @file   EventBase.h
 * @brief  全イベントの基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_event_EventBase_h
#define stf_core_event_EventBase_h

#include "../../datatype/String.h"

namespace stf {
namespace core {
namespace event {

//! 全イベントの基底クラス．
/*! */
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
};

} /* End of namespace stf::core::event */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_event_EventBase_h
