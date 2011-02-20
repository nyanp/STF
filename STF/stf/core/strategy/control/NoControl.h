/**
 * @file   NoControl.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_control_NoControl_h
#define stf_core_strategy_control_NoControl_h

#include "IControlStrategy.h"
#include "../StrategyBase.h"
#include "../../../util/Null.h"
#include "../../devicedriver/IOPort.h"

namespace stf {
namespace datatype {
class Time;
}
namespace core {
namespace strategy {
namespace control {

//êßå‰ÇµÇ»Ç¢
	class NoControl : public StrategyBase, public devicedriver::OutputPort<datatype::StaticVector<3>>{
public:
	NoControl(int instance_id) : StrategyBase(instance_id, "NoControl"){}
	~NoControl(){}
	virtual const datatype::StaticVector<3>& get_in_bodyframe(const datatype::Time& t){
		return this->value_b_;
	}//âΩÇ‡ÇµÇ»Ç¢
private:

};

} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_strategy_control_NoControl_h
