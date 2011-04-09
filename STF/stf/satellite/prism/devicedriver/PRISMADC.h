/**
 * @file   PRISMADC.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_PRISMADC_h
#define stf_core_devicedriver_PRISMADC_h


#include "../../../core/devicedriver/CDHComponent.h"
#include "../../../core/devicedriver/adc/ADCBase.h"

namespace stf {
namespace core {
namespace devicedriver {

#define PRISM__ADC__CHANNELS      96
#define PRISM__VOLTAGE__CHANNELS  12
#define PRISM__CURRENT__CHANNELS  26
#define PRISM__TEMP__CHANNELS     22
#define PRISM__VOLTAGE__OFFSET     0
#define PRISM__CURRENT__OFFSET    23
#define PRISM__TEMP__OFFSET       60

template<class Env>
class PRISMADC : public ADCBase<PRISM__ADC__CHANNELS, Env>{
public:
	PRISMADC(int instance_id) : ADCBase<PRISM__ADC__CHANNELS, Env>(instance_id){}
	virtual void do_update(){
		//TBD
	}
};

template<class Env = ENV>
class PRISMCurrentSensor : public MultiSensor<datatype::Current, PRISM__CURRENT__CHANNELS, PRISM__ADC__CHANNELS, Env> {
public:
	PRISMCurrentSensor(int instance_id, ADCBase<PRISM__ADC__CHANNELS, Env>* adc) 
		: MultiSensor<datatype::Current, PRISM__CURRENT__CHANNELS, PRISM__ADC__CHANNELS, Env>(instance_id, adc, PRISM__CURRENT__OFFSET){}
};

template<class Env = ENV>
class PRISMVoltageSensor : public  MultiSensor<datatype::Voltage, PRISM__VOLTAGE__CHANNELS, PRISM__ADC__CHANNELS, Env> {
public:
	PRISMVoltageSensor(int instance_id, ADCBase<PRISM__ADC__CHANNELS, Env>* adc)
		:  MultiSensor<datatype::Voltage, PRISM__VOLTAGE__CHANNELS, PRISM__ADC__CHANNELS, Env>(instance_id, adc, PRISM__VOLTAGE__OFFSET){}
};

template<class Env = ENV>
class PRISMTempSensor : public  MultiSensor<datatype::Temperature, PRISM__TEMP__CHANNELS, PRISM__ADC__CHANNELS, Env> {
public:
	PRISMTempSensor(int instance_id, ADCBase<PRISM__ADC__CHANNELS, Env>* adc)
		:  MultiSensor<datatype::Temperature, PRISM__TEMP__CHANNELS, PRISM__ADC__CHANNELS, Env>(instance_id, adc, PRISM__TEMP__OFFSET){}
};


} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_PRISMADC_h
