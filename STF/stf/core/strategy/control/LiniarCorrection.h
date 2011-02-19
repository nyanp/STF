#ifndef stf_core_strategy_control_LiniarCorrection_h
#define stf_core_strategy_control_LiniarCorrection_h
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

// TをaT+bに変換して出力する制御ブロック
template<class T>
class LiniarCorrection : public devicedriver::InputPorts< TYPELIST_1(T) >, 
		public devicedriver::OutputPorts < TYPELIST_1(T) > ,
		public StrategyBase
{
public:
	LiniarCorrection(int instance_id, double scale_factor) : sf_(scale_factor), StrategyBase(instance_id, "LiniarCorrection"){}
	LiniarCorrection(int instance_id, double scale_factor, T offset): sf_(scale_factor), offset_(offset), StrategyBase(instance_id, "LiniarCorrection"){}
	LiniarCorrection(int instance_id,
		double scale_factor,
		double offset,
		devicedriver::OutputPort<T>* target_source, 
		devicedriver::InputPort<T>* target_out) : sf_(scale_factor), offset_(offset)
	{
		 this->connectSource<0>(target_source);
		 if(target_out != 0) target_out->connectSource_(this);
	}
	~LiniarCorrection(){}

	virtual void do_compute(const datatype::Time& t){
		if(t > this->last_update_){
			util::cout << "compute: LiniarCorrection" << util::endl;
			this->value_b_ =  sf_ * this->source<0,T>().getValueInBodyFrame(t) + offset_;
			this->last_update_ = t;
		}
	}
private:
	double sf_;
	T offset_;

};




} /* End of namespace stf::core::mode::strategy::control */
} /* End of namespace stf::core::mode::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_mode_storategy_control_LiniarCorrection_h
