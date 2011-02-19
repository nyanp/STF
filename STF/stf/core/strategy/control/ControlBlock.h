/**
 * @file   ControlBlock.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_control_ControlBlock_h
#define stf_core_strategy_control_ControlBlock_h
#include <assert.h>
#include "IControlStrategy.h"
#include "../StrategyBase.h"
#include "../../devicedriver/IOPort.h"

namespace stf {
namespace core {
namespace devicedriver {
template<class T, class U, class ENV> class AOCSComponent;
}
namespace strategy {
namespace control {

struct ControlImpl {
	virtual void setTorque(const datatype::Time& t) = 0;
};

template<class Actuator>
struct ControlInputPort : public ControlImpl{
	devicedriver::OutputPort<typename Actuator::Hold>* holderport_;
	Actuator* output_;
	virtual void setTorque(const datatype::Time& t){
		if(holderport_ != 0 && output_ != 0)
		 output_->setValueInBodyFrame(holderport_->getValueInBodyFrame(t));
	}
	virtual void connectHolder_(devicedriver::OutputPort<typename Actuator::Hold>* holder) { holderport_ = holder; }
	virtual void connectActuator_(Actuator* act) { output_ = act; }
};


class ControlBlock : public StrategyBase, virtual public IControlStrategy
{
public:
	ControlBlock(int instance_id) : StrategyBase(instance_id, "ControlBlock") {}
	template<class T>
	ControlBlock(int instance_id,devicedriver::OutputPort<typename T::Hold>* torque_source, T* torque_target)
		: StrategyBase(instance_id, "ControlBlock")
	{
		setActuator<T>(torque_target,torque_source);
	}

	virtual void computeTorque(const datatype::Time& t){
		if(this->is_enabled_){
			datatype::List< ControlImpl >::iterator it = controllers_.begin();
			while( it != controllers_.end() ){
				(*it).setTorque(t);
				++it;
			}
		}
	}

	template<class T> void setActuator(T* torque_target, devicedriver::OutputPort<typename T::Target>* torque_source){
		ControlInputPort<T>* tuple = new ControlInputPort<T>;
		tuple->connectActuator_(torque_target);
		tuple->connectHolder_(torque_source);
		this->controllers_.add(*tuple);
	}
private:
	datatype::List< ControlImpl > controllers_;
};

} /* End of namespace stf::core::mode::strategy::control */
} /* End of namespace stf::core::mode::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_mode_storategy_control_ControlBlock_h
