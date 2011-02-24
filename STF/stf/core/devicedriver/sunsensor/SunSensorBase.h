/**
 * @file   SunSensorBase.h
 * @brief  太陽センサの基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_sunsensor_SunSensorBase_h
#define stf_core_devicedriver_sunsensor_SunSensorBase_h

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
	@tparam T コンポーネントの環境クラス．
*/
template <class T>
class SunSensorBase : public AOCSSensor<datatype::StaticVector<2>,datatype::StaticVector<2>,T>{
public:
	SunSensorBase(int instance_id, const datatype::DCM &angle, double err_deg, int sigma = 3);
	virtual ~SunSensorBase(){}
	virtual void do_update();
	virtual datatype::StaticVector<2> filter(const datatype::StaticVector<2>& value); 
private:
    SunSensorBase();
	double err_deg_;
	int sigma_;
};

template <class T>
SunSensorBase<T>::SunSensorBase(int instance_id, const datatype::DCM& dcm, double err_deg, int sigma)
	: AOCSSensor<datatype::StaticVector<2>,datatype::StaticVector<2>,T>(instance_id, "SS", dcm), err_deg_(err_deg), sigma_(sigma)
{

}

template <class T>
void SunSensorBase<T>::do_update(){

}

//シミュレータ用の特殊化
template <>
void SunSensorBase<environment::Simulator>::do_update();
template <>
datatype::StaticVector<2> SunSensorBase<environment::Simulator>::filter(const datatype::StaticVector<2>& value); 

} /* End of namespace stf::core::devicedriver::sunsensor */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_sunsensor_SunSensorBase_h
