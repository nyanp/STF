#ifndef stf_GlobalObject_h
#define stf_GlobalObject_h

#include<fstream>
#include"InstanceID.h"
#include"datatype/List.h"

namespace stf {

namespace environment{
class Simulator;

class NullEnv;
} /* End of namespace stf::environment */

namespace util {
class Null;
}

namespace datatype {
template<class T> class List;
class Time;
class DateTime;
class IAocsData;
class SatelliteModel;
}

namespace core {
namespace functor {
class IFunctor;
}
namespace mode {
class SafeMode;
class MissionMode;
class UnloadingMode;
} /* End of namespace stf::core::mode */
namespace event {
class EventBase;
} /* End of namespace stf::core::event */
namespace strategy {
class StrategyBase;
namespace telemetry {
//class ITelemetryStrategy;
} /* End of namespace stf::core::strategy::telemetry */
namespace control {
class EKF;
class IControlStrategy;
class ControlBlock;
class PID;
} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
namespace manager {
class ModeManager;
class UnitManager;
class ControlManager;
class TelemetryManager;
class CustomManager;
class SystemManager;
class CommandManager;
class ManagerBase;
} /* End of namespace stf::core::manager */
namespace datapool {
class AocsDataPool;
class EventDataPool;
} /* End of namespace stf::core::datapool */
namespace devicedriver {
template<class Leaf,int Numbers> class CompositeInput;
template<class Leaf,int Numbers> class CompositeOutput;
namespace gps {
template<class T> class DummyGPS;
}
namespace cmhandler {
class ICommandReceiver;
}
namespace tmhandler {
class ITelemetryStoragable;
} /* End of namespace stf::core::devicedriver::tmhandler */
namespace clock {
class DummyClock;
class ITimeClock;
class IAbsoluteTimeClock;
} /* End of namespace stf::core::devicedriver::clock */
namespace earthsensor {
template<class T> class EarthSensor;
}
namespace magnetometer {
template<class T> class TAM;
}
namespace rw {
template<class T> class RW;
}
namespace sunsensor {
template<class T> class SunSensor;
}
namespace mtq {
template<class T> class MTQ;
} /* End of namespace stf::core::devicedriver::mtq */
namespace gyro {
template<class T> class Gyro;
} /* End of namespace stf::core::devicedriver::gyro */
namespace stt {
template<class T> class STT;
} /* End of namespace stf::core::devicedriver::stt */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

namespace stf {
using namespace core;

template<class Env>
class Global{

public:
	//static Global<Env>& getInstance();//Environmentごとに単一のインスタンスのみを生成
	virtual const core::datapool::AocsDataPool* getDataPool() const = 0;
	virtual const core::datapool::EventDataPool* getEventDataPool() const = 0;

	virtual const datatype::Time getGlobalTime() = 0;//衛星のOBC時刻を取得
	virtual const datatype::DateTime getGlobalDateTime() = 0;//衛星のRTC時刻を取得
	virtual const datatype::SatelliteModel getSatelliteModel() const = 0;//衛星の質量特性モデルを取得
	virtual datatype::List<core::manager::ManagerBase>* getFunctionManager() {return &(this->managers_);}

	//static datapool::AocsDataPool g_DataPool;
	//static datapool::EventDataPool g_EventDatapool;

	virtual ~Global(){}//デストラクタ
	Global(){}//コンストラクタを禁止（シングルトンパターン）
	Global(const Global<Env>&);
	void operator=(const Global<Env>&);

	datatype::List<core::manager::ManagerBase> managers_;

    //Environment
	/*stf::core::devicedriver::tmhandler::ITelemetryStoragable* g_Logger;

	//Mode
	mode::SafeMode* safemode;
	mode::MissionMode* missionmode;
	mode::UnloadingMode* unloadingmode;

	//Manager
	manager::ModeManager* modeman;
	manager::UnitManager* uniman;
	manager::ControlManager* conman;
	manager::TelemetryManager* telman;
	manager::CustomManager* cusman;
	manager::SystemManager* sysman;
	manager::CommandManager* commman;

	//Control Strategy
	core::strategy::control::IControlStrategy* pid;
	core::strategy::control::IControlStrategy* pid2;
	core::strategy::control::IControlStrategy* ratedumping;
	core::strategy::control::IControlStrategy* nocontrol;
	core::strategy::telemetry::ITelemetryStrategy* outputall;

	//Functor
	core::functor::IFunctor* func;

	//Telemetry Handler
	devicedriver::tmhandler::ITelemetryStoragable* storage;

	//MTQ
	devicedriver::mtq::MTQ<Env>* mtq1;
	devicedriver::mtq::MTQ<Env>* mtq2;
	devicedriver::mtq::MTQ<Env>* mtq3;
	devicedriver::CompositeOutput<devicedriver::mtq::MTQ<Env>,3>* mtq;

	//Star Tracker
	devicedriver::stt::STT<Env>* stt1;
	devicedriver::stt::STT<Env>* stt2;
	devicedriver::CompositeInput<devicedriver::stt::STT<Env>,2>* stt;

	//Gyro
	devicedriver::gyro::Gyro<Env>* gyro1;
	devicedriver::gyro::Gyro<Env>* gyro2;	
	devicedriver::gyro::Gyro<Env>* gyro3;
	devicedriver::CompositeInput<devicedriver::gyro::Gyro<Env>,3>* gyro;

	//Sun Sensor
	devicedriver::sunsensor::SunSensor<Env>* ss1;
	devicedriver::sunsensor::SunSensor<Env>* ss2;
	devicedriver::sunsensor::SunSensor<Env>* ss3;
	devicedriver::sunsensor::SunSensor<Env>* ss4;
	devicedriver::sunsensor::SunSensor<Env>* ss5;
	devicedriver::sunsensor::SunSensor<Env>* ss6;
	devicedriver::CompositeInput<devicedriver::sunsensor::SunSensor<Env>,6>* ss;

	//Reaction Wheel
	devicedriver::rw::RW<Env>* rw1;
	devicedriver::rw::RW<Env>* rw2;
	devicedriver::rw::RW<Env>* rw3;
	devicedriver::rw::RW<Env>* rw4;
	devicedriver::CompositeOutput<devicedriver::rw::RW<Env>,4>* rw;

	//Earth Sensor
	devicedriver::earthsensor::EarthSensor<Env>* earth;
	//Magnetrometer
	devicedriver::magnetometer::TAM<Env>* tam;
	//GPS
	devicedriver::gps::DummyGPS<Env>* gpsdummy;
	//
	devicedriver::cmhandler::ICommandReceiver* comm;

	*/

//private:

};

} /* End of namespace stf */

#endif // stf_GlobalObject_h