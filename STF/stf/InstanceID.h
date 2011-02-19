/**
 * @file   InstanceID.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef InstanceID_h
#define InstanceID_h

namespace stf {

template <int ID>
struct InstanceID {
	enum { value = ID };
};

namespace environment {
class Simulator;
class NullEnv;
class SH;
}

} /* End of namespace stf */

typedef stf::environment::Simulator ENV;

//datetime settings
#define YEAR 2005
#define MONTH 1
#define DATE 31

//satellite settings
#define STEPTIME 0.1
#define GYROECRV 1000

//
#define ID_STT_X 1
#define ID_STT_Y 2
#define ID_STT 3
#define ID_MTQ_X 4
#define ID_MTQ_Y 5
#define ID_MTQ_Z 6
#define ID_MTQ 7
#define ID_GYRO_X 8
#define ID_GYRO_Y 9
#define ID_GYRO_Z 10
#define ID_GYRO 11
#define ID_SS_PX 12
#define ID_SS_PY 13
#define ID_SS_PZ 14
#define ID_SS_MX 15
#define ID_SS_MY 16
#define ID_SS_MZ 17
#define ID_SS   18
#define ID_RW_1 20
#define ID_RW_2 21
#define ID_RW_3 22
#define ID_RW_4 23
#define ID_RW 24
#define ID_TAM 25
#define ID_EARTH 26
#define ID_GPS 27
#define ID_RECEIVER 28
#define ID_FOG_X 29
#define ID_FOG_Y 30
#define ID_FOG_Z 31
#define ID_FOG 32
#define ID_RTC 33
#define ID_ADC 34
#define ID_TEMPSENSOR 35
#define ID_CURRENTSENSOR 36
#define ID_VOLTAGESENSOR 37


//Modes
#define ID_SAFEMODE 30
#define ID_MISSIONMODE 31
#define ID_UNLOADINGMODE 32

//Strategies
#define ID_PID 40
#define ID_NOCONTROL 41
#define ID_OUTPUTALLTM 42
#define ID_PID2 43
#define ID_DUMPING 44
#define ID_EKF 45

// Global Util
#define ID_DATAPOOL 50
#define ID_EVENTPOOL 51
#define ID_CLOCK 52
#define ID_MODEMANAGER 60
#define ID_CONTROLMANAGER 61
#define ID_UNITMANAGER 62
#define ID_TELEMETRYMANAGER 63
#define ID_CUSTOMMANAGER 64
#define ID_SYSTEMMANAGER 65
#define ID_COMMANDMANAGER 66

//EventID
#define ID_ModeChangeEvent 0
#define ID_COMMANDEVENT 1


#endif // InstanceID_h