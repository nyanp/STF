/**
 * @file   NJControllers.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "NJControllers.h"
#include "../../datatype/OrbitCalc.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {
namespace nj {

void QuaternionAveraging::do_compute(const datatype::Time& t){
	if(t > this->last_update_){

		this->last_update_ = t;
	}
}

void MidRangeSpinController::do_compute(const datatype::Time& t){
	if(t > this->last_update_){

		this->last_update_ = t;
	}
}

void LongRangeSpinController::do_compute(const datatype::Time& t){
	if(t > this->last_update_){

		this->last_update_ = t;
	}
}

void StarImageEKF::do_compute(const datatype::Time& t){
	if(t > this->last_update_){

		this->last_update_ = t;
	}
}

void QuaternionForRMMEstimation::do_compute(const datatype::Time& t){
	if(t > this->last_update_){
		//Šµ«‹óŠÔ‚É‚¨‚¯‚é‘¾—z•ûŒü‚ğŒvZ
		datatype::StaticVector<2> sunvector = datatype::OrbitCalc::getSunDirection2D(this->clock_->get_datetime());

		datatype::DCM sundcm = datatype::TypeConverter::toDCM(sunvector[0],sunvector[1],0);
		datatype::DCM dcm;

		switch(this->index_){
		case 0:
			dcm = datatype::TypeConverter::toDCM(0,0,0);
			break;
		case 1:
			dcm = datatype::TypeConverter::toDCM(90,0,0);
			break;
		case 2:
			dcm = datatype::TypeConverter::toDCM(-90,0,0);
			break;
		case 3:
			dcm = datatype::TypeConverter::toDCM(0,90,0);
			break;
		case 4:
			dcm = datatype::TypeConverter::toDCM(0,-90,0);
			break;
		case 5:
			dcm = datatype::TypeConverter::toDCM(0,0,180);
			break;
		default:
			index_ = 0;
			break;
		}	
		this->value_b_ = datatype::TypeConverter::toQuaternion( dcm * sundcm );

		if(t > this->before_ + this->timespan_){
			index_ ++;
			this->before_ = t;
		}

		this->last_update_ = t;
	}
}

void MCConstantOutput::do_compute(const datatype::Time& t){
	if(t > this->last_update_){
		//todo: abstraction?
		double output;

		switch(this->index_){
		case 0:
			output = 0.2;
			break;
		case 1:
			output = -0.2;
			break;
		case 2:
			output = 0.4;
			break;
		case 3:
			output = -0.4;
			break;
		case 4:
			output = 0.6;
			break;
		case 5:
			output = -0.6;
			break;
		default:
			index_ = 0;
			axis_++;
			this->value_b_.reset();
			break;
		}

		switch(this->axis_){
		case 0:
			this->value_b_[0] = output;
			break;
		case 1:
			this->value_b_[1] = output;
			break;
		case 2:
			this->value_b_[2] = output;
			break;
		default:
			axis_ = 0;
		}

		if(t > this->before_ + this->timespan_){
			index_ ++;
			this->before_ = t;
		}

		this->last_update_ = t;
	}
}

void RWConstantOutput::do_compute(const datatype::Time& t){

}

} /* End of namespace stf::core::mode::strategy::control::nj */
} /* End of namespace stf::core::mode::strategy::control */
} /* End of namespace stf::core::mode::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */