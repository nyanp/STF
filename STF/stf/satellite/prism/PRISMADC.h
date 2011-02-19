#ifndef stf_core_devicedriver_PRISMADC_h
#define stf_core_devicedriver_PRISMADC_h


#include "../../core/devicedriver/CDHComponent.h"
#include "../../core/devicedriver/adc/ADCBase.h"

namespace stf {
namespace core {
namespace devicedriver {

#define __PRISM__ADC__CHANNELS      96
#define __PRISM__VOLTAGE__CHANNELS  12
#define __PRISM__CURRENT__CHANNELS  26
#define __PRISM__TEMP__CHANNELS     22
#define __PRISM__VOLTAGE__OFFSET     0
#define __PRISM__CURRENT__OFFSET    23
#define __PRISM__TEMP__OFFSET       60

template<class Env>
class PRISMADC : public ADCBase<__PRISM__ADC__CHANNELS, Env>{
public:
	PRISMADC(int instance_id) : ADCBase<__PRISM__ADC__CHANNELS, Env>(instance_id){}

};

template<class Env = ENV>
class PRISMCurrentSensor : public MultiSensor<datatype::Current, __PRISM__CURRENT__CHANNELS, __PRISM__ADC__CHANNELS, Env> {
public:
	PRISMCurrentSensor(int instance_id, ADCBase<__PRISM__ADC__CHANNELS,Env>* adc) 
		: MultiSensor<datatype::Current, __PRISM__CURRENT__CHANNELS, __PRISM__ADC__CHANNELS, Env>(instance_id, adc, __PRISM__CURRENT__OFFSET){}
};

template<class Env = ENV>
class PRISMVoltageSensor : public  MultiSensor<datatype::Voltage, __PRISM__VOLTAGE__CHANNELS, __PRISM__ADC__CHANNELS, Env> {
public:
	PRISMVoltageSensor(int instance_id, ADCBase<__PRISM__ADC__CHANNELS,Env>* adc)
		:  MultiSensor<datatype::Voltage, __PRISM__VOLTAGE__CHANNELS, __PRISM__ADC__CHANNELS, Env>(instance_id, adc, __PRISM__VOLTAGE__OFFSET){}
};

template<class Env = ENV>
class PRISMTempSensor : public  MultiSensor<datatype::Temperature, __PRISM__TEMP__CHANNELS, __PRISM__ADC__CHANNELS, Env> {
public:
	PRISMTempSensor(int instance_id, ADCBase<__PRISM__ADC__CHANNELS,Env>* adc)
		:  MultiSensor<datatype::Temperature, __PRISM__TEMP__CHANNELS, __PRISM__ADC__CHANNELS, Env>(instance_id, adc, __PRISM__TEMP__OFFSET){}
};


} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_PRISMADC_h
