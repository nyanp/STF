/**
 * @file   CustomManager.h
 * @brief  カスタムコードの実行を行う機能マネージャ．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_manager_CustomManager_h
#define stf_core_manager_CustomManager_h

#include "CustomManagerBase.h"

namespace stf {
namespace core {
namespace manager {

//! カスタムコードの実行を行う機能マネージャ．
/*! 
	Generation-GapパターンによってBaseから派生しており，デフォルトでは実装を持たない．
	そのため，フレームワークからインスタンス化されると，仮想関数の機構によってBaseのインスタンスと殆ど同様に振る舞う．
	ユーザーはBaseクラスの実装を変更する代わりに，この派生クラス側で必要に応じて仮想関数を宣言し，
	機能マネージャの振る舞いをカスタマイズすることができる．
*/
class CustomManager : public CustomManagerBase
{
public:
	CustomManager(int instance_id) : CustomManagerBase(instance_id){}
	~CustomManager(){}
	virtual void run();
	virtual bool runnable();
protected:
};

} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_manager_CustomManager_h