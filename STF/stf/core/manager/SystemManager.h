/**
 * @file   SystemManager.h
 * @brief  条件判定や異常対応を行う機能マネージャ．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_manager_SystemManager_h
#define stf_core_manager_SystemManager_h

#include "SystemManagerBase.h"

namespace stf {
namespace core {
namespace manager {

//! 条件判定や異常対応を行う機能マネージャ．
/*! 
	Generation-GapパターンによってBaseから派生しており，デフォルトでは実装を持たない．
	そのため，フレームワークからインスタンス化されると，仮想関数の機構によってBaseのインスタンスと殆ど同様に振る舞う．
	ユーザーはBaseクラスの実装を変更する代わりに，この派生クラス側で必要に応じて仮想関数を宣言し，
	機能マネージャの振る舞いをカスタマイズすることができる．
*/
class SystemManager : public SystemManagerBase { 
public:
	SystemManager(int instance_id) : SystemManagerBase(instance_id){}
	~SystemManager(){}
};

} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif //stf_core_manager_SystemManager_h
