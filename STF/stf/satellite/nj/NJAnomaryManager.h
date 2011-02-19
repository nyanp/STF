/**
 * @file   NJAnomaryManager.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef scube_core_devicedriver_NJADC_h
#define scube_core_devicedriver_NJADC_h


#include "../../core/devicedriver/CDHComponent.h"
#include "../../core/devicedriver/adc/ADCBase.h"

namespace scube {
namespace core {
namespace devicedriver {

#define __NJ__ADC__CHANNELS     128
#define __NJ__VOLTAGE__CHANNELS  32
#define __NJ__CURRENT__CHANNELS  12
#define __NJ__TEMP1__CHANNELS     32
#define __NJ__TEMP2__CHANNELS     32
#define __NJ__VOLTAGE__OFFSET     0
#define __NJ__CURRENT__OFFSET    25
#define __NJ__TEMP1__OFFSET       60
#define __NJ__TEMP2__OFFSET       96

template<class Env>
class NJADC : public ADCBase<__NJ__ADC__CHANNELS, Env>{
public:
	NJADC(int instance_id) : ADCBase<__NJ__ADC__CHANNELS, Env>(instance_id){}

};

//電流センサ
template<class Env = ENV>
class NJCurrentSensor : public MultiSensor<datatype::Current, __NJ__CURRENT__CHANNELS, __NJ__ADC__CHANNELS, Env> {
public:
	NJCurrentSensor(int instance_id, ADCBase<__NJ__ADC__CHANNELS,Env>* adc) 
		: MultiSensor<datatype::Current, __NJ__CURRENT__CHANNELS, __NJ__ADC__CHANNELS, Env>(instance_id, adc, __NJ__CURRENT__OFFSET){}
};

//電圧センサ
template<class Env = ENV>
class NJVoltageSensor : public  MultiSensor<datatype::Voltage, __NJ__VOLTAGE__CHANNELS, __NJ__ADC__CHANNELS, Env> {
public:
	NJVoltageSensor(int instance_id, ADCBase<__NJ__ADC__CHANNELS,Env>* adc)
		:  MultiSensor<datatype::Voltage, __NJ__VOLTAGE__CHANNELS, __NJ__ADC__CHANNELS, Env>(instance_id, adc, __NJ__VOLTAGE__OFFSET){}
};

//2線式温度計
template<class Env = ENV>
class NJCoarseTempSensor : public  MultiSensor<datatype::Temperature, __NJ__TEMP1__CHANNELS, __NJ__ADC__CHANNELS, Env> {
public:
	NJCoarseTempSensor(int instance_id, ADCBase<__NJ__ADC__CHANNELS,Env>* adc)
		:  MultiSensor<datatype::Temperature, __NJ__TEMP1__CHANNELS, __NJ__ADC__CHANNELS, Env>(instance_id, adc,  __NJ__TEMP1__OFFSET){}
};

//4線式温度計
template<class Env = ENV>
class NJFineTempSensor : public  MultiSensor<datatype::Temperature, __NJ__TEMP2__CHANNELS, __NJ__ADC__CHANNELS, Env> {
public:
	NJFineTempSensor(int instance_id, ADCBase<__NJ__ADC__CHANNELS,Env>* adc)
		:  MultiSensor<datatype::Temperature, __NJ__TEMP2__CHANNELS, __NJ__ADC__CHANNELS, Env>(instance_id, adc,  __NJ__TEMP2__OFFSET){}
};

} /* End of namespace scube::core::component */
} /* End of namespace scube::core */
} /* End of namespace scube */

#endif // scube_core_devicedriver_NJADC_h
