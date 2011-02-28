/**
 * @file   STTBase.cpp
 * @brief  スターセンサの基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "STTBase.h"
#include "../../../datatype/TypeConverter.h"
#include "../../../environment/Simulator.h"
#include "../../datapool/Datapool.h"
#include "../../../util/math/Rand.h"
#include "../../../util/math.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace stt {

//STT本体のQuaternion
//シミュレータ環境ではSTT座標系での真値を取得する
template <>
void STTBase<environment::Simulator>::do_update(){
	count_++;
	if(count_ >= 5){
		this->value_ = filter(this->environment_->getQuaternion(*this));
		if(this->datapool_ != 0){
			datapool_->set<STTBase<environment::Simulator>>(datapool_hold_index_,this->value_);
		}
		count_ = 0;
	}
}

template <>
datatype::Quaternion STTBase<environment::Simulator>::filter(const datatype::Quaternion& value){
	datatype::EulerAngle angle;
	angle[0] = util::math::WhiteNoise(this->err_arcsec_ * util::math::ARCSEC2RAD ,0) / 3;
	angle[1] = util::math::WhiteNoise(this->err_arcsec_ * util::math::ARCSEC2RAD, 0) / 3;
	angle[2] = util::math::WhiteNoise(this->err_arcsec_ * util::math::ARCSEC2RAD, 0) / 3;
	return datatype::TypeConverter::toQuaternion(angle) * value;
}

} /* End of namespace stf::core::devicedriver::stt */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */
