/**
 * @file   RWBase.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "RWBase.h"
#include "../../../environment/Simulator.h"
#include "../../datapool/Datapool.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace rw {


template <>
void RWBase<environment::Simulator>::do_update(){
	//角運動量（回転数）の更新
	this->angular_momentum_ += this->value_.value() * STEPTIME;
	//
	if(this->datapool_ != 0){
		datapool_->set<RWBase<environment::Simulator>>(datapool_hold_index_,this->value_);
	}
}

// シミュレータ用の特殊化版コンストラクタ．
// トルクソースとしてシミュレータに自動的に登録
template<>
RWBase<environment::Simulator>::RWBase(int instance_id, const datatype::DCM &dcm, double max_torque, double min_torque, double max_angular_momentum) : 
AOCSActuator<datatype::StaticVector<3>, datatype::Scalar, environment::Simulator>(instance_id, "RW", dcm), max_angular_momentum_(max_angular_momentum)
{
	this->environment_->attachTorqueSource(this);
	this->max_output_ = max_torque;
	this->min_output_ = min_torque;
}

} /* End of namespace stf::core::devicedriver::mtq */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */
