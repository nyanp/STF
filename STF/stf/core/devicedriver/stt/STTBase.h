/**
 * @file   STTBase.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_stt_STTBase_h
#define stf_core_devicedriver_stt_STTBase_h

#include "../../../datatype/DCM.h"
#include "../../../datatype/Quaternion.h"
#include "../../../datatype/Vector.h"
#include "../AOCSSensor.h"

namespace stf {
namespace environment {
class Simulator;
}
namespace core {
namespace devicedriver {
namespace stt {
template <class T>
class STTBase : public AOCSSensor<datatype::Quaternion,datatype::Quaternion,T>{
public:
	STTBase(int instance_id, const datatype::DCM &angle,double err_arcsec,int sigma = 3);
    virtual ~STTBase();
	virtual void do_update();
	virtual const datatype::Quaternion& get_in_bodyframe();
	virtual datatype::Quaternion filter(const datatype::Quaternion& value); 
private:
    STTBase();
    //datatype::Quaternion q_;
	datatype::Quaternion q_set_angle_;
	double err_arcsec_;
	int sigma_;
	int count_;//TBD
    //datatype::Vector qerror_[ 4];
    //double sigma_;
};


template <class T>
STTBase<T>::STTBase(int instance_id, const datatype::DCM& dcm,double err_arcsec,int sigma) 
	: AOCSSensor<datatype::Quaternion,datatype::Quaternion,T>(instance_id, "STT", dcm), err_arcsec_(err_arcsec), sigma_(sigma), count_(0)
{
	this->q_set_angle_ = datatype::TypeConverter::toQuaternion(dcm);
}

template <class T>
STTBase<T>::STTBase()
{
}

template <class T>
STTBase<T>::~STTBase()
{
}

template <class T>
void STTBase<T>::do_update(){

}

// DCMで計算せずにQuaternionで計算するためにオーバーライド
template <class T>
const datatype::Quaternion& STTBase<T>::get_in_bodyframe(){
	this->value_b_ = q_set_angle_ * value_;
	return this->value_b_;
}

//STT本体のQuaternion
template <>
void STTBase<environment::Simulator>::do_update();
template <>
datatype::Quaternion STTBase<environment::Simulator>::filter(const datatype::Quaternion& value); 
} /* End of namespace stf::core::devicedriver::stt */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_stt_STTBase_h
