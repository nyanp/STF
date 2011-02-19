/**
 * @file   TorqueCombining.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_control_TorqueCombining_h
#define stf_core_strategy_control_TorqueCombining_h
#include <assert.h>
#include "IControlStrategy.h"
#include "../../devicedriver/IOPort.h"
#include "../../manager/ControlManager.h"
#include "../StrategyBase.h"
#include "../../../datatype/EulerAngle.h"
#include "../../../datatype/StaticVector.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {

//3つのトルクを単純加算で合成する制御ブロック．
class TorqueCombining : public devicedriver::InputPorts< TYPELIST_3(datatype::StaticVector<3>, datatype::StaticVector<3>, datatype::StaticVector<3>) >, 
		public devicedriver::OutputPorts < TYPELIST_1(datatype::StaticVector<3>) > ,
		public StrategyBase
{
public:
    TorqueCombining(int instance_id);
	TorqueCombining(int instance_id,

		devicedriver::OutputPort<datatype::StaticVector<3>>* source_1, 
		devicedriver::OutputPort<datatype::StaticVector<3>>* source_2,
		devicedriver::OutputPort<datatype::StaticVector<3>>* source_3,
		devicedriver::InputPort<datatype::StaticVector<3>>* torque_out);
	~TorqueCombining(){}
	virtual void do_compute(const datatype::Time& t);
protected:

};



} /* End of namespace stf::core::mode::strategy::control */
} /* End of namespace stf::core::mode::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_mode_storategy_control_TorqueCombining_h
