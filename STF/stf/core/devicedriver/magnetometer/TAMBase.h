/**
 * @file   TAMBase.h
 * @brief  3軸磁気センサの基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_magnetometer_TAMBase_h
#define stf_core_devicedriver_magnetometer_TAMBase_h

#include "../../../datatype/Magnetic.h"

#include "../AOCSSensor.h"

namespace stf {
namespace environment {
class Simulator;
}
namespace core {
namespace devicedriver {
namespace magnetometer {


//! 3軸磁気センサの基底クラス．
/*! 
	@tparam T コンポーネントの環境クラス．
*/
template <class T>
class TAMBase : public AOCSSensor<datatype::MagneticField, datatype::MagneticField, T>{
public:
	TAMBase(int instance_id, const datatype::DCM &angle);
	virtual ~TAMBase(){}
	virtual void do_update();
	virtual datatype::MagneticField filter(const datatype::MagneticField& value); 
private:
    TAMBase();
	double err_deg_;
	int sigma_;
};

template <class T>
TAMBase<T>::TAMBase(int instance_id, const datatype::DCM& dcm)
	: AOCSSensor<datatype::MagneticField, datatype::MagneticField, T>(instance_id, "TAM", dcm)
{

}

template <class T>
void TAMBase<T>::do_update(){

}

//シミュレータ用の特殊化
template <>
void TAMBase<environment::Simulator>::do_update();
template <>
datatype::MagneticField TAMBase<environment::Simulator>::filter(const datatype::MagneticField& value); 

} /* End of namespace stf::core::devicedriver::magnetometer */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_sunsensor_TAMBase_h
