/**
 * @file   STTBase.h
 * @brief  スターセンサの基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_stt_STTBase_h
#define stf_core_devicedriver_stt_STTBase_h

#include "../../../util/stfassert.h"
#include "../../../util/Macros.h"
#include "../../../util/math/Rand.h"
#include "../../../util/math.h"
#include "../AOCSSensor.h"
#include "../../../datatype/StaticVector.h"
#include "../../environment/Envfwd.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace stt {

//! スターセンサの基底クラス．
/*! 
	@tparam Env コンポーネントの環境クラス．
	@todo count_をどうにかする
*/
template <class Env>
class STTBase : public AOCSSensor<Env, datatype::Quaternion, datatype::Quaternion>{
public:
	STTBase(const datatype::DCM &angle, double err_arcsec, int sigma = 3);
	virtual ~STTBase(){}
	virtual datatype::Quaternion filter(const datatype::Quaternion& value); 
private:
	DO_UPDATE_SIMULATOR(){
		count_++;
		if(count_ >= 5){
			this->value_ = filter(this->environment_->getQuaternion(*this));
			if(this->datapool_ != 0){
				datapool_->set<STTBase<environment::Simulator<App> > >(datapool_hold_index_, this->value_);
			}
			count_ = 0;
		}
	}
	datatype::Quaternion q_set_angle_;
	double err_arcsec_;
	int sigma_;
	int count_;//TBD
};


template <class Env>
STTBase<Env>::STTBase(const datatype::DCM& dcm, double err_arcsec, int sigma) 
	: AOCSSensor<Env, datatype::Quaternion, datatype::Quaternion>("STT", dcm), err_arcsec_(err_arcsec), sigma_(sigma), count_(0)
{
	this->q_set_angle_ = datatype::TypeConverter::toQuaternion(dcm);
}


template <class Env>
datatype::Quaternion STTBase<Env>::filter(const datatype::Quaternion& value){
	datatype::EulerAngle angle;
	angle[0] = util::math::WhiteNoise(this->err_arcsec_ * util::math::ARCSEC2RAD , 0) / 3;
	angle[1] = util::math::WhiteNoise(this->err_arcsec_ * util::math::ARCSEC2RAD, 0) / 3;
	angle[2] = util::math::WhiteNoise(this->err_arcsec_ * util::math::ARCSEC2RAD, 0) / 3;
	return datatype::TypeConverter::toQuaternion(angle) * value;
}


} /* End of namespace stf::core::devicedriver::stt */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_stt_STTBase_h
