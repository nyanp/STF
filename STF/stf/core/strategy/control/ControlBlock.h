/**
 * @file   ControlBlock.h
 * @brief  制御ネットワークのラッパーとなるスーパーブロック．
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
#include "../../../datatype/List.h"

namespace stf {
namespace core {
namespace devicedriver {
template<class T, class U, class ENV> class AOCSComponent;
}
namespace strategy {
namespace control {

//! 制御ネットワークのラッパーとなるスーパーブロック．
/*! 
	相互に接続された制御ブロック群をControlManagerが起動するときの
	インターフェースとなる．最終段のアクチュエータと，アクチュエータに直接接続される制御ブロックへの
	ポインタを保持しており，制御ブロックを起動して得られた値をアクチュエータに順次渡す．
*/
class ControlBlock : public StrategyBase, virtual public IControlStrategy
{
public:
	ControlBlock(int instance_id) : StrategyBase(instance_id, "ControlBlock") {}

	template<class T>
	ControlBlock(int instance_id, devicedriver::OutputPort<typename T::Hold>* torque_source, T* torque_target)
		: StrategyBase(instance_id, "ControlBlock")
	{
		set_actuator<T>(torque_target, torque_source);
	}

	virtual void compute_torque(const datatype::Time& t);
	template<class T> void set_actuator(T* torque_target, devicedriver::OutputPort<typename T::Hold>* torque_source);
private:
	//! アクチュエータ・制御ブロックのペアを組み合わせるための内部抽象インターフェース．
	struct ControlImpl {
		virtual void set_torque(const datatype::Time& t) = 0;
	};

	//! アクチュエータ・制御ブロックのペアを組み合わせるための内部クラス．
	template<class Actuator>
	struct ControlInputPort : public ControlImpl{
		virtual void set_torque(const datatype::Time& t){
			if(holderport_ != 0 && output_ != 0)
			 output_->set_torque(holderport_->get_value(t));
		}

		virtual void connect_holder_(devicedriver::OutputPort<typename Actuator::Hold>* holder){
			holderport_ = holder;
		}

		virtual void connect_actuator_(Actuator* act) {
			output_ = act;
		}

		devicedriver::OutputPort<typename Actuator::Hold>* holderport_;
		Actuator* output_;
	};

	datatype::List< ControlImpl > controllers_;
};

inline void ControlBlock::compute_torque(const datatype::Time& t){
	if(this->is_enabled_){
		datatype::List< ControlImpl >::iterator it = controllers_.begin();
		while( it != controllers_.end() ){
			(*it).set_torque(t);
			++it;
		}
	}
}

template<class T> void ControlBlock::set_actuator(T* torque_target, devicedriver::OutputPort<typename T::Hold>* torque_source){
	ControlInputPort<T>* tuple = new ControlInputPort<T>;
	tuple->connect_actuator_(torque_target);
	tuple->connect_holder_(torque_source);
	this->controllers_.add(*tuple);
}

} /* End of namespace stf::core::mode::strategy::control */
} /* End of namespace stf::core::mode::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_mode_storategy_control_ControlBlock_h
