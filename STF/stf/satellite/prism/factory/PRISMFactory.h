/**
 * @file   PRISMFactory.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef factory_PRISMFactory_h
#define factory_PRISMFactory_h

#include "../../../GlobalObject.h"
#include "../../../core/factory/SatelliteFactory.h"
#include "../../../core/strategy/control/Includes.h"
#include "../../../core/manager/Includes.h"
#include "../../../core/devicedriver/Includes.h"
#include "../../../core/datapool/Datapool.h"
#include "../../../core/command/Includes.h"
#include "../../../core/functor/InputFunctor.h"
#include "../../../core/functor/OutputFunctor.h"
#include "../../../core/datapool/Datapool.h"
#include "../../../core/mode/Mode.h"
#include "../../../core/strategy/telemetry/Includes.h"
#include "../../../datatype/Time.h"

#include "PRISMGlobal.h"

namespace stf {
namespace core {
namespace factory {

template<class Env>
class PRISMFactory : public SatelliteFactory<Env, PRISMFactory<Env>>{
	friend class SatelliteFactory<Env, PRISMFactory<Env>>;
	typedef Env Environment;//!< 環境クラス．

	PRISMFactory(){ this->global_ = new PRISMGlobal<Env>();}
	virtual ~PRISMFactory(){ delete this->global_; }

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
	virtual void satellite_initialize(){}
	virtual Global<Env>* return_created_object(){
		return this->global_;
	}

	PRISMGlobal<Env>* global_;
};

template<class Env>
void PRISMFactory<Env>::create_mode(){
	this->global_->pr_safemode = new core::mode::Mode("PRISM_SAFEMODE");
	this->global_->pr_amode = new core::mode::Mode("PRISM_AOCSMODE");
	this->global_->pr_dmode = new core::mode::Mode("PRISM_NOCONTROLMODE");
	this->global_->pr_dpmode = new core::mode::Mode("PRISM_MISSIONMODE");
	this->global_->pr_dsmode = new core::mode::Mode("PRISM_SAFEMODE");
	this->global_->pr_resetmode = new core::mode::Mode("PRISM_RESETMODE");
}


template<class Env>
void PRISMFactory<Env>::create_component(){
	typedef stf::core::devicedriver::CompositeOutput<devicedriver::mtq::PRISMMTQ<Env>, 3> ThreeAxisMTQ;
	typedef stf::core::devicedriver::CompositeInput<devicedriver::gyro::PRISMGyro<Env>, 3> ThreeAxisGyro;
	typedef stf::core::devicedriver::CompositeInput<devicedriver::sunsensor::PRISMSunSensor<Env>, 6> SixAxisSS;
	typedef stf::core::devicedriver::gyro::PRISMGyro<Env> GYRO;
	typedef stf::core::devicedriver::mtq::PRISMMTQ<Env> MTQ;
	typedef stf::core::devicedriver::sunsensor::PRISMSunSensor<Env> SS;
	typedef stf::core::devicedriver::magnetometer::PRISMTAM<Env> TAM;
	typedef stf::core::devicedriver::gps::DummyGPS<Env> GPS;
	typedef stf::core::devicedriver::clock::PRISMDummyClock<Env> Clock;

	//DataPool
	this->global_->pr_aocsdatapool = new core::datapool::AocsDataPool();
	this->global_->pr_eventdatapool = new core::datapool::EventDataPool();

	// MTQ
	this->global_->pr_mtqx = new MTQ(datatype::TypeConverter::toDCM(0,-90, 0));
	this->global_->pr_mtqy = new MTQ(datatype::TypeConverter::toDCM(0, 0, 90));
	this->global_->pr_mtqz = new MTQ(datatype::TypeConverter::toDCM(0, 0, 0));
	this->global_->pr_mtq = new ThreeAxisMTQ(datatype::TypeConverter::toDCM(0, 0, 0));
	this->global_->pr_mtq->append_child(this->global_->pr_mtqx);
	this->global_->pr_mtq->append_child(this->global_->pr_mtqy);
	this->global_->pr_mtq->append_child(this->global_->pr_mtqz);

	// Gyro
	this->global_->pr_gyrox = new GYRO(datatype::TypeConverter::toDCM(0,-90, 0));
	this->global_->pr_gyroy = new GYRO(datatype::TypeConverter::toDCM(0, 0, 90));
	this->global_->pr_gyroz = new GYRO(datatype::TypeConverter::toDCM(0, 0, 0));
	this->global_->pr_gyro =  new ThreeAxisGyro(datatype::TypeConverter::toDCM(0, 0, 0));
	this->global_->pr_gyro->append_child(this->global_->pr_gyrox);
	this->global_->pr_gyro->append_child(this->global_->pr_gyroy);
	this->global_->pr_gyro->append_child(this->global_->pr_gyroz);

	// Sun Sensor
	this->global_->pr_sspx = new SS(datatype::TypeConverter::toDCM(0,-90, 0));
	this->global_->pr_sspy = new SS(datatype::TypeConverter::toDCM(0, 0, 90));
	this->global_->pr_sspz = new SS(datatype::TypeConverter::toDCM(0, 0, 0));
	this->global_->pr_ssmx = new SS(datatype::TypeConverter::toDCM(180,-90, 0));
	this->global_->pr_ssmy = new SS(datatype::TypeConverter::toDCM(180, 0, 90));
	this->global_->pr_ssmz = new SS(datatype::TypeConverter::toDCM(180, 0, 0));
	this->global_->pr_ss = new SixAxisSS(datatype::TypeConverter::toDCM(0, 0, 0));
	this->global_->pr_ss->append_child(this->global_->pr_sspx);
	this->global_->pr_ss->append_child(this->global_->pr_sspy);
	this->global_->pr_ss->append_child(this->global_->pr_sspz);
	this->global_->pr_ss->append_child(this->global_->pr_ssmx);
	this->global_->pr_ss->append_child(this->global_->pr_ssmy);
	this->global_->pr_ss->append_child(this->global_->pr_ssmz);

	// MagnetoMeter
	this->global_->pr_tam = new TAM(datatype::TypeConverter::toDCM(0, 0, 0));

	// DummyGPS(TLE Holder)
	this->global_->pr_gpsdummy = new GPS();

	// Clock(RTC&OBCTime)
	this->global_->pr_clock = new Clock(YEAR, MONTH, DATE);

	// Telemetery Handler
	//this->global_->pr_tmhandler = new core::devicedriver::tmhandler::PRISMTelemetryHandler();
	this->global_->pr_tmhandler = new core::devicedriver::tmhandler::PRISMTelemetryHandler<Env>();
	this->global_->pr_commandreceiver = new core::devicedriver::cmhandler::PRISMCommandReceiver<Env>(this->global_->pr_commman, "command.txt", this->global_);

	this->global_->pr_adc = new core::devicedriver::PRISMADC<Env>();
	this->global_->pr_currentsensor = new core::devicedriver::PRISMCurrentSensor<Env>(global_->pr_adc);
	this->global_->pr_voltagesensor = new core::devicedriver::PRISMVoltageSensor<Env>(global_->pr_adc);
	this->global_->pr_tempsensor = new core::devicedriver::PRISMTempSensor<Env>(global_->pr_adc);
	//this->global_->pr_currentsensor = new core::devicedriver::CDHComponent<
}

template<class Env>
void PRISMFactory<Env>::create_funcmanager(){
	this->global_->pr_modeman = new core::manager::ModeManagerBase();
	this->global_->pr_conman = new core::manager::ControlManagerBase();
	this->global_->pr_uniman1 = new core::manager::UnitManagerBase();
	this->global_->pr_uniman2 = new core::manager::UnitManagerBase();
	this->global_->pr_telman1 = new core::manager::TelemetryManagerBase();
	this->global_->pr_telman2 = new core::manager::TelemetryManagerBase();
	this->global_->pr_sysman = new core::manager::SystemManagerBase();
	this->global_->pr_commman = new core::manager::CommandManagerBase();
	this->global_->pr_heater = new core::manager::HeaterControl<Env>(this->global_->pr_tempsensor, 0, 0);
	this->global_->pr_customman = new core::manager::PRISMCustomManager<Env>(this->global_->pr_heater);

	this->global_->add_function_manager(this->global_->pr_modeman);
	this->global_->add_function_manager(this->global_->pr_conman);
	this->global_->add_function_manager(this->global_->pr_uniman1);
	this->global_->add_function_manager(this->global_->pr_uniman2);
	this->global_->add_function_manager(this->global_->pr_telman1);
	this->global_->add_function_manager(this->global_->pr_telman2);
	this->global_->add_function_manager(this->global_->pr_sysman);
	this->global_->add_function_manager(this->global_->pr_commman);
	this->global_->add_function_manager(this->global_->pr_customman);
}

template<class Env>
void PRISMFactory<Env>::create_controller(){
	typedef core::strategy::control::Combining_5<datatype::StaticVector<3>>     TorqueCombiner;
	typedef core::strategy::control::Combining_3<datatype::MagneticMoment>      MagCombiner;
	typedef core::strategy::control::CrossProduct                               CrossProduct;
	typedef core::strategy::control::LiniarCorrection<datatype::MagneticMoment> LiniarCorrection;
	typedef core::strategy::control::Bdot                                       Bdot;
	typedef core::strategy::control::CouplingCompensation<Env>                  Decoupling;
	typedef core::strategy::control::RateDumping                                RateDumping;
	typedef core::strategy::control::EarthPointingPID                           PID;
	typedef core::strategy::control::GGCompensation                             GGComp;
	typedef core::strategy::control::PRISMEKF                                   EKF;
	typedef core::strategy::control::PRISMSunMagTRIAD                           TRIAD;
	typedef core::strategy::control::PRISMRMMEKF                                RMMEKF;
	typedef core::strategy::control::PRISMControlBlock                          STRATEGY;
	//PRISM Controller
	TorqueCombiner*   PRISM_TORQUE_COMBINER = new TorqueCombiner();
	MagCombiner*      PRISM_MAG_COMBINER    = new MagCombiner();
	CrossProduct*     PRISM_CROSSPRODUCT    = new CrossProduct();
	LiniarCorrection* PRISM_RMMCOMP         = new LiniarCorrection(-1);
	Bdot*             PRISM_BDOT            = new Bdot(1);
	Decoupling*       PRISM_DECOUPLING      = new Decoupling(this->global_);
	RateDumping*      PRISM_RATEDUMPING     = new RateDumping(1, 0.1, 0.1, STEPTIME);
	PID*              PRISM_PID             = new PID(1, 0.01, 0.01, STEPTIME,*(new datatype::StaticVector<3>));
	PID*              PRISM_PD              = new PID(1, 0, 0.01, STEPTIME,*(new datatype::StaticVector<3>));
	GGComp*           PRISM_GGCOMP          = new GGComp();
	EKF*              PRISM_EKF             = new EKF();
	TRIAD*            PRISM_TRIAD           = new TRIAD();
	RMMEKF*           PRISM_RMMEKF          = new RMMEKF();

	//制御ブロックのコンテナ
	STRATEGY* PRISM_CONTROLLER = new STRATEGY(PRISM_MAG_COMBINER, this->global_->pr_mtq);
	PRISM_CONTROLLER->setStrategy(STRATEGY::TorqueCombiner, PRISM_TORQUE_COMBINER);
	PRISM_CONTROLLER->setStrategy(STRATEGY::MagCombiner, PRISM_MAG_COMBINER);
	PRISM_CONTROLLER->setStrategy(STRATEGY::CrossProduct, PRISM_CROSSPRODUCT);
	PRISM_CONTROLLER->setStrategy(STRATEGY::LiniarCorrection, PRISM_RMMCOMP);
	PRISM_CONTROLLER->setStrategy(STRATEGY::Bdot, PRISM_BDOT);
	PRISM_CONTROLLER->setStrategy(STRATEGY::Decoupling, PRISM_DECOUPLING);
	PRISM_CONTROLLER->setStrategy(STRATEGY::RateDumping, PRISM_RATEDUMPING);
	PRISM_CONTROLLER->setStrategy(STRATEGY::PID, PRISM_PID);
	PRISM_CONTROLLER->setStrategy(STRATEGY::PD, PRISM_PD);
	PRISM_CONTROLLER->setStrategy(STRATEGY::GGComp, PRISM_GGCOMP);
	PRISM_CONTROLLER->setStrategy(STRATEGY::EKF, PRISM_EKF);
	PRISM_CONTROLLER->setStrategy(STRATEGY::TRIAD, PRISM_TRIAD);
	PRISM_CONTROLLER->setStrategy(STRATEGY::RMMEKF, PRISM_RMMEKF);
	
	// 磁気モーメント合成
	PRISM_MAG_COMBINER->connect_source<0>(PRISM_CROSSPRODUCT);
	PRISM_MAG_COMBINER->connect_source<1>(PRISM_BDOT);
	PRISM_MAG_COMBINER->connect_source<2>(PRISM_RMMCOMP);

	// 残留磁気補償
	// input: RMMEKF -> MagneticMoment
	PRISM_RMMCOMP->connect_source<0>(PRISM_RMMEKF);

	// B-Dot
	// input: TAM -> MagneticMoment
	PRISM_BDOT->connect_source<0>(this->global_->pr_tam);

	// Cross-Product
	// input: TorqueCombiner -> Torque
	//        TAM            -> MagneticMoment
	PRISM_CROSSPRODUCT->connect_source<0>(PRISM_TORQUE_COMBINER);
	PRISM_CROSSPRODUCT->connect_source<1>(this->global_->pr_tam);
	
	// トルク合成
	PRISM_TORQUE_COMBINER->connect_source<0>(PRISM_DECOUPLING);
	PRISM_TORQUE_COMBINER->connect_source<1>(PRISM_RATEDUMPING);
	PRISM_TORQUE_COMBINER->connect_source<2>(PRISM_PID);
	PRISM_TORQUE_COMBINER->connect_source<3>(PRISM_GGCOMP);
	PRISM_TORQUE_COMBINER->connect_source<4>(PRISM_PD);

	// Decoupling
	// input: EKF            -> Omega
	PRISM_DECOUPLING->connect_source<0>(PRISM_EKF);

	// Rate-Dumping
	// input: EKF            -> Omega
	PRISM_RATEDUMPING->connect_source<0>(PRISM_EKF);
	
	// PID/PD(Earth-pointing)
	// input: EKF                  -> Quaternion
	//        EKF                  -> Omega
	//        GPSDummy(TLE Uplink) -> Position
	PRISM_PID->connect_source<0>(PRISM_EKF);
	PRISM_PID->connect_source<1>(PRISM_EKF);
	PRISM_PID->connect_source<2>(this->global_->pr_gpsdummy);
	
	PRISM_PD->connect_source<0>(PRISM_EKF);
	PRISM_PD->connect_source<1>(PRISM_EKF);
	PRISM_PD->connect_source<2>(this->global_->pr_gpsdummy);

	// Gravity-Gradient Compensation
	// input: EKF                  -> Quaternion
	//        GPSDummy(TLE Uplink) -> Position
	PRISM_GGCOMP->connect_source<0>(PRISM_EKF);
	PRISM_GGCOMP->connect_source<1>(this->global_->pr_gpsdummy);

	// Gyro-Bias EKF
	// input: TRIAD          -> Quaternion
	//        Gyro           -> Omega
	PRISM_EKF->connect_source<0>(PRISM_TRIAD);
	PRISM_EKF->connect_source<1>(this->global_->pr_gyro);

	// TRIAD
	// input: Sunsensor            -> SunVector(body frame)
	//        TAM                  -> MagneticField(body frame)
	//        GPSDummy(TLE Uplink) -> Position
	//        Clock                -> Time
	PRISM_TRIAD->connect_source<0>(this->global_->pr_ss);
	PRISM_TRIAD->connect_source<1>(this->global_->pr_tam);
	PRISM_TRIAD->connect_source<2>(this->global_->pr_gpsdummy);
	PRISM_TRIAD->connect_source<3>(this->global_->pr_clock);
	
	///////////////////////////////////////////////////
	// 制御ブロックへのアクセスが必要な初期化処理

	this->global_->pr_controlstrategy = PRISM_CONTROLLER;

	// AOCSテレメトリにカルマンフィルタとTRIADのパラメータを追加
	this->global_->pr_aocstmstrategy->add_tmlist(new interface::PRISMEKFIterator<1000>(PRISM_EKF));
	this->global_->pr_aocstmstrategy->add_tmlist(new interface::PRISMRMMEKFIterator<1000>(PRISM_RMMEKF));
	this->global_->pr_aocstmstrategy->add_tmlist(new interface::PRISMSunMagTRIADIterator<1000>(PRISM_TRIAD));

	//　AOCS系コマンド
	datatype::Time t_init = this->global_->pr_clock->get_time();

	this->global_->pr_c_aen0 = new command::SimpleMemberFunctionCommand<STRATEGY, void>(t_init,PRISM_CONTROLLER,&STRATEGY::enable);

	this->global_->pr_c_aen1 = new command::SimpleMemberFunctionCommand<STRATEGY, void>(t_init,PRISM_CONTROLLER,&STRATEGY::disable);

	this->global_->pr_c_ams = new command::TypeListMemberFunctionCommand<STRATEGY, int, 2>
		(t_init,PRISM_CONTROLLER,&STRATEGY::set_mode, 0, 0);

	this->global_->pr_c_amG = new command::IteratorStreamCommand<1>(t_init, new interface::PRISMControlBlockIterator(PRISM_CONTROLLER));

	///////////////////////////////////////////////////
	// 制御則をモードに登録
	this->global_->pr_amode->add_list<core::strategy::control::IControlStrategy>(PRISM_CONTROLLER);
}

template<class Env>
void PRISMFactory<Env>::create_command(){
	typedef core::manager::HeaterControl<Env> Heater;
	typedef core::devicedriver::clock::PRISMDummyClock<Env> Clock;
	typedef core::strategy::telemetry::PRISMTelemetryStrategy<Env, 1000> Telem;
	typedef core::manager::ModeManagerBase ModeManager;
	datatype::Time t_init = this->global_->pr_clock->get_time();

	// 生存確認
	this->global_->pr_c_alv = new core::command::MessageCommand(t_init, "alive");

	// ヒーター制御関係
	this->global_->pr_c_hta = 
		new core::command::SimpleMemberFunctionCommand<Heater, void>
		(t_init, this->global_->pr_heater,&Heater::enable);

	this->global_->pr_c_htd = 
		new core::command::SimpleMemberFunctionCommand<Heater, void>
		(t_init, this->global_->pr_heater,&Heater::disable);

	this->global_->pr_c_htg = 
		new core::command::GetCommand<Heater, datatype::String>
		(t_init, this->global_->pr_heater,&Heater::get_status);

	this->global_->pr_c_hts = 
		new core::command::TypeListMemberFunctionCommand<Heater, int, 3>
		(t_init, this->global_->pr_heater,&Heater::set_params, 0, 0, 0);

	// 時刻設定・時刻取得関係
	this->global_->pr_c_rtg = 
		new core::command::GetIteratorCommand<Clock, interface::DateTimeIterator, const datatype::DateTime, 100>(t_init, this->global_->pr_clock,&Clock::get_datetime);

	this->global_->pr_c_tmg = 
		new core::command::GetIteratorCommand<Clock, interface::TimeIterator, const datatype::Time, 100>(t_init, this->global_->pr_clock,&Clock::get_time);

	this->global_->pr_c_rts = 
		new core::command::TypeListMemberFunctionCommand<Clock, int, 6>
		(t_init, this->global_->pr_clock,&Clock::set_absolute_time, 0, 0, 0, 0, 0, 0);

	this->global_->pr_c_tms = 
		new core::command::TypeListMemberFunctionCommand<Clock, int, 2>
		(t_init, this->global_->pr_clock,&Clock::set_time, 0, 0);

	//CDHテレメ
	this->global_->pr_c_tlg = 
		new core::command::IteratorStreamCommand<100>(t_init, this->global_->pr_telemetryiterator);

	this->global_->pr_c_sgs = 
		new core::command::IteratorStreamCommand<100>(t_init, this->global_->pr_statusiterator);

	this->global_->pr_c_trs =
		new core::command::TypeListMemberFunctionCommand<Telem, int, 6>
		(t_init, this->global_->pr_tmstrategy,&Telem::setRTCTime, 0, 0, 0, 0, 0, 0);

	this->global_->pr_c_tos = 
		new core::command::UnAryMemberFunctionCommand<Telem, void, int>
		(t_init, this->global_->pr_tmstrategy,&Telem::set_time, 0);

	//電源系
	//this->global_->pr_c_pd = 
	//	new core::command::SwitchCommand();
	
	//this->global_->pr_c_pu = 
	//	new core::command::SwitchCommand();	

	this->global_->pr_c_mds = 
		new core::command::modeChangeCommand(t_init, this->global_->pr_safemode, this->global_->pr_modeman);

	this->global_->pr_c_mdn = 
		new core::command::modeChangeCommand(t_init, this->global_->pr_amode, this->global_->pr_modeman);

	this->global_->pr_c_md = 
		new core::command::GetCommand<ModeManager, const datatype::String&>(t_init, this->global_->pr_modeman, &ModeManager::get_current_modename);

	this->global_->pr_c_hth = 
		new core::command::GetCommand<Heater, datatype::String>
		(t_init, this->global_->pr_battheater,&Heater::get_status);

	this->global_->pr_c_hdt = 
		new core::command::TypeListMemberFunctionCommand<Heater, int, 3>
		(t_init, this->global_->pr_battheater,&Heater::set_params, 0, 0, 0);

	//AOCS系->一部はcontrollerHotSpotでインスタンス化
	this->global_->pr_c_atw = new core::command::UnAryMemberFunctionCommand<Telem, void, bool>
		(t_init, this->global_->pr_aocstmstrategy,&Telem::setstate, false);

	this->global_->pr_c_atg = new core::command::IteratorStreamCommand<100>(t_init, this->global_->pr_aocstelemetryiterator);

	this->global_->pr_c_atr = new core::command::TypeListMemberFunctionCommand<Telem, int, 6>
		(t_init, this->global_->pr_aocstmstrategy,&Telem::setRTCTime, 0, 0, 0, 0, 0, 0);

	this->global_->pr_c_ato = 
		new core::command::UnAryMemberFunctionCommand<Telem, void, int>
		(t_init, this->global_->pr_aocstmstrategy,&Telem::set_time, 0);
}

template<class Env>
void PRISMFactory<Env>::create_telemetry(){
	this->global_->pr_tmstrategy = new core::strategy::telemetry::PRISMTelemetryStrategy<Env, 1000>(this->global_->pr_tmhandler, this->global_->pr_aocsdatapool, this->global_->pr_eventdatapool, this->global_->pr_clock);
	this->global_->pr_aocstmstrategy = new core::strategy::telemetry::PRISMTelemetryStrategy<Env, 1000>(this->global_->pr_tmhandler, this->global_->pr_aocsdatapool, this->global_->pr_eventdatapool, this->global_->pr_clock);
	///////////////////////////////////////////////////
	// テレメトリストラテジをモードに登録
	this->global_->pr_safemode->add_list<core::strategy::telemetry::ITelemetryStrategy>(this->global_->pr_tmstrategy);
	this->global_->pr_dpmode->add_list<core::strategy::telemetry::ITelemetryStrategy>(this->global_->pr_tmstrategy);
	this->global_->pr_dsmode->add_list<core::strategy::telemetry::ITelemetryStrategy>(this->global_->pr_tmstrategy);
	this->global_->pr_dmode->add_list<core::strategy::telemetry::ITelemetryStrategy>(this->global_->pr_tmstrategy);
	this->global_->pr_amode->add_list<core::strategy::telemetry::ITelemetryStrategy>(this->global_->pr_tmstrategy);
	this->global_->pr_resetmode->add_list<core::strategy::telemetry::ITelemetryStrategy>(this->global_->pr_tmstrategy);

	this->global_->pr_safemode->add_list<core::strategy::telemetry::ITelemetryStrategy>(this->global_->pr_aocstmstrategy);
	this->global_->pr_dpmode->add_list<core::strategy::telemetry::ITelemetryStrategy>(this->global_->pr_aocstmstrategy);
	this->global_->pr_dsmode->add_list<core::strategy::telemetry::ITelemetryStrategy>(this->global_->pr_aocstmstrategy);
	this->global_->pr_dmode->add_list<core::strategy::telemetry::ITelemetryStrategy>(this->global_->pr_aocstmstrategy);
	this->global_->pr_amode->add_list<core::strategy::telemetry::ITelemetryStrategy>(this->global_->pr_aocstmstrategy);
	this->global_->pr_resetmode->add_list<core::strategy::telemetry::ITelemetryStrategy>(this->global_->pr_aocstmstrategy);
}

template<class Env>
void PRISMFactory<Env>::create_dataupdates(){
	datatype::List<core::devicedriver::IDataUpdatable> defaultUpdateList;
	defaultUpdateList.add(*this->global_->pr_clock);
	defaultUpdateList.add(*this->global_->pr_gpsdummy);
	defaultUpdateList.add(*this->global_->pr_gyro);
	defaultUpdateList.add(*this->global_->pr_tam);
	defaultUpdateList.add(*this->global_->pr_tempsensor);
	defaultUpdateList.add(*this->global_->pr_currentsensor);
	defaultUpdateList.add(*this->global_->pr_voltagesensor);

	datatype::List<core::devicedriver::IDataUpdatable>::iterator it = defaultUpdateList.begin();

	while(it != defaultUpdateList.end()){
		this->global_->pr_amode->add_list(&(*it));
		this->global_->pr_dmode->add_list(&(*it));
		this->global_->pr_dpmode->add_list(&(*it));
		this->global_->pr_dsmode->add_list(&(*it));
		this->global_->pr_resetmode->add_list(&(*it));
		this->global_->pr_safemode->add_list(&(*it));
		++it;
	}

	// AMode
	this->global_->pr_amode->add_list((core::devicedriver::IDataUpdatable*)(this->global_->pr_mtq));
	// DMode
	this->global_->pr_dmode->add_list((core::devicedriver::IDataUpdatable*)(this->global_->pr_mtq));
	// DPMode
	this->global_->pr_dpmode->add_list((core::devicedriver::IDataUpdatable*)(this->global_->pr_mtq));
	// DSMode
	this->global_->pr_dsmode->add_list((core::devicedriver::IDataUpdatable*)(this->global_->pr_mtq));
}

template<class Env>
void PRISMFactory<Env>::create_switches(){
	datatype::List<core::devicedriver::ISwitchable> defaultSwitchList;
	defaultSwitchList.add(*this->global_->pr_clock);
	defaultSwitchList.add(*this->global_->pr_gpsdummy);
	defaultSwitchList.add(*this->global_->pr_gyro);
	defaultSwitchList.add(*this->global_->pr_tam);
	defaultSwitchList.add(*this->global_->pr_tempsensor);
	defaultSwitchList.add(*this->global_->pr_currentsensor);
	defaultSwitchList.add(*this->global_->pr_voltagesensor);

	datatype::List<core::devicedriver::ISwitchable>::iterator it = defaultSwitchList.begin();

	while(it != defaultSwitchList.end()){
		this->global_->pr_amode->add_list(&(*it));
		this->global_->pr_dmode->add_list(&(*it));
		this->global_->pr_dpmode->add_list(&(*it));
		this->global_->pr_dsmode->add_list(&(*it));
		this->global_->pr_resetmode->add_list(&(*it));
		this->global_->pr_safemode->add_list(&(*it));
		++it;
	}

	// AMode
	this->global_->pr_amode->add_list((core::devicedriver::ISwitchable*)(this->global_->pr_mtq));
	// DMode
	this->global_->pr_dmode->add_list((core::devicedriver::ISwitchable*)(this->global_->pr_mtq));
	// DPMode
	this->global_->pr_dpmode->add_list((core::devicedriver::ISwitchable*)(this->global_->pr_mtq));
	// DSMode
	this->global_->pr_dsmode->add_list((core::devicedriver::ISwitchable*)(this->global_->pr_mtq));
}

template<class Env>
void PRISMFactory<Env>::create_functor(){
	////////////////////////////////
	// モード変更関係のファンクタ

	//一定時間が経過したらSafeModeに移行するファンクタ
	core::functor::IFunctor* timerfunc = new functor::Functor<functor::Getter_Over<datatype::Time, devicedriver::clock::ITimeClock>, core::functor::ModeChangeFunc>
			(
				new functor::Getter_Over<datatype::Time, devicedriver::clock::ITimeClock>(
					this->global_->pr_clock,&devicedriver::clock::ITimeClock::get_time, new datatype::Time(200, 0)
					),
					new functor::ModeChangeFunc(this->global_->pr_modeman,*(this->global_->pr_safemode))
			);
	this->global_->pr_resetmode->add_list(timerfunc);

	//EventDataPoolのAnomaryEventが一定数溜まったらSafeModeに移行するファンクタ

	//撮影予約時刻に到達したらDPModeに移行するファンクタ

	//撮影完了したらDSModeに移行するファンクタ

	//////////////////////////////////
	//  アノマリー関係のファンクタ
}

template<class Env>
void PRISMFactory<Env>::create_additional_hotspot(){

}

template<class Env>
void PRISMFactory<Env>::create_datapool(){
	this->global_->pr_mtqx->connect(global_->pr_aocsdatapool, 10, "PR_MTQ1");
	this->global_->pr_mtqy->connect(global_->pr_aocsdatapool, 10, "PR_MTQ2");
	this->global_->pr_mtqz->connect(global_->pr_aocsdatapool, 10, "PR_MTQ3");
	this->global_->pr_mtq->connect(global_->pr_aocsdatapool, 10, "PR_MTQ");

	this->global_->pr_gyrox->connect(global_->pr_aocsdatapool, 20, "PR_GYRO1");
	this->global_->pr_gyroy->connect(global_->pr_aocsdatapool, 20, "PR_GYRO2");
	this->global_->pr_gyroz->connect(global_->pr_aocsdatapool, 20, "PR_GYRO3");
	this->global_->pr_gyro->connect(global_->pr_aocsdatapool, 20, "PR_GYRO");

	this->global_->pr_ss->connect(global_->pr_aocsdatapool, 20, "PR_SS");

	this->global_->pr_tam->connect(global_->pr_aocsdatapool, 20, "PR_TAM");	
}


} /* End of namespace stf::core::factory */
} /* End of namespace stf::core */ 
} /* End of namespace stf */

#endif // factory_PRISMFactory_h