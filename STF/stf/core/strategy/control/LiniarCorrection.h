/**
 * @file   LiniarCorrection.h
 * @brief  TをaT+bに変換して出力する制御ブロック
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_control_LiniarCorrection_h
#define stf_core_strategy_control_LiniarCorrection_h
#include "../../../util/stfassert.h"
#include "../StrategyBase.h"
#include "../../devicedriver/IOPort.h"
#include "../../../util/Trace.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {

//! TをaT+bに変換して出力する制御ブロック．
/*! 
	@tparam T 変換対象の物理量．operator + (const T&, const T&)　および operator * (double, const T&)が実装されている必要がある
*/
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
		 this->connect_source<0>(target_source);
		 if(target_out != 0) target_out->connect_source_(this);
	}
	~LiniarCorrection(){}

	virtual void do_compute(const datatype::Time& t){
		if(t > this->last_update_){
			util::Trace trace(util::Trace::kControlBlock, name_);

			this->value_ =  sf_ * this->source<0, T>().get_value(t) + offset_;
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
