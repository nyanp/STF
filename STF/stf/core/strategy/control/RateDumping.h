/**
 * @file   RateDumping.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_control_RateDumping_h
#define stf_core_strategy_control_RateDumping_h
#include <assert.h>
#include "../../../util/Ostream.h"
#include "../StrategyBase.h"
#include "../../devicedriver/IOPort.h"
#include "../../../datatype/StaticVector.h"

namespace stf {
namespace datatype {
class Time;
}
namespace core {
namespace strategy {
namespace control {

class RateDumping : public StrategyBase,
	public devicedriver::InputPorts< TYPELIST_1(datatype::StaticVector<3>)>,
	public devicedriver::OutputPorts< TYPELIST_1(datatype::StaticVector<3>)>{
public:
    RateDumping(int instance_id, double kp, double ki, double kd, double dt);
	RateDumping(int instance_id, double kp, double ki, double kd, double dt,
		devicedriver::OutputPort<datatype::StaticVector<3>>* omega_source,
		devicedriver::InputPort<datatype::StaticVector<3>>* torque_target );

	virtual ~RateDumping(){}
	virtual void do_compute(const datatype::Time& t);
protected:
    datatype::StaticVector<3> computeTorque_(const datatype::StaticVector<3>& input);
    RateDumping();
    double ki_;
    double kd_;
    double kp_;
	double dt_;
	datatype::StaticVector<3> omega_before_;
    datatype::StaticVector<3> omega_total_;
};


} /* End of namespace core::mode::strategy::control */
} /* End of namespace core::mode::strategy */
} /* End of namespace core::mode */
} /* End of namespace core */

#endif // aocs_strategy_control_RateDumping_h
