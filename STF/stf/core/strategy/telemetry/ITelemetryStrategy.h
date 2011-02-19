/**
 * @file   ITelemetryStrategy.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_telemetry_ITelemetryStrategy_h
#define stf_core_strategy_telemetry_ITelemetryStrategy_h

#include "../StrategyBase.h"


namespace stf {
namespace interface {
class Iterator;
}
namespace core {
namespace strategy {
namespace telemetry {


class ITelemetryStrategy{
public:
	virtual void write_to_telemetry() = 0;
	virtual void add_tmlist(interface::Iterator* tm) = 0;
	virtual void remove_tmlist(interface::Iterator* tm) = 0;
	virtual ~ITelemetryStrategy(){}
protected:

};

} /* End of namespace stf::core::strategy::telemetry */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_strategy_telemetry_ITelemetryStrategy_h