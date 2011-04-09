/**
 * @file   CrossProduct.cpp
 * @brief  クロスプロダクト則を用いて要求出力トルクを磁気モーメントに変換する制御ブロック．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "CrossProduct.h"
#include "../../../datatype/DCM.h"
#include "../../../datatype/OrbitCalc.h"
#include "../../../datatype/TypeConverter.h"
#include "../../../GlobalObject.h"
#include "../../../util/Trace.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {


CrossProduct::CrossProduct( 
		devicedriver::OutputPort<datatype::StaticVector<3>>* torquer_source,
		devicedriver::OutputPort<datatype::MagneticField>* b_source,
		devicedriver::InputPort<datatype::MagneticMoment>* mag_out
		) : StrategyBase("CrossProduct")
{
	this->connect_source<0>(torquer_source);
	this->connect_source<1>(b_source);
	if(mag_out != 0){
		mag_out->connect_source_(this);
	}
}

void CrossProduct::do_compute(const datatype::Time& t) {
	if(t <= this->last_update_) return; //既に別のブロック経由で更新済みなら再計算しない

	util::Trace trace(util::Trace::kControlBlock, name_);

	// M = B * T / |B|2
	datatype::MagneticField B = this->source<1, datatype::MagneticField>().get_value(t);
	datatype::StaticVector<3> T = this->source<0, datatype::StaticVector<3>>().get_value(t);

	this->value_ = (B % T) / (B.norm(2) * B.norm(2));

	this->last_update_ = t;
}


} /* End of namespace core::mode::strategy::control */
} /* End of namespace core::mode::strategy */
} /* End of namespace core::mode */
} /* End of namespace core */
