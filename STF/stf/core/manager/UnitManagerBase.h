/**
 * @file   UnitManagerBase.h
 * @brief  機器の定期データ取得・更新を行う機能マネージャ基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_manager_UnitManagerBase_h
#define stf_core_manager_UnitManagerBase_h

#include "ManagerBase.h"
#include "../../datatype/List.h"
#include "../event/Event.h"
#include "../event/SubjectBase.h"
#include "../../util/loki/TypeManip.h"

namespace stf {
namespace core {
namespace devicedriver {
class IDataUpdatable;
}
namespace manager {

//! 機器の定期データ取得・更新を行う機能マネージャ基底クラス．
/*! 
	ユーザーはこのクラスを書き換えることが許可されない．
	機能マネージャの振る舞いをカスタマイズしたい場合，派生クラス側で仮想関数を実装する（Generation-Gapパターン）．
*/
class UnitManagerBase : public ManagerBase, virtual public event::Observer<event::ModeChangeEvent>
{
public:
	typedef core::devicedriver::IDataUpdatable HotSpot;
	typedef Loki::Type2Type<core::devicedriver::IDataUpdatable> SpotType;

	UnitManagerBase(int instance_id) : ManagerBase(instance_id, "UnitManager"), unit_list_(0) {}
	virtual ~UnitManagerBase(){}

    void run();
	bool runnable() const { return true; }
	virtual void notify(const mode::Mode* value);
protected:
    const datatype::List<HotSpot>* unit_list_;
};

} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_manager_UnitManagerBase_h