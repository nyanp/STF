/**
 * @file   FirstOrderCorrection.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_control_FirstOrderCorrection_h
#define stf_core_strategy_control_FirstOrderCorrection_h
#include <assert.h>
#include "IControlStrategy.h"
#include "../../devicedriver/IOPort.h"
#include "../../manager/ControlManager.h"
#include "../StrategyBase.h"

#include "../../../util/Ostream.h"

#include "../../../datatype/StaticVector.h"
#include "../../../datatype/Quaternion.h"
#include "../../../datatype/EulerAngle.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {

// TをT*Uに変換して出力する制御ブロック
template<class T,class U>
class FirstOrderCorrection : public devicedriver::InputPorts< TYPELIST_2(T, U) >, 
		public devicedriver::OutputPorts < TYPELIST_1(T) > ,
		public StrategyBase
{
public:
	FirstOrderCorrection(int instance_id) {}
	FirstOrderCorrection(int instance_id,
		devicedriver::OutputPort<T>* target_source, 
		devicedriver::OutputPort<U>* corrector_source, 
		devicedriver::InputPort<T>* target_out) 
	{
		 this->connectSource<0>(target_source);
		 this->connectSource<1>(corrector_source);
		 if(target_out != 0) target_out->connectSource_(this);
	}
	~FirstOrderCorrection(){}

	virtual void do_compute(const datatype::Time& t){
		if(t > this->last_update_){
			util::cout << "compute: FirstOrderCorrection" << util::endl;
			this->value_b_ =  this->source<0,T>().getValueInBodyFrame(t) * this->source<1,U>().getValueInBodyFrame(t);
			this->last_update_ = t;
		}
	}
protected:
};




} /* End of namespace stf::core::mode::strategy::control */
} /* End of namespace stf::core::mode::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_mode_storategy_control_FirstOrderCorrection_h
