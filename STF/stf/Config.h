/**
 * @file   Config.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef Config_h
#define Config_h

namespace stf{
namespace environment{
class Simulator;
class SH;
class Virtex;
}
}
//#include "environment/SH.h"
//typedef stf::environment::SH ENV;

#include "environment/Simulator.h"
typedef stf::environment::Simulator ENV;


//datetime settings
#define YEAR 2005
#define MONTH 1
#define DATE 31

//satellite settings
#define STEPTIME 0.1
#define GYROECRV 1000




#endif // Config_h