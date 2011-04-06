/**
 * @file   Config.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef Config_h
#define Config_h

#include "core/environment/Simulator.h"
typedef stf::core::environment::Simulator ENV;


//datetime settings
#define YEAR 2005
#define MONTH 1
#define DATE 31

//satellite settings
#define STEPTIME 0.1
#define GYROECRV 1000

#define MODEHOTSPOT TYPELIST_5(devicedriver::ISwitchable, devicedriver::IDataUpdatable, functor::IFunctor, core::strategy::telemetry::ITelemetryStrategy, core::strategy::control::IControlStrategy)


#endif // Config_h