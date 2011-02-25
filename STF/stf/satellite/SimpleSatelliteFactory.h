/**
 * @file   SimpleSatelliteFactory.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef factory_SimpleSatelliteFactory_h
#define factory_SimpleSatelliteFactory_h

#include "../GlobalObject.h"
#include "../factory/SatelliteFactory.h"

#include "../core/strategy/control/Includes.h"

#include "../core/manager/Includes.h"
#include "../core/devicedriver/Includes.h"
#include "../core/datapool/Datapool.h"
#include "../core/command/Includes.h"
#include "../core/event/Includes.h"
#include "../core/functor/InputFunctor.h"
#include "../core/functor/OutputFunctor.h"
#include "../core/datapool/Datapool.h"
#include "../core/mode/ModeBase.h"

#include "../core/strategy/telemetry/Includes.h"
#include "../datatype/Time.h"
#include "../InstanceID.h"
#include "simplesatellite/SSGlobal.h"

namespace stf {
namespace factory {

template<class Env>
class SimpleSatelliteFactory : public SatelliteFactory<Env>{
public:
	SimpleSatelliteFactory(){ this->global_ = new SSGlobal<Env>();}
	virtual ~SimpleSatelliteFactory(){ delete this->global_; }
	virtual void create_component();
	virtual void create_funcmanager();
	virtual void create_controller();
	virtual void create_telemetry();
	virtual void create_command();
	virtual void create_functor();
	virtual void create_dataupdates();
	virtual void create_switches();
	virtual void create_additional_hotspot();
	virtual void create_mode();
	virtual void create_datapool();
	virtual void satellite_initialize();
	virtual Global<Env>* return_created_object(){
		return this->global_;
	}
private:
	SSGlobal<Env>* global_;
};

template<class Env>
void SimpleSatelliteFactory<Env>::create_mode(){
	this->global_->ss_safemode = new mode::ModeBase(ID_SAFEMODE,"SS_SAFEMODE");
	this->global_->ss_missionmode = new mode::ModeBase(ID_MISSIONMODE,"SS_MISSIONMODE");
}


template<class Env>
void SimpleSatelliteFactory<Env>::create_component(){
	typedef devicedriver::gyro::Gyro<Env> GYRO;
	typedef devicedriver::CompositeInput<GYRO, 3> ThreeAxisGyro;
	typedef devicedriver::rw::RW<Env> RW;
	typedef devicedriver::CompositeOutput<RW, 4> SkewRW;
	typedef stf::core::devicedriver::clock::DummyClock<100> Clock;

	//DataPool
	this->global_->ss_aocsdatapool = new core::datapool::AocsDataPool(0);
	this->global_->ss_eventdatapool = new core::datapool::EventDataPool(0);


	// Clock(RTC&OBCTime)
	this->global_->ss_clock = new Clock(ID_CLOCK,YEAR,MONTH,DATE);


	//Gyro
	this->global_->ss_gyrox = new GYRO(ID_GYRO_X,datatype::TypeConverter::toDCM(0,-90,0));
	this->global_->ss_gyroy = new GYRO(ID_GYRO_Y,datatype::TypeConverter::toDCM(0,0,90));
	this->global_->ss_gyroz = new GYRO(ID_GYRO_Z,datatype::TypeConverter::toDCM(0,0,0));
	this->global_->ss_gyro =  new ThreeAxisGyro(ID_GYRO,datatype::TypeConverter::toDCM(0,0,0));
	this->global_->ss_gyro->appendChild(this->global_->ss_gyrox);
	this->global_->ss_gyro->appendChild(this->global_->ss_gyroy);
	this->global_->ss_gyro->appendChild(this->global_->ss_gyroz);

	// Reaction Wheel
	this->global_->ss_rw1 = new RW(ID_RW_1,datatype::TypeConverter::toDCM(0,0,0));
	this->global_->ss_rw2 = new RW(ID_RW_2,datatype::TypeConverter::toDCM(0,0,0));
	this->global_->ss_rw3 = new RW(ID_RW_3,datatype::TypeConverter::toDCM(0,0,0));
	this->global_->ss_rw4 = new RW(ID_RW_4,datatype::TypeConverter::toDCM(0,0,0));
	this->global_->ss_rw  = new SkewRW(ID_RW,datatype::TypeConverter::toDCM(0,0,0));
	this->global_->ss_rw->appendChild(this->global_->ss_rw1);
	this->global_->ss_rw->appendChild(this->global_->ss_rw2);
	this->global_->ss_rw->appendChild(this->global_->ss_rw3);
	this->global_->ss_rw->appendChild(this->global_->ss_rw4);
}

template<class Env>
void SimpleSatelliteFactory<Env>::create_funcmanager(){
	global_->ss_modemanager = new manager::ModeManager(ID_MODEMANAGER);
	global_->ss_controlmanager = new manager::ControlManager(ID_CONTROLMANAGER);
	global_->ss_commandmanager = new manager::CommandManager(ID_COMMANDMANAGER);
	global_->ss_telemetrymanager = new manager::TelemetryManager(ID_TELEMETRYMANAGER);
	global_->ss_unitmanager = new manager::UnitManager(ID_UNITMANAGER);
	global_->ss_systemmanager = new manager::SystemManager(ID_SYSTEMMANAGER);

	this->global_->managers_.add(*this->global_->ss_unitmanager);
	this->global_->managers_.add(*this->global_->ss_systemmanager);
	this->global_->managers_.add(*this->global_->ss_commandmanager);
	this->global_->managers_.add(*this->global_->ss_modemanager);
	this->global_->managers_.add(*this->global_->ss_controlmanager);
	this->global_->managers_.add(*this->global_->ss_telemetrymanager);
}

template<class Env>
void SimpleSatelliteFactory<Env>::create_controller(){

}

template<class Env>
void SimpleSatelliteFactory<Env>::create_command(){
}

template<class Env>
void SimpleSatelliteFactory<Env>::create_telemetry(){
}

template<class Env>
void SimpleSatelliteFactory<Env>::create_dataupdates(){
	// SafeMode
	this->global_->ss_safemode->add_list((core::devicedriver::IDataUpdatable*)(this->global_->ss_clock));
	this->global_->ss_safemode->add_list((core::devicedriver::IDataUpdatable*)(this->global_->ss_gyro));
	// MissionMode
	this->global_->ss_missionmode->add_list((core::devicedriver::IDataUpdatable*)(this->global_->ss_clock));
	this->global_->ss_missionmode->add_list((core::devicedriver::IDataUpdatable*)(this->global_->ss_rw));
	this->global_->ss_missionmode->add_list((core::devicedriver::IDataUpdatable*)(this->global_->ss_gyro));
}

template<class Env>
void SimpleSatelliteFactory<Env>::create_switches(){
	// SafeMode
	this->global_->ss_safemode->add_list((core::devicedriver::ISwitchable*)(this->global_->ss_clock));
	this->global_->ss_safemode->add_list((core::devicedriver::ISwitchable*)(this->global_->ss_gyro));
	// MissionMode
	this->global_->ss_missionmode->add_list((core::devicedriver::ISwitchable*)(this->global_->ss_clock));
	this->global_->ss_missionmode->add_list((core::devicedriver::ISwitchable*)(this->global_->ss_rw));
	this->global_->ss_missionmode->add_list((core::devicedriver::ISwitchable*)(this->global_->ss_gyro));
}

template<class Env>
void SimpleSatelliteFactory<Env>::create_functor(){

}

template<class Env>
void SimpleSatelliteFactory<Env>::create_additional_hotspot(){
	//àÍíËéûä‘Ç™åoâﬂÇµÇΩÇÁSafeMode->MissionModeÇ÷à⁄çs
	core::functor::IFunctor* timerfunc = new functor::Functor<functor::Getter_Over<datatype::Time,devicedriver::clock::ITimeClock>,core::functor::ModeChangeFunc>
			(
				new functor::Getter_Over<datatype::Time,devicedriver::clock::ITimeClock>(
					this->global_->ss_clock,&devicedriver::clock::ITimeClock::get_time,new datatype::Time(10,0)
					),
					new functor::ModeChangeFunc(this->global_->ss_modemanager,*(this->global_->ss_missionmode))
			);
	this->global_->ss_safemode->add_list(timerfunc);
}

template<class Env>
void SimpleSatelliteFactory<Env>::create_datapool(){
	this->global_->ss_gyrox->connect(global_->ss_aocsdatapool,20,"SS_GYRO1");
	this->global_->ss_gyroy->connect(global_->ss_aocsdatapool,20,"SS_GYRO2");
	this->global_->ss_gyroz->connect(global_->ss_aocsdatapool,20,"SS_GYRO3");
	this->global_->ss_gyro->connect(global_->ss_aocsdatapool,20,"SS_GYRO");

	this->global_->ss_rw1->connect(global_->ss_aocsdatapool,10,"SS_RW1");
	this->global_->ss_rw2->connect(global_->ss_aocsdatapool,10,"SS_RW2");
	this->global_->ss_rw3->connect(global_->ss_aocsdatapool,10,"SS_RW3");
	this->global_->ss_rw4->connect(global_->ss_aocsdatapool,10,"SS_RW4");
	this->global_->ss_rw->connect(global_->ss_aocsdatapool,10,"SS_RW");
}

template<class Env>
void SimpleSatelliteFactory<Env>::satellite_initialize(){
	this->global_->ss_modemanager->change_mode(this->global_->ss_safemode);
}


} /* End of namespace stf::factory */
} /* End of namespace stf */




#endif // factory_SimpleSatelliteFactory_h