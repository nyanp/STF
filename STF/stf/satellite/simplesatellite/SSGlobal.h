/**
 * @file   SSGlobal.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef satellite_simplesatellite_SSGlobal_h
#define satellite_simplesatellite_SSGlobal_h
#include "../../GlobalObject.h"
#include "../../core/manager/Includes.h"
#include "../../core/devicedriver/Includes.h"
#include "../../core/mode/ModeBase.h"
#include "../../datatype/SatelliteModel.h"


namespace stf {
namespace factory {
template <class Env> class SSFactory;
}

template <class Env>
struct SSGlobal : public Global<Env>{
	
	virtual const datatype::Time get_global_time(){
		return this->ss_clock->get_time();
	}
	virtual const datatype::DateTime get_global_datetime(){
		return this->ss_clock->get_datetime();
	}
	virtual const datatype::SatelliteModel get_satellitemodel() const{
		return this->ss_body_;
	}
	virtual const core::datapool::AocsDataPool* get_datapool() const {
		return this->ss_aocsdatapool;
	}
	virtual const core::datapool::EventDataPool* get_eventdatapool() const {
		return this->ss_eventdatapool;
	}

	// Satellite Body
	datatype::SatelliteModel ss_body_;

	// DataPool
	datapool::AocsDataPool* ss_aocsdatapool;
	datapool::EventDataPool* ss_eventdatapool;

	// Mode
	mode::ModeBase* ss_safemode;
	mode::ModeBase* ss_missionmode;

	//Clock
	devicedriver::clock::DummyClock<Env, 100>* ss_clock;

	//Manager
	manager::ModeManager* ss_modemanager;
	manager::ControlManager* ss_controlmanager;
	manager::TelemetryManager* ss_telemetrymanager;
	manager::CommandManager* ss_commandmanager;
	manager::UnitManager* ss_unitmanager;
	manager::SystemManager* ss_systemmanager;

	// Command / Telemetry Handler 
	devicedriver::cmhandler::ICommandReceiver* ss_commandreceiver;
	devicedriver::tmhandler::ITelemetryStoragable* ss_tmhandler;

	//Control Strategy
	core::strategy::control::IControlStrategy* ss_controlstrategy;
	core::strategy::telemetry::ITelemetryStrategy* ss_tmstrategy;


	//Gyro
	typedef devicedriver::gyro::Gyro<Env> Gyro;
	typedef devicedriver::CompositeInput<Gyro, 3> ThreeAxisGyro;

	Gyro* ss_gyrox;
	Gyro* ss_gyroy;
	Gyro* ss_gyroz;
	ThreeAxisGyro* ss_gyro;

	//Reaction Wheel
	typedef devicedriver::rw::RW<Env> RW;
	typedef devicedriver::CompositeOutput<RW, 4> SkewRW;

	RW* ss_rw1;
	RW* ss_rw2;
	RW* ss_rw3;
	RW* ss_rw4;
	SkewRW* ss_rw;
};

} /* End of namespace stf */




#endif // satellite_simplesatellite_SSGlobal_h