/**
 * @file   TAMBase.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "TAMBase.h"
#include "../../../datatype/TypeConverter.h"
#include "../../../environment/Simulator.h"
#include "../../datapool/Datapool.h"
#include "../../../util/math.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace magnetometer {

//STT本体のQuaternion
//シミュレータ環境ではSTT座標系での真値を取得する
template <>
void TAMBase<environment::Simulator>::do_update(){
	this->set_value(filter(this->environment_->getMagneticField(*this)));
	util::cout << this->value_b_;
	if(this->datapool_ != 0){
		datapool_->set<TAMBase<environment::Simulator>>(datapool_hold_index_,this->value_);
	}
}

template <>
datatype::MagneticField TAMBase<environment::Simulator>::filter(const datatype::MagneticField& value){
	return value;
}

} /* End of namespace stf::core::devicedriver::magnetometer */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */
