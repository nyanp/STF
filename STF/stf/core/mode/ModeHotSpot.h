/**
 * @file   ModeHotSpot.h
 * @brief  モード固有のアルゴリズムをタイプリスト形式で纏めるインターフェース．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_mode_ModeHotSpot_h
#define stf_core_mode_ModeHotSpot_h

#include "../../RootObject.h"
#include "../../datatype/List.h"
#include "../../util/loki/HierarchyGenerators.h"
#include "../../util/loki/TypeManip.h"

namespace stf {
namespace core {
namespace functor {
class IFunctor;
template<class T> class IUnAryFunctor;
}
namespace devicedriver {
class ISwitchable;
class IDataUpdatable;
}
namespace strategy {
namespace telemetry {
class ITelemetryStrategy;
}
namespace control {
class IControlStrategy;
class ControlBlock;
}
}
namespace mode {
class ModeBase;

//! モードに依存したアルゴリズムを保持するクラス．
/*! 
	@params T リスト化されるアルゴリズムの型．
*/
template<class T> class HotSpotList {
public:
	HotSpotList(){}
	virtual ~HotSpotList(){}
	virtual const datatype::List<T>* get_list(Loki::Type2Type<T>) const{ 
		return &value_;
	};
	virtual void add_list_(T& value) {
		this->value_.push_back(value);
	}
	datatype::List<T> value_;
};



//! モードに依存したアルゴリズムを纏め，インターフェースを提供するクラス．
/*! 
	@todo add_list, getlistをFieldヘルパでまとめる．ユーザから任意個のHotSpotを追加で与えられるようなパラメータを用意する
*/
struct StrategyHolder : 
	public Loki::GenScatterHierarchy<
	TYPELIST_5(devicedriver::ISwitchable,
	devicedriver::IDataUpdatable, 
	functor::IFunctor, 
	core::strategy::telemetry::ITelemetryStrategy,
	core::strategy::control::IControlStrategy), HotSpotList>
{
	void add_list(devicedriver::ISwitchable* value){
		(static_cast<HotSpotList<devicedriver::ISwitchable>& >(*this).add_list_(*value));
	}
	void add_list(devicedriver::IDataUpdatable* value){
		(static_cast<HotSpotList<devicedriver::IDataUpdatable>& >(*this).add_list_(*value));
	}
	void add_list(stf::core::functor::IFunctor* value){
		(static_cast<HotSpotList<stf::core::functor::IFunctor>& >(*this).add_list_(*value));
	}
	void add_list(stf::core::strategy::control::IControlStrategy* value){
		(static_cast<HotSpotList<stf::core::strategy::control::IControlStrategy>& >(*this).add_list_(*value));
	}
	void add_list(stf::core::strategy::telemetry::ITelemetryStrategy* value){
		(static_cast<HotSpotList<stf::core::strategy::telemetry::ITelemetryStrategy>& >(*this).add_list_(*value));
	}

	virtual const datatype::List<devicedriver::ISwitchable>* getlist(Loki::Type2Type<devicedriver::ISwitchable>) const{
		return &(static_cast<const HotSpotList<stf::core::devicedriver::ISwitchable>& >(*this).value_);
	}
	virtual const datatype::List<devicedriver::IDataUpdatable>* getlist(Loki::Type2Type<devicedriver::IDataUpdatable>) const{
		return &(static_cast<const HotSpotList<stf::core::devicedriver::IDataUpdatable>& >(*this).value_);
	}
	virtual const datatype::List<stf::core::functor::IFunctor>* getlist(Loki::Type2Type<functor::IFunctor>) const{
		return &(static_cast<const HotSpotList<functor::IFunctor>& >(*this).value_);
	}
	virtual const datatype::List<stf::core::strategy::telemetry::ITelemetryStrategy>* getlist(Loki::Type2Type<stf::core::strategy::telemetry::ITelemetryStrategy>) const{
		return &(static_cast<const HotSpotList<stf::core::strategy::telemetry::ITelemetryStrategy>& >(*this).value_);
	}
	virtual const datatype::List<stf::core::strategy::control::IControlStrategy>* getlist(Loki::Type2Type<stf::core::strategy::control::IControlStrategy>) const{
		return &(static_cast<const HotSpotList<stf::core::strategy::control::IControlStrategy>& >(*this).value_);
	}
};

} /* End of namespace stf::core::mode */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_mode_ModeHotSpot_h