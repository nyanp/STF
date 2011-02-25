/**
 * @file   WheelUnloading.cpp
 * @brief  RWのアンローディングをMTQを使用して行うための制御ブロック．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "WheelUnloading.h"
#include "../../../util/Trace.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {


WheelUnloading::WheelUnloading(int instance_id, 
		devicedriver::OutputPort<datatype::PositionInfo>* position_source,
		devicedriver::InputPort<datatype::StaticVector<3>>* torquer_out,
		devicedriver::InputPort<datatype::StaticVector<3>>* wheel_out
		) : StrategyBase(instance_id, "WheelUnloading")
{
	this->connect_source<0>(position_source);
	if(torquer_out != 0){
		torquer_out->connect_source_(&outputport<0,datatype::StaticVector<3>>());
	}
	if(wheel_out != 0){
		wheel_out->connect_source_(&outputport<1,datatype::StaticVector<3>>());
	}
}

void WheelUnloading::do_compute(const datatype::Time& t) {
	//if(t <= this->last_update_) return; //既に別のブロック経由で更新済みなら再計算しない
	util::Trace trace(util::Trace::kControlBlock,name_);
	//this->last_update_ = t;
}


} /* End of namespace core::mode::strategy::control */
} /* End of namespace core::mode::strategy */
} /* End of namespace core::mode */
} /* End of namespace core */
