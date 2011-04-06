/**
 * @file   TelemetryManagerBase.h
 * @brief  テレメトリ生成を行う機能マネージャ基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_manager_TelemetryManagerBase_h
#define stf_core_manager_TelemetryManagerBase_h

#include "ManagerBase.h"
#include "../../datatype/List.h"
#include "../event/Event.h"
#include "../event/SubjectBase.h"
#include "../../util/loki/TypeManip.h"

namespace stf {
namespace core {
namespace strategy {
namespace telemetry {
class ITelemetryStrategy;
}
}
namespace datapool {
template<class T>class Tuple;
}
namespace manager {

//! テレメトリ生成を行う機能マネージャ基底クラス．
/*! 
	ユーザーはこのクラスを書き換えることが許可されない．
	機能マネージャの振る舞いをカスタマイズしたい場合，派生クラス側で仮想関数を実装する（Generation-Gapパターン）．
*/
class TelemetryManagerBase : public ManagerBase, virtual public event::Observer<event::ModeChangeEvent> {
public:	
	typedef core::strategy::telemetry::ITelemetryStrategy HotSpot;
	typedef Loki::Type2Type<core::strategy::telemetry::ITelemetryStrategy> SpotType;

	TelemetryManagerBase(int instance_id) : ManagerBase(instance_id, "TelemetryManager"), telem_(0) {}
	virtual ~TelemetryManagerBase(){}
    virtual void run();
	virtual bool runnable() const { return true; };
	virtual void notify(const mode::Mode* value);
protected:
	const datatype::List<HotSpot>* telem_;
};

} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_manager_TelemetryManagerBase_h
