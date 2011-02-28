/**
 * @file   CouplingCompensation.h
 * @brief  3軸独立に制御則を適用した際に生じるカップリング項Iωを，フィードフォワードに打ち消すために使う制御ブロック．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_control_CouplingCompensation_h
#define stf_core_strategy_control_CouplingCompensation_h

#include "../StrategyBase.h"
#include "../../../datatype/StaticVector.h"
#include "../../../datatype/SatelliteModel.h"
#include "../../devicedriver/IOPort.h"
#include "../../../GlobalObject.h"
#include "../../../util/Trace.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {

//! 3軸独立に制御則を適用した際に生じるクロスカップリング項Iωを，フィードフォワードに打ち消すために使う制御ブロック．
/*! 
	入力:3軸角速度
	出力:3軸トルク
*/
template<class Env>
class CouplingCompensation
	: virtual public StrategyBase, 
	public devicedriver::InputPorts< TYPELIST_1( datatype::StaticVector<3> ) >,
	public devicedriver::OutputPorts< TYPELIST_1( datatype::StaticVector<3> ) >
{
public:
	CouplingCompensation(int instance_id, Global<Env>* global) : global_(global), StrategyBase(instance_id, "CouplingCompensation"){}
	CouplingCompensation(int instance_id, Global<Env>* global, 
		devicedriver::OutputPort<datatype::StaticVector<3>>* omega_source,
		devicedriver::InputPort<datatype::StaticVector<3>>* torque_out = 0
		) : global_(global) 
	{
		this->connect<0>(omega_source);
		if(torque_out != 0) torque_out->connect_source_(this);
	}
	~CouplingCompensation(){ }
	virtual void do_compute(const datatype::Time& t){
		if(t <= this->last_update_) return;

		util::Trace trace(util::Trace::kControlBlock, name_);

		datatype::StaticVector<3> omega = this->source<0, datatype::StaticVector<3>>().get_value(t);
		const datatype::StaticMatrix<3, 3>& I = this->global_->get_satellitemodel().getI();
			
		this->value_ = - omega % ( I * omega );

		this->last_update_ = t;
		
	}
private:
	Global<Env>* global_;
};


} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_strategy_control_input_CouplingCompensation_h
