/**
 * @file   EarthSensorBase.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_earthsensor_EarthSensorBase_h
#define stf_core_devicedriver_earthsensor_EarthSensorBase_h

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
namespace earthsensor {


template <class T>
class EarthSensorBase : public AOCSSensor<datatype::StaticVector<2>,datatype::StaticVector<2>,T>{
public:
	EarthSensorBase(int instance_id, const datatype::DCM &angle, double err_deg, int sigma = 3);
	virtual ~EarthSensorBase(){}
	virtual void doUpdate();
	virtual datatype::StaticVector<2> inputFilter(const datatype::StaticVector<2>& value); 
private:
    EarthSensorBase();
	double err_deg_;
	int sigma_;
};

template <class T>
EarthSensorBase<T>::EarthSensorBase(int instance_id, const datatype::DCM& dcm, double err_deg, int sigma)
	: AOCSSensor<datatype::StaticVector<2>,datatype::StaticVector<2>,T>(instance_id, "EarthSensor", dcm), err_deg_(err_deg), sigma_(sigma)
{

}

template <class T>
void EarthSensorBase<T>::doUpdate(){

}

//シミュレータ用の特殊化
template <>
void EarthSensorBase<environment::Simulator>::doUpdate();
template <>
datatype::StaticVector<2> EarthSensorBase<environment::Simulator>::inputFilter(const datatype::StaticVector<2>& value); 

} /* End of namespace stf::core::devicedriver::earthsensor */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_earthsensor_EarthSensorBase_h
