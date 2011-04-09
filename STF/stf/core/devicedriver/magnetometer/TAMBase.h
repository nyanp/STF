/**
 * @file   TAMBase.h
 * @brief  3軸磁気センサの基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_magnetometer_TAMBase_h
#define stf_core_devicedriver_magnetometer_TAMBase_h

#include "../../../util/stfassert.h"
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
	@tparam Env コンポーネントの環境クラス．
*/
template <class Env>
class TAMBase : public AOCSSensor<Env, datatype::MagneticField, datatype::MagneticField>{
public:
	TAMBase(const datatype::DCM &angle);
	virtual ~TAMBase(){}
	virtual void do_update();
	virtual datatype::MagneticField filter(const datatype::MagneticField& value); 
private:
    TAMBase();
	double err_deg_;
	int sigma_;
};

template <class Env>
TAMBase<Env>::TAMBase(const datatype::DCM& dcm)
	: AOCSSensor<Env, datatype::MagneticField, datatype::MagneticField>( "TAM", dcm)
{

}

template <class Env>
void TAMBase<Env>::do_update(){
	stf_static_assert(0 && "Not-Implemented-Exception");
}

//シミュレータ用の特殊化
template <>
void TAMBase<environment::Simulator>::do_update();


} /* End of namespace stf::core::devicedriver::magnetometer */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_sunsensor_TAMBase_h
