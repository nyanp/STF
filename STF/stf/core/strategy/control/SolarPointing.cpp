/**
 * @file   SolarPointing.cpp
 * @brief  MTQで太陽指向制御を行うための制御ブロック．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "SolarPointing.h"
#include "../../../datatype/DCM.h"
#include "../../../datatype/OrbitCalc.h"
#include "../../../datatype/TypeConverter.h"
#include "../../../GlobalObject.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {


SolarPointing::SolarPointing(int instance_id, double k,
		devicedriver::OutputPort<datatype::MagneticField>* mag_source,
		devicedriver::OutputPort<datatype::StaticVector<2>>* sunvector_source ,
		devicedriver::InputPort<datatype::MagneticMoment>* mag_out
		) : StrategyBase(instance_id, "SolarPointing"), K_(k)
{
	this->connect_source<0>(mag_source);
	this->connect_source<1>(sunvector_source);
	if(mag_out != 0){
		mag_out->connect_source_(this);
	}
}

void SolarPointing::do_compute(const datatype::Time& t) {
	if(t <= this->last_update_) return; //既に別のブロック経由で更新済みなら再計算しない
	util::cout << "compute: solar pointing" << util::endl;
	datatype::MagneticField b = this->source<0,datatype::MagneticField>().value_b_;
	datatype::StaticVector<3> s = datatype::TypeConverter::toRectangular(this->source<1,datatype::StaticVector<2>>().value_b_);

	this->value_b_[0] = 0;
	this->value_b_[1] = 0;
	this->value_b_[2] = (- s[0] * b[1] + s[1] * b[0]) * K_;

	this->last_update_ = t;
}


} /* End of namespace core::mode::strategy::control */
} /* End of namespace core::mode::strategy */
} /* End of namespace core::mode */
} /* End of namespace core */
