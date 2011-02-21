/**
 * @file   SubjectBase.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "SubjectBase.h"
#include "ModeChangeEvent.h"
#include "../manager/ModeManagerBase.h"
#include "../datapool/Datapool.h"

namespace stf {
namespace core {
namespace event {

template class SubjectBase<ModeChangeEvent>;
template class Observer<ModeChangeEvent>;

template <class Evt>
Observer<Evt>::Observer(){
	Evt::SubjectClass::add_listener(this);
}

template <class Evt>
void SubjectBase<Evt>::check(){
	datatype::List< Reporter<Evt> >::iterator it = reporters_.begin();
	typename Evt::Target* t = 0;
	typename Evt::Target* next = 0;
	int priority = 0;
	for( ; it != reporters_.end() ; ++it ){
		int i = (*it).check(t);
		if(t != 0 && i > priority){
			priority = i;
			next = t;
		}
	}
	if(next != 0) notify_observers(*next);
}

template <class Evt>
void SubjectBase<Evt>::notify_observers(const typename Evt::Target& p){
	datatype::List< Observer<Evt> >::iterator it = observers_.begin();
	for( ; it != observers_.end() ; ++it ){
		(*it).notify(&p);
	}
	//Global<ENV>::get_eventdatapool().set<SubjectBase<Evt>>(this->event_.instance_id(),this->event_);
}

} /* End of namespace stf::core::event */
} /* End of namespace stf::core */
} /* End of namespace stf */

