/**
 * @file   Default.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.04.09
 */
#ifndef stf_app_Default_h
#define stf_app_Default_h

#include "../util/loki/Typelist.h"

namespace stf {

// Forward Decl
namespace datatype {
class String;
}
namespace core {
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

#define DEFAULT_MODE_HOTSPOT core::devicedriver::ISwitchable, core::devicedriver::IDataUpdatable, core::functor::IFunctor, core::strategy::telemetry::ITelemetryStrategy, core::strategy::control::IControlStrategy
namespace app {

struct Default {
	static const int year = 2005;
	static const int month = 1;
	static const int date = 30;
	static const double steptime = 0.01;
	typedef TYPELIST_5(DEFAULT_MODE_HOTSPOT) modehotspot;
	typedef datatype::String char_t;
};

}
}

#endif