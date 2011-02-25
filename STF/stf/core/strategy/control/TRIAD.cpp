/**
 * @file   TRIAD.cpp
 * @brief  TRIAD則で姿勢決定を行う制御ブロック群．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "TRIAD.h"
#include "../../../datatype/DateTime.h"
#include "../../../datatype/DCM.h"
#include "../../../datatype/OrbitCalc.h"
#include "../../../datatype/TypeConverter.h"
#include "../../../GlobalObject.h"
#include "../../../util/Trace.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {

//TRIAD共通の計算を無名名前空間に纏める．
namespace {
datatype::Quaternion estimate_(
	datatype::StaticVector<3> v1, datatype::StaticVector<3> v2, 
	datatype::StaticVector<3> w1, datatype::StaticVector<3> w2)
{
	datatype::StaticVector<3> r1 = v1;
	datatype::StaticVector<3> s1 = w1;
	datatype::StaticVector<3> r2 = (r1 % v2) / (r1 % v2).norm(2);
	datatype::StaticVector<3> s2 = (s1 % w2) / (s1 % w2).norm(2);
	datatype::StaticVector<3> r3 = r1 % r2;
	datatype::StaticVector<3> s3 = s1 % s2;
	datatype::DCM dcm;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			dcm[i][j] = s1[i] * r1[j] + s2[i] * r2[j] + s3[i] * r3[j];
			dcm[i][j] = s1[i] * r1[j] + s2[i] * r2[j] + s3[i] * r3[j];
			dcm[i][j] = s1[i] * r1[j] + s2[i] * r2[j] + s3[i] * r3[j];
		}
	}
	return datatype::TypeConverter::toQuaternion(dcm);
}
}

TRIAD::TRIAD(int instance_id, 
		devicedriver::OutputPort<datatype::StaticVector<2>>* body_vector1,
		devicedriver::OutputPort<datatype::StaticVector<2>>* inertial_vector1,
		devicedriver::OutputPort<datatype::StaticVector<2>>* body_vector2,
		devicedriver::OutputPort<datatype::StaticVector<2>>* inertial_vector2,
		devicedriver::InputPort<datatype::Quaternion>* q_out
		) : StrategyBase(instance_id, "TRIAD")
{
	this->connect_source<0>(body_vector1);
	this->connect_source<1>(inertial_vector1);
	this->connect_source<2>(body_vector2);
	this->connect_source<3>(inertial_vector2);
	if(q_out != 0){
		q_out->connect_source_(this);
	}
}

void TRIAD::do_compute(const datatype::Time& t) {
	if(t <= this->last_update_) return; //既に別のブロック経由で更新済みなら再計算しない
	util::Trace trace(util::Trace::kControlBlock,name_);

	datatype::StaticVector<3> v1 = datatype::TypeConverter::toRectangular(
		this->source<0,datatype::StaticVector<2>>().get_value(t));

	datatype::StaticVector<3> v2 = datatype::TypeConverter::toRectangular(
		this->source<2,datatype::StaticVector<2>>().get_value(t));

	datatype::StaticVector<3> w1 = datatype::TypeConverter::toRectangular(
		this->source<1,datatype::StaticVector<2>>().get_value(t));

	datatype::StaticVector<3> w2 = datatype::TypeConverter::toRectangular(
		this->source<3,datatype::StaticVector<2>>().get_value(t));

	this->value_b_ = estimate_(v1, v2, w1, w2);
	this->last_update_ = t;
}


SunEarthTRIAD::SunEarthTRIAD(int instance_id, 
		devicedriver::OutputPort<datatype::StaticVector<2>>* sunvector_source,
		devicedriver::OutputPort<datatype::StaticVector<2>>* earthvector_source,
		devicedriver::OutputPort<datatype::PositionInfo>* position_source,	
		devicedriver::OutputPort<datatype::DateTime>* time_source,
		devicedriver::InputPort<datatype::Quaternion>* q_out
		) : StrategyBase(instance_id, "TRIAD")
{
	this->connect_source<0>(sunvector_source);
	this->connect_source<1>(earthvector_source);
	this->connect_source<2>(position_source);
	this->connect_source<3>(time_source);
	if(q_out != 0){
		q_out->connect_source_(this);
	}
}

void SunEarthTRIAD::do_compute(const datatype::Time& t) {
	if(t <= this->last_update_) return; //既に別のブロック経由で更新済みなら再計算しない

	util::Trace trace(util::Trace::kControlBlock,name_);

	//センサから取得した衛星基準座標系における地球，太陽方向
	datatype::StaticVector<2> w_sun = this->source<0,datatype::StaticVector<2>>().get_value(t);
	datatype::StaticVector<2> w_earth = this->source<1,datatype::StaticVector<2>>().get_value(t);
	//軌道情報をもとに計算された衛星位置における地球，太陽方向
	datatype::StaticVector<3> v1 = datatype::OrbitCalc::getSunDirection3D(this->source<3,datatype::DateTime>().get_value(t));
	datatype::StaticVector<3> v2 = datatype::OrbitCalc::getEarthDirection3D(this->source<2,datatype::PositionInfo>().get_value(t));

	datatype::StaticVector<3> w1 = datatype::TypeConverter::toRectangular(w_sun);
	datatype::StaticVector<3> w2 = datatype::TypeConverter::toRectangular(w_earth);

	this->value_b_ = estimate_(v1, v2, w1, w2);
	this->last_update_ = t;
}

SunMagTRIAD::SunMagTRIAD(int instance_id, 
		devicedriver::OutputPort<datatype::StaticVector<2>>* sunvector_source,
		devicedriver::OutputPort<datatype::MagneticField>* magvector_source,
		devicedriver::OutputPort<datatype::PositionInfo>* position_source,
		devicedriver::OutputPort<datatype::DateTime>* time_source,
		devicedriver::InputPort<datatype::Quaternion>* q_out
		) : StrategyBase(instance_id, "TRIAD")
{
	this->connect_source<0>(sunvector_source);
	this->connect_source<1>(magvector_source);
	this->connect_source<2>(position_source);
	this->connect_source<3>(time_source);
	if(q_out != 0){
		q_out->connect_source_(this);
	}
}

void SunMagTRIAD::do_compute(const datatype::Time& t) {
	if(t <= this->last_update_) return; //既に別のブロック経由で更新済みなら再計算しない

	util::Trace trace(util::Trace::kControlBlock,name_);

	//センサから取得した衛星基準座標系における地球，太陽方向
	datatype::StaticVector<2> w_sun = this->source<0,datatype::StaticVector<2>>().get_value(t);
	datatype::MagneticField w_mag = this->source<1,datatype::MagneticField>().get_value(t);
	//軌道情報をもとに計算された衛星位置における地球，太陽方向
	datatype::DateTime time = this->source<3,datatype::DateTime>().get_value(t);

	datatype::MagneticField v_mag = 
		datatype::OrbitCalc::getMagneticFieldDirection(this->source<2,datatype::PositionInfo>().get_value(t),time);
	datatype::StaticVector<3> v1 = datatype::OrbitCalc::getSunDirection3D(time);
	datatype::StaticVector<3> w1 = datatype::TypeConverter::toRectangular(w_sun);

	this->value_b_ = estimate_(v1, v_mag, w1, w_mag);
	this->last_update_ = t;
}

SunMagTRIAD2::SunMagTRIAD2(int instance_id, 
		devicedriver::clock::IAbsoluteTimeClock* clock,
		devicedriver::OutputPort<datatype::StaticVector<2>>* sunvector_source,
		devicedriver::OutputPort<datatype::MagneticField>* magvector_source,
		devicedriver::OutputPort<datatype::PositionInfo>* position_source,
		devicedriver::InputPort<datatype::Quaternion>* q_out
		) : StrategyBase(instance_id, "TRIAD"), clock_(clock)
{
	if(sunvector_source != 0) this->connect_source<0>(sunvector_source);
	if(magvector_source != 0) this->connect_source<1>(magvector_source);
	if(position_source != 0) this->connect_source<2>(position_source);

	if(q_out != 0){
		q_out->connect_source_(this);
	}
}

void SunMagTRIAD2::do_compute(const datatype::Time& t) {
	if(t <= this->last_update_) return; //既に別のブロック経由で更新済みなら再計算しない
	util::Trace trace(util::Trace::kControlBlock,name_);

	//センサから取得した衛星基準座標系における地球，太陽方向
	datatype::StaticVector<2> w_sun = this->source<0,datatype::StaticVector<2>>().get_value(t);
	datatype::MagneticField w_mag = this->source<1,datatype::MagneticField>().get_value(t);
	//軌道情報をもとに計算された衛星位置における地球，太陽方向
	datatype::DateTime time = this->clock_->get_datetime();

	datatype::MagneticField v_mag = 
		datatype::OrbitCalc::getMagneticFieldDirection(this->source<2,datatype::PositionInfo>().get_value(t),time);
	datatype::StaticVector<3> v1 = datatype::OrbitCalc::getSunDirection3D(time);
	datatype::StaticVector<3> w1 = datatype::TypeConverter::toRectangular(w_sun);

	this->value_b_ = estimate_(v1, v_mag, w1, w_mag);
	this->last_update_ = t;
}

} /* End of namespace core::mode::strategy::control */
} /* End of namespace core::mode::strategy */
} /* End of namespace core::mode */
} /* End of namespace core */
