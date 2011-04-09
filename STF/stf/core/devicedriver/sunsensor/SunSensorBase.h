/**
 * @file   SunSensorBase.h
 * @brief  太陽センサの基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_sunsensor_SunSensorBase_h
#define stf_core_devicedriver_sunsensor_SunSensorBase_h

#include "../../../util/stfassert.h"
#include "../AOCSSensor.h"
#include "../../../datatype/StaticVector.h"

namespace stf {
namespace environment {
class Simulator;
}
namespace core {
namespace devicedriver {
namespace sunsensor {

//! 太陽センサの基底クラス．
/*! 
	@tparam Env コンポーネントの環境クラス．
*/
template <class Env>
class SunSensorBase : public AOCSSensor<Env, datatype::StaticVector<2>, datatype::StaticVector<2>>{
public:
	SunSensorBase(const datatype::DCM &angle, double err_deg, int sigma = 3);
	virtual ~SunSensorBase(){}
	virtual void do_update();
	virtual datatype::StaticVector<2> filter(const datatype::StaticVector<2>& value); 
private:
    SunSensorBase();
	double err_deg_;
	int sigma_;
};

template <class Env>
SunSensorBase<Env>::SunSensorBase(const datatype::DCM& dcm, double err_deg, int sigma)
	: AOCSSensor<Env, datatype::StaticVector<2>, datatype::StaticVector<2>>("SS", dcm), err_deg_(err_deg), sigma_(sigma)
{

}

template <class Env>
void SunSensorBase<Env>::do_update(){
	stf_static_assert(0 && "Not-Implemented-Exception");
}

//シミュレータ用の特殊化
template <>
void SunSensorBase<environment::Simulator>::do_update();

} /* End of namespace stf::core::devicedriver::sunsensor */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_sunsensor_SunSensorBase_h
