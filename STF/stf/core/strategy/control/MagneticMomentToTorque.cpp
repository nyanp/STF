/**
 * @file   MagneticMomentToTorque.cpp
 * @brief  磁気モーメントをトルクに変換する制御ブロック．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "MagneticMomentToTorque.h"
#include "../../../util/Trace.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {


MagneticMomentToTorque::MagneticMomentToTorque( 
		devicedriver::OutputPort<datatype::MagneticMoment>* mag_body_source,
		devicedriver::OutputPort<datatype::MagneticMoment>* mag_out_source,
		devicedriver::InputPort<datatype::StaticVector<3>>* torque_out
		) : StrategyBase("MagneticMomentToTorque")
{
	this->connect_source<0>(mag_body_source);
	this->connect_source<1>(mag_out_source);
	if(torque_out != 0){
		torque_out->connect_source_(this);
	}
}

void MagneticMomentToTorque::do_compute(const datatype::Time& t) {
	if(t <= this->last_update_) return; //既に別のブロック経由で更新済みなら再計算しない

	util::Trace trace(util::Trace::kControlBlock, name_);

	// T = M * B
	this->value_ = 
		this->source<1, datatype::MagneticMoment>().get_value(t) % 
		this->source<0, datatype::MagneticMoment>().get_value(t);

	this->last_update_ = t;
}


} /* End of namespace core::mode::strategy::control */
} /* End of namespace core::mode::strategy */
} /* End of namespace core::mode */
} /* End of namespace core */
