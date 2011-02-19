/**
 * @file   QUEST.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "QUEST.h"
#include "../../../datatype/DateTime.h"
#include "../../../datatype/DCM.h"
#include "../../../datatype/OrbitCalc.h"
#include "../../../datatype/TypeConverter.h"
#include "../../../GlobalObject.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {


QUEST::QUEST(int instance_id, double sigma_sun, double sigma_earth,
		devicedriver::OutputPort<datatype::StaticVector<2>>* sunvector_source,
		devicedriver::OutputPort<datatype::StaticVector<2>>* earthvector_source,
		devicedriver::OutputPort<datatype::PositionInfo>* position_source,	
		devicedriver::OutputPort<datatype::DateTime>* time_source,	
		devicedriver::InputPort<datatype::Quaternion>* q_out
		) : StrategyBase(instance_id, "QUEST"), sigma_sun_(sigma_sun), sigma_earth_(sigma_earth)
{
	this->connectSource<0>(sunvector_source);
	this->connectSource<1>(earthvector_source);
	this->connectSource<2>(position_source);
	this->connectSource<3>(time_source);
	if(q_out != 0){
		q_out->connectSource_(this);
	}
	init_();
}

void QUEST::do_compute(const datatype::Time& t) {
	if(t <= this->last_update_) return; //既に別のブロック経由で更新済みなら再計算しない
		util::cout << "compute: QUEST" << util::endl;
	//センサから取得した衛星基準座標系における地球，太陽方向
	datatype::StaticVector<2> w_sun = this->source<0,datatype::StaticVector<2>>().getValueInBodyFrame(t);
	datatype::StaticVector<2> w_earth = this->source<1,datatype::StaticVector<2>>().getValueInBodyFrame(t);
	//軌道情報をもとに計算された衛星位置における地球，太陽方向
	datatype::StaticVector<3> v1 = datatype::OrbitCalc::getSunDirection3D(this->source<3,datatype::DateTime>().getValueInBodyFrame());
	datatype::StaticVector<3> v2 = datatype::OrbitCalc::getEarthDirection3D(this->source<2,datatype::PositionInfo>().getValueInBodyFrame(t));
	datatype::StaticVector<3> w1 = datatype::TypeConverter::toRectangular(w_sun);
	datatype::StaticVector<3> w2 = datatype::TypeConverter::toRectangular(w_earth);

	this->value_b_ = estimate_(v1, v2, w1, w2);
	this->last_update_ = t;
}


datatype::Quaternion QUEST::estimate_(
	datatype::StaticVector<3> v1, datatype::StaticVector<3> v2, 
	datatype::StaticVector<3> w1, datatype::StaticVector<3> w2)
{
	datatype::Matrix B(3,3);
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			B[i][j] = a1_ * w1[i] * v1[j] + a2_ * w2[i] * v2[j];
			B[i][j] = a1_ * w1[i] * v1[j] + a2_ * w2[i] * v2[j];
			B[i][j] = a1_ * w1[i] * v1[j] + a2_ * w2[i] * v2[j];
		}
	}
	double sigma = B.trace();
	datatype::Matrix S = B + B.trans();
	datatype::Matrix I(3,3); I.unitize();
	double det = S.det();

	//TBD!

	return datatype::TypeConverter::toQuaternion(B);
}

void QUEST::init_()
{
	//重みづけの計算
	double sigma1 = 1 / ( sigma_sun_ * sigma_sun_ );
	double sigma2 = 1 / ( sigma_earth_ * sigma_earth_ );
	this->a1_ =  sigma1 / ( sigma1 + sigma2 );
	this->a2_ =  sigma2 / ( sigma1 + sigma2 );
}


} /* End of namespace core::mode::strategy::input */
} /* End of namespace core::mode::strategy */
} /* End of namespace core::mode */
} /* End of namespace core */
