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
class PRISMADC : public ADCBase<Env, PRISM__ADC__CHANNELS>{
public:
	PRISMADC(){}
	virtual void do_update(){
		//TBD
	}
};

template<class Env>
class PRISMCurrentSensor : public MultiSensor<Env, datatype::Current, PRISM__CURRENT__CHANNELS, PRISM__ADC__CHANNELS> {
public:
	PRISMCurrentSensor( ADCBase<Env, PRISM__ADC__CHANNELS>* adc) 
		: MultiSensor<Env, datatype::Current, PRISM__CURRENT__CHANNELS, PRISM__ADC__CHANNELS>( adc, PRISM__CURRENT__OFFSET){}
};

template<class Env>
class PRISMVoltageSensor : public  MultiSensor<Env, datatype::Voltage, PRISM__VOLTAGE__CHANNELS, PRISM__ADC__CHANNELS> {
public:
	PRISMVoltageSensor( ADCBase<Env, PRISM__ADC__CHANNELS>* adc)
		:  MultiSensor<Env, datatype::Voltage, PRISM__VOLTAGE__CHANNELS, PRISM__ADC__CHANNELS>( adc, PRISM__VOLTAGE__OFFSET){}
};

template<class Env>
class PRISMTempSensor : public  MultiSensor<Env, datatype::Temperature, PRISM__TEMP__CHANNELS, PRISM__ADC__CHANNELS> {
public:
	PRISMTempSensor( ADCBase<Env, PRISM__ADC__CHANNELS>* adc)
		:  MultiSensor<Env, datatype::Temperature, PRISM__TEMP__CHANNELS, PRISM__ADC__CHANNELS>( adc, PRISM__TEMP__OFFSET){}
};


} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_PRISMADC_h
