/**
 * @file   SubjectBase.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_event_Subject_h
#define stf_core_event_Subject_h
#include <iostream>
#include "../../datatype/List.h"
#include <vector>

namespace stf {
namespace core {
namespace event {

template <class Evt>
class Observer {
public:
	Observer();
	virtual ~Observer(){}
	virtual void notify(const typename Evt::Target* value) = 0;
private:
};

template <class Evt>
class Reporter {
public:
	Reporter(){}
	~Reporter(){}
	virtual int check(typename Evt::Target* value) = 0;
private:	
};

template <class Evt>
class SubjectBase {
public:
	typedef Evt Hold;//datapool—p
	SubjectBase() {}
	~SubjectBase(){}
	static void add_reporter(Reporter<Evt>* obs){
		reporters_.add(*obs);
	}
	static void clear_reporter(){
		reporters_.clear();
	}
	static void add_listener(Observer<Evt>* obs){
		observers_.add(*obs);
	}
	static void clear_listener(){
		observers_.clear();
	}
	void check();
	void notify_observers(const typename Evt::Target& p);
private:
	static Evt event_;
	static datatype::List< Reporter<Evt> > reporters_;
	static datatype::List< Observer<Evt> > observers_;
};

template <class Evt> datatype::List< Reporter<Evt> > SubjectBase<Evt>::reporters_;
template <class Evt> datatype::List< Observer<Evt> > SubjectBase<Evt>::observers_;
template <class Evt> Evt SubjectBase<Evt>::event_;


} /* End of namespace stf::core::event */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_event_Subject_h
