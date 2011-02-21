/**
 * @file   SubjectBase.h
 * @brief  Observerパターンの構成テンプレートクラス群．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_event_Subject_h
#define stf_core_event_Subject_h

#include "../../datatype/List.h"

namespace stf {
namespace core {
namespace event {

//! イベントオブザーバ．
/*! 
	通常のObserverパターンと異なり，コンストラクタでSubjectクラスに登録されるので，
	イベントオブザーバとしたいクラスは，このクラスを継承してnotifyを実装し，インスタンス化するだけでよい．
	@tparam Evt 観測するイベント．
*/
template <class Evt>
class Observer {
public:
	Observer();
	virtual ~Observer(){}
	virtual void notify(const typename Evt::Target* value) = 0;
private:
};

//! イベントレポータ．
/*! 
	check関数によって，イベントのSubjectにイベント発生を報告する．
	@tparam Evt 観測するイベント．
*/
template <class Evt>
class Reporter {
public:
	Reporter(){}
	~Reporter(){}
	//! イベントの発生を監視する．
	/*!
		@retval イベントの優先度．0だとイベント発生なし．0以上の値だと，そのイベントの優先度を示す．
	*/
	virtual int check(typename Evt::Target* value) = 0;
private:	
};

//! イベントSubject．
/*! 
	observerパターンにおいて，各observerに通知する責任を負う．オブザーバがstaticなリストとして定義されているので，
	基本的に単一のイベントに対するsubjectは複数有ってはならない．
	@tparam Evt 観測するイベント．
*/
template <class Evt>
class SubjectBase {
public:
	typedef Evt Hold;//datapool用
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
