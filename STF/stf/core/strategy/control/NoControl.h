/**
 * @file   NoControl.h
 * @brief  制御を行わない制御ブロック．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_control_NoControl_h
#define stf_core_strategy_control_NoControl_h

#include "../StrategyBase.h"
#include "../../devicedriver/IOPort.h"

namespace stf {
namespace datatype {
class Time;
}
namespace core {
namespace strategy {
namespace control {

//! 制御を行わない制御ブロック．
/*! */
class NoControl : public StrategyBase, public devicedriver::OutputPort<datatype::StaticVector<3>>{
public:
	NoControl(int instance_id) : StrategyBase(instance_id, "NoControl"){}
	~NoControl(){}
	virtual const datatype::StaticVector<3>& get_in_bodyframe(const datatype::Time& t){
		return this->value_b_;
	}//何もしない
};

} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_strategy_control_NoControl_h
