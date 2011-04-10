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
#include "../../app/Default.h"

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
class Mode;

//! モードに依存したアルゴリズムを保持するクラス．
/*! 
	@tparam T リスト化されるアルゴリズムの型．
*/
template<class T> class HotSpotList {
public:
	HotSpotList(){}
	virtual ~HotSpotList(){}
	virtual const datatype::List<T>* get_list(Loki::Type2Type<T>) const{ 
		return &value_;
	};

	void add_list_(T& value) {
		this->value_.push_back(value);
	}
	datatype::List<T> value_;
};


//! モードに依存したアルゴリズムを纏め，インターフェースを提供するクラス．
/*! 
*/
struct StrategyHolder : 
	public Loki::GenScatterHierarchy<typename app::Default::modehotspot, HotSpotList>
{	
	template<class T>
	void add_list(T* value){
		(static_cast<HotSpotList<T>& >(*this).add_list_(*value));
	}

	template<class T>
	const datatype::List<T>* get_list(Loki::Type2Type<T>) const{
		return &(static_cast<const HotSpotList<T>& >(*this).value_);
	}
};

} /* End of namespace stf::core::mode */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_mode_ModeHotSpot_h