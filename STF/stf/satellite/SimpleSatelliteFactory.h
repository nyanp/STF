/**
 * @file   SimpleSatelliteFactory.h
 * @brief  SimpleSatellite用の具象ファクトリ．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef factory_SimpleSatelliteFactory_h
#define factory_SimpleSatelliteFactory_h

#include "../GlobalObject.h"
#include "../core/factory/SatelliteFactory.h"

#include "../core/strategy/control/Includes.h"

#include "../core/manager/Includes.h"
#include "../core/devicedriver/Includes.h"
#include "../core/datapool/Datapool.h"
#include "../core/command/Includes.h"
#include "../core/functor/InputFunctor.h"
#include "../core/functor/OutputFunctor.h"
#include "../core/datapool/Datapool.h"
#include "../core/mode/Mode.h"

#include "../core/strategy/telemetry/Includes.h"
#include "../datatype/Time.h"
#include "simplesatellite/SSGlobal.h"

namespace stf {
namespace core {
namespace factory {


template<class Env, class App>
class SimpleSatelliteFactory : public SatelliteFactory<Env, App, SimpleSatelliteFactory<Env, App> >{
	friend class SatelliteFactory<Env, App, SimpleSatelliteFactory<Env, App> >;
	typedef Env Environment;//!< 環境クラス．
	typedef App Application;//!< アプリケーションクラス．


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

	SSGlobal<Env>* global_;
};

template<class Env, class App>
void SimpleSatelliteFactory<Env, App>::create_mode(){
	this->global_->ss_safemode = new mode::Mode("SS_SAFEMODE");
	this->global_->ss_missionmode = new mode::Mode("SS_MISSIONMODE");
}


template<class Env, class App>
void SimpleSatelliteFactory<Env, App>::create_component(){
	typedef devicedriver::gyro::Gyro<Env> GYRO;
	typedef devicedriver::CompositeInput<GYRO, 3> ThreeAxisGyro;
	typedef devicedriver::rw::RW<Env> RW;
	typedef devicedriver::CompositeOutput<RW, 4, true> SkewRW;
	typedef stf::core::devicedriver::clock::DummyClock<Env, 100> Clock;
	typedef devicedriver::cmhandler::DummyCommandReceiver CmHandler;
	typedef devicedriver::tmhandler::DebugLogger TmHandler;

	//DataPool
	this->global_->ss_aocsdatapool = new core::datapool::AocsDataPool();
	this->global_->ss_eventdatapool = new core::datapool::EventDataPool();

	// Clock(RTC&OBCTime)
	this->global_->ss_clock = new Clock(App::year, App::month, App::date);

	// Command/Telemetry Driver
	this->global_->ss_commandreceiver = new CmHandler(global_->ss_commandmanager);
	this->global_->ss_tmhandler = new TmHandler("ss_telemetry.csv", false);

	//Gyro
	this->global_->ss_gyrox = new GYRO(datatype::TypeConverter::toDCM(0,-90, 0));
	this->global_->ss_gyroy = new GYRO(datatype::TypeConverter::toDCM(0, 0, 90));
	this->global_->ss_gyroz = new GYRO(datatype::TypeConverter::toDCM(0, 0, 0));
	this->global_->ss_gyro =  new ThreeAxisGyro(datatype::TypeConverter::toDCM(0, 0, 0));
	this->global_->ss_gyro->append_child(this->global_->ss_gyrox);
	this->global_->ss_gyro->append_child(this->global_->ss_gyroy);
	this->global_->ss_gyro->append_child(this->global_->ss_gyroz);

	// Reaction Wheel
	this->global_->ss_rw1 = new RW(datatype::TypeConverter::toDCM(0, 70, 0));
	this->global_->ss_rw2 = new RW(datatype::TypeConverter::toDCM(0, 70, 120));
	this->global_->ss_rw3 = new RW(datatype::TypeConverter::toDCM(0, 70, 240));
	this->global_->ss_rw4 = new RW(datatype::TypeConverter::toDCM(0, 0, 0));
	this->global_->ss_rw  = new SkewRW(datatype::TypeConverter::toDCM(0, 0, 0));
	this->global_->ss_rw->append_child(this->global_->ss_rw1);
	this->global_->ss_rw->append_child(this->global_->ss_rw2);
	this->global_->ss_rw->append_child(this->global_->ss_rw3);
	this->global_->ss_rw->append_child(this->global_->ss_rw4);
}

template<class Env, class App>
void SimpleSatelliteFactory<Env, App>::create_funcmanager(){
	global_->ss_modemanager = new manager::ModeManagerBase();
	global_->ss_controlmanager = new manager::ControlManagerBase();
	global_->ss_commandmanager = new manager::CommandManagerBase();
	global_->ss_telemetrymanager = new manager::TelemetryManagerBase();
	global_->ss_unitmanager = new manager::UnitManagerBase();
	global_->ss_systemmanager = new manager::SystemManagerBase();

	this->global_->add_function_manager(this->global_->ss_unitmanager);
	this->global_->add_function_manager(this->global_->ss_systemmanager);
	this->global_->add_function_manager(this->global_->ss_commandmanager);
	this->global_->add_function_manager(this->global_->ss_modemanager);
	this->global_->add_function_manager(this->global_->ss_controlmanager);
	this->global_->add_function_manager(this->global_->ss_telemetrymanager);
}

template<class Env, class App>
void SimpleSatelliteFactory<Env, App>::create_controller(){
	typedef strategy::control::RateDumping RateDumping;
	typedef strategy::control::ControlBlock ControlBlock;

	RateDumping* rd = new RateDumping(0.2, 0.0, 0.5, App::steptime);
	ControlBlock* cb = new ControlBlock(rd, this->global_->ss_rw);

	rd->connect_source<0>(this->global_->ss_gyro);

	this->global_->ss_controlstrategy = cb;

	this->global_->ss_missionmode->add_list(global_->ss_controlstrategy);

}

template<class Env, class App>
void SimpleSatelliteFactory<Env, App>::create_command(){
}

template<class Env, class App>
void SimpleSatelliteFactory<Env, App>::create_telemetry(){
	this->global_->ss_tmstrategy = new strategy::telemetry::OutputAll<>(global_->ss_tmhandler, global_->ss_aocsdatapool, global_->ss_eventdatapool);

	this->global_->ss_safemode->add_list(global_->ss_tmstrategy);
	this->global_->ss_missionmode->add_list(global_->ss_tmstrategy);

}

template<class Env, class App>
void SimpleSatelliteFactory<Env, App>::create_dataupdates(){
	// SafeMode
	this->global_->ss_safemode->add_list((core::devicedriver::IDataUpdatable*)(this->global_->ss_clock));
	this->global_->ss_safemode->add_list((core::devicedriver::IDataUpdatable*)(this->global_->ss_gyro));
	// MissionMode
	this->global_->ss_missionmode->add_list((core::devicedriver::IDataUpdatable*)(this->global_->ss_clock));
	this->global_->ss_missionmode->add_list((core::devicedriver::IDataUpdatable*)(this->global_->ss_rw));
	this->global_->ss_missionmode->add_list((core::devicedriver::IDataUpdatable*)(this->global_->ss_gyro));
}

template<class Env, class App>
void SimpleSatelliteFactory<Env, App>::create_switches(){
	// SafeMode
	this->global_->ss_safemode->add_list((core::devicedriver::ISwitchable*)(this->global_->ss_clock));
	this->global_->ss_safemode->add_list((core::devicedriver::ISwitchable*)(this->global_->ss_gyro));
	// MissionMode
	this->global_->ss_missionmode->add_list((core::devicedriver::ISwitchable*)(this->global_->ss_clock));
	this->global_->ss_missionmode->add_list((core::devicedriver::ISwitchable*)(this->global_->ss_rw));
	this->global_->ss_missionmode->add_list((core::devicedriver::ISwitchable*)(this->global_->ss_gyro));
}

template<class Env, class App>
void SimpleSatelliteFactory<Env, App>::create_functor(){
	//一定時間が経過したらSafeMode->MissionModeへ移行
	core::functor::IFunctor* timerfunc = new functor::Functor<functor::Getter_Over<datatype::Time, devicedriver::clock::ITimeClock>, core::functor::ModeChangeFunc>
			(
				new functor::Getter_Over<datatype::Time, devicedriver::clock::ITimeClock>(
					this->global_->ss_clock,&devicedriver::clock::ITimeClock::get_time, new datatype::Time(10, 0)
					),
					new functor::ModeChangeFunc(this->global_->ss_modemanager,*(this->global_->ss_missionmode))
			);
	this->global_->ss_safemode->add_list(timerfunc);
}

template<class Env, class App>
void SimpleSatelliteFactory<Env, App>::create_additional_hotspot(){

}

template<class Env, class App>
void SimpleSatelliteFactory<Env, App>::create_datapool(){
	this->global_->ss_gyrox->connect(global_->ss_aocsdatapool, 20, "SS_GYRO1");
	this->global_->ss_gyroy->connect(global_->ss_aocsdatapool, 20, "SS_GYRO2");
	this->global_->ss_gyroz->connect(global_->ss_aocsdatapool, 20, "SS_GYRO3");
	this->global_->ss_gyro->connect(global_->ss_aocsdatapool, 20, "SS_GYRO");

	this->global_->ss_rw1->connect(global_->ss_aocsdatapool, 10, "SS_RW1");
	this->global_->ss_rw2->connect(global_->ss_aocsdatapool, 10, "SS_RW2");
	this->global_->ss_rw3->connect(global_->ss_aocsdatapool, 10, "SS_RW3");
	this->global_->ss_rw4->connect(global_->ss_aocsdatapool, 10, "SS_RW4");
	this->global_->ss_rw->connect(global_->ss_aocsdatapool, 10, "SS_RW");
}

template<class Env, class App>
void SimpleSatelliteFactory<Env, App>::satellite_initialize(){
	this->global_->ss_modemanager->change_mode(this->global_->ss_safemode);
}

} /* End of namespace stf::core::factory */
} /* End of namespace stf::core */ 
} /* End of namespace stf */



#endif // factory_SimpleSatelliteFactory_h