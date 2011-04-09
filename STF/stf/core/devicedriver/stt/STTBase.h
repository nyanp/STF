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
#include "../AOCSSensor.h"
#include "../../../datatype/StaticVector.h"

namespace stf {
namespace environment {
class Simulator;
}
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
	virtual void do_update();
	virtual datatype::Quaternion filter(const datatype::Quaternion& value); 
private:
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
void STTBase<Env>::do_update(){
	stf_static_assert(0 && "Not-Implemented-Exception");
}

// DCMで計算せずにQuaternionで計算するためにオーバーライド
/*template <class T>
const datatype::Quaternion& STTBase<T>::get_in_bodyframe(){
	this->value_b_ = q_set_angle_ * value_;
	return this->value_b_;
}*/

//STT本体のQuaternion
template <>
void STTBase<environment::Simulator>::do_update();

} /* End of namespace stf::core::devicedriver::stt */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_stt_STTBase_h
