/**
 * @file   TelemetryManager.h
 * @brief  テレメトリ生成を行う機能マネージャ．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_manager_TelemetryManager_h
#define stf_core_manager_TelemetryManager_h

#include "TelemetryManagerBase.h"

namespace stf {
namespace core {
namespace manager {

//! テレメトリ生成を行う機能マネージャ．
/*! 
	Generation-GapパターンによってBaseから派生しており，デフォルトでは実装を持たない．
	そのため，フレームワークからインスタンス化されると，仮想関数の機構によってBaseのインスタンスと殆ど同様に振る舞う．
	ユーザーはBaseクラスの実装を変更する代わりに，この派生クラス側で必要に応じて仮想関数を宣言し，
	機能マネージャの振る舞いをカスタマイズすることができる．
*/
class TelemetryManager : public TelemetryManagerBase { 
public:
	TelemetryManager(int instance_id) : TelemetryManagerBase(instance_id){}
	~TelemetryManager(){}
};

} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif //stf_core_manager_TelemetryManager_h