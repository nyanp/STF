/**
 * @file   ControlManagerBase.h
 * @brief  制御ブロックの実行を行う機能マネージャ基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef core_manager_ControlManagerBase_h
#define core_manager_ControlManagerBase_h

#include "ManagerBase.h"
#include "../../datatype/List.h"
#include "../event/Event.h"
#include "../event/SubjectBase.h"
#include "../../util/loki/TypeManip.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {
class IControlStrategy;
}
}
namespace mode {
class ModeBase;
} /* End of namespace core::mode */
} /* End of namespace core */

namespace core {
namespace manager {

//! 制御ブロックの実行を行う機能マネージャ基底クラス．
/*! 
	ユーザーはこのクラスを書き換えることが許可されない．
	機能マネージャの振る舞いをカスタマイズしたい場合，派生クラス側で仮想関数を実装する（Generation-Gapパターン）．
*/
class ControlManagerBase : public ManagerBase, virtual public event::Observer<event::ModeChangeEvent>{
public:
	typedef core::strategy::control::IControlStrategy HotSpot;
	typedef Loki::Type2Type<HotSpot> SpotType;

	ControlManagerBase(int instance_id) : ManagerBase(instance_id, "ControlManager"), controller_(0) {}
	virtual ~ControlManagerBase(){};
    virtual void run();
	virtual bool runnable() const { return true; }
	virtual void notify(const mode::ModeBase* value);
protected:
    virtual void doControl(const datatype::Time&);
	const datatype::List<HotSpot>* controller_;
};


} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // core_manager_ControlManagerBase_h
