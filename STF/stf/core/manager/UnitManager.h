/**
 * @file   UnitManager.h
 * @brief  機器の定期データ取得・更新を行う機能マネージャ．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_manager_UnitManager_h
#define stf_core_manager_UnitManager_h

#include "UnitManagerBase.h"

namespace stf {
namespace core {
namespace manager {

//! 機器の定期データ取得・更新を行う機能マネージャ．
/*! 
	Generation-GapパターンによってBaseから派生しており，デフォルトでは実装を持たない．
	そのため，フレームワークからインスタンス化されると，仮想関数の機構によってBaseのインスタンスと殆ど同様に振る舞う．
	ユーザーはBaseクラスの実装を変更する代わりに，この派生クラス側で必要に応じて仮想関数を宣言し，
	機能マネージャの振る舞いをカスタマイズすることができる．
*/
class UnitManager : public UnitManagerBase 
{
public:
	UnitManager(int instance_id) : UnitManagerBase(instance_id){}
	~UnitManager(){}
};

} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_manager_UnitManager_h