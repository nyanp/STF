/**
 * @file   NJ.h
 * @brief  アプリケーション固有のパラメータ宣言
 *
 * @author Taiga Nomi
 * @date   2011.04.09
 */
#ifndef stf_app_NJ_h
#define stf_app_NJ_h


#include "../../../util/loki/Typelist.h"
#include "../../../core/environment/Simulator.h"

namespace stf {

// Forward Decl
namespace datatype {
template<class T> class List;
class String;
}
namespace core {
namespace environment {
template<class App> class Simulator;
}
namespace functor {
class IFunctor;
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
}
}
}

namespace app {

struct NJ {
	static const int year;
	static const int month;
	static const int date;
	static const double steptime;

	typedef stf::core::environment::Simulator<NJ> ios_env;

	typedef TYPELIST_5(core::devicedriver::ISwitchable, 
			core::devicedriver::IDataUpdatable, 
			core::functor::IFunctor, 
			core::strategy::telemetry::ITelemetryStrategy, 
			core::strategy::control::IControlStrategy) modehotspot;

	typedef datatype::String char_t;

	template<typename T>
	struct list {
		typedef datatype::List<T> type;
	};
};

}
}

#endif