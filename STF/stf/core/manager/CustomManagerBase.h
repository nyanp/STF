/**
 * @file   CustomManagerBase.h
 * @brief  カスタムコードの実行を行う機能マネージャ基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_manager_CustomManagerBase_h
#define stf_core_manager_CustomManagerBase_h

#include "ManagerBase.h"

namespace stf {
namespace core {
namespace manager {

//! カスタムコードの実行を行う機能マネージャ基底クラス．
/*! 
	ユーザーはこのクラスを書き換えることが許可されない．
	機能マネージャの振る舞いをカスタマイズしたい場合，派生クラス側で仮想関数を実装する（Generation-Gapパターン）．
*/
class CustomManagerBase : public ManagerBase
{
public:
	CustomManagerBase(int instance_id) : ManagerBase(instance_id, "CustomManager"){}
	virtual ~CustomManagerBase(){}
protected:

};

} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_manager_CustomManagerBase_h