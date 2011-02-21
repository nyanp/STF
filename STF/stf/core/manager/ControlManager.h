/**
 * @file   ControlManager.h
 * @brief  制御ブロックの実行を行う機能マネージャ．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef core_manager_ControlManager_h
#define core_manager_ControlManager_h

#include "ControlManagerBase.h"

namespace stf {
namespace core {
namespace mode {
namespace strategy {
namespace control {
class IControlStrategy;
}
}
}

namespace manager {

//! 制御ブロックの実行を行う機能マネージャ．
/*! 
	Generation-GapパターンによってBaseから派生しており，デフォルトでは実装を持たない．
	そのため，フレームワークからインスタンス化されると，仮想関数の機構によってBaseのインスタンスと殆ど同様に振る舞う．
	ユーザーはBaseクラスの実装を変更する代わりに，この派生クラス側で必要に応じて仮想関数を宣言し，
	機能マネージャの振る舞いをカスタマイズすることができる．
*/
class ControlManager : public ControlManagerBase {
public:
	ControlManager(int instance_id) : ControlManagerBase(instance_id) {}
	~ControlManager(){}
private:
	//strategy::control::IControlStrategy* strategy_;
};


} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // core_manager_ControlManager_h
