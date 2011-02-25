/**
 * @file   GGCompensation.cpp
 * @brief  重力傾斜トルクを計算し，逆符号のトルクを出力する制御ブロック．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "GGCompensation.h"
#include "../../../datatype/OrbitCalc.h"
#include "../../../datatype/SatelliteModel.h"
#include "../../../GlobalObject.h"
#include "../../../datatype/StaticMatrix.h"
#include "../../../util/Trace.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {


GGCompensation::GGCompensation(int instance_id, 
		const datatype::SatelliteModel& sat,
		devicedriver::OutputPort<datatype::Quaternion>* q_source,
		devicedriver::OutputPort<datatype::PositionInfo>* position_source,
		devicedriver::InputPort<datatype::StaticVector<3>>* torque_out
		) : StrategyBase(instance_id, "GGCompensation")
{
	this->connect_source<0>(q_source);
	this->connect_source<1>(position_source);
	if(torque_out != 0){
		torque_out->connect_source_(this);
	}
}

void GGCompensation::do_compute(const datatype::Time& t) {
	if(t <= this->last_update_) return; //既に別のブロック経由で更新済みなら再計算しない

	util::Trace trace(util::Trace::kControlBlock,name_);

	// 軌道情報と姿勢情報から，機体座標における地球方向ベクトルを算出
	datatype::StaticVector<3> R = datatype::OrbitCalc::getEarthDirectionInBodyFrame(
		this->source<1,datatype::PositionInfo>().get_value(t),
		this->source<0,datatype::Quaternion>().get_value(t));

	double r = R.norm(2);
	datatype::StaticVector<3> u = R / r;

	//重力傾斜トルクを打ち消すようなトルクを出力
	this->value_b_ = ( 3 * util::math::MU / ( r * r * r ) ) * u % (sat_.getI() * u);

	this->last_update_ = t;
}


} /* End of namespace core::mode::strategy::control */
} /* End of namespace core::mode::strategy */
} /* End of namespace core::mode */
} /* End of namespace core */
