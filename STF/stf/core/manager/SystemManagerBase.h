/**
 * @file   SystemManagerBase.h
 * @brief  条件判定や異常対応を行う機能マネージャ基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_manager_SystemManagerBase_h
#define stf_core_manager_SystemManagerBase_h

#include "ManagerBase.h"
#include "../../datatype/List.h"
#include "../event/Event.h"
#include "../event/SubjectBase.h"
#include "../../util/loki/TypeManip.h"

namespace stf {
namespace core {
namespace mode {
class ModeBase;
}
namespace functor {
class IFunctor;
template<class T> class IUnAryFunctor;
}
namespace datapool {
template<class T>class Tuple;
}
namespace manager {

//! 条件判定や異常対応を行う機能マネージャ基底クラス．
/*! 
	ユーザーはこのクラスを書き換えることが許可されない．
	機能マネージャの振る舞いをカスタマイズしたい場合，派生クラス側で仮想関数を実装する（Generation-Gapパターン）．
*/
class SystemManagerBase : public ManagerBase, virtual public event::Observer<event::ModeChangeEvent> {
public:	
	typedef functor::IFunctor HotSpot;
	typedef Loki::Type2Type<functor::IFunctor> SpotType;

	SystemManagerBase(int instance_id) : ManagerBase(instance_id, "SystemManager"), func_(0) {}
	virtual ~SystemManagerBase(){}
    virtual void run();
	virtual bool runnable() const { return true; };
	virtual void notify(const mode::ModeBase* value);
protected:
	const datatype::List<HotSpot>* func_;
};

} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_manager_SystemManagerBase_h
