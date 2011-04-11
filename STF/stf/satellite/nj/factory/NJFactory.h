/**
 * @file   NJFactory.h
 * @brief  Nano-JASMINEのオブジェクトを生成するファクトリ．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef factory_NJFactory_h
#define factory_NJFactory_h

#include "NJGlobal.h"

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

#include "../../../core/strategy/telemetry/Includes.h"

#include "../NJfwd.h"

namespace stf {
namespace core {
namespace factory {

template<class Env, class App = app::NJ>
class NJFactory : public SatelliteFactory<Env, App, NJFactory<Env, App> >{
	friend class SatelliteFactory<Env, App, NJFactory<Env, App> >;
	typedef Env Environment;//!< 環境クラス．
	typedef App Application;//!< アプリケーションクラス．


	NJFactory(){ this->global_ = new NJGlobal<Env>();}
	virtual ~NJFactory(){ delete this->global_; }

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

	NJGlobal<Env>* global_;
};

template<class Env, class App>
void NJFactory<Env, App>::create_mode(){
	this->global_->nj_sfem = new core::mode::Mode("NJ_SAFEMODE");
	this->global_->nj_stbm = new core::mode::Mode("NJ_STBMODE");
	this->global_->nj_inim = new core::mode::Mode("NJ_INITIALMODE");
	this->global_->nj_ctrm = new core::mode::Mode("NJ_COARSECONTROLMODE");
	this->global_->nj_ccdm = new core::mode::Mode("NJ_FINECONTROLMODE");
	this->global_->nj_mism = new core::mode::Mode("NJ_MISSIONMODE");
	this->global_->nj_rwum = new core::mode::Mode("NJ_UNLOADINGMODE");
	this->global_->nj_estm_fog = new core::mode::Mode("NJ_ESTM_FOG");
	this->global_->nj_estm_rmm = new core::mode::Mode("NJ_ESTM_RMM");
	this->global_->nj_estm_rw = new core::mode::Mode("NJ_ESTM_RW");
	this->global_->nj_estm_mc = new core::mode::Mode("NJ_ESTM_MC");
}

template<class Env, class App>
void NJFactory<Env, App>::create_component(){
	typedef devicedriver::mtq::NJMTQ<Env> MTQ;
	typedef devicedriver::CompositeOutput<MTQ, 3> ThreeAxisMTQ;
	typedef devicedriver::mtq::NJMC<Env> MC;
	typedef devicedriver::CompositeOutput<MC, 3> ThreeAxisMC;
	typedef devicedriver::rw::NJRW<Env> RW;
	typedef devicedriver::CompositeOutput<RW, 4, true> SkewRW;
	typedef devicedriver::stt::NJSTT<Env> STT;
	typedef devicedriver::CompositeInput<STT, 2> TwoAxisSTT;
	typedef devicedriver::sunsensor::NJSunSensor<Env> Sunsensor;
	typedef devicedriver::CompositeInput<Sunsensor, 6> SixAxisSunsensor;
	typedef devicedriver::clock::NJRTC<Env> RTC;
	typedef devicedriver::gps::NJGPS<Env> GPS;
	typedef devicedriver::gyro::NJGyro<Env> GYRO;
	typedef devicedriver::CompositeInput<GYRO, 3> ThreeAxisGyro;
	typedef devicedriver::gyro::NJFOG<Env> FOG;
	typedef devicedriver::CompositeInput<FOG, 3> ThreeAxisFOG;
	typedef devicedriver::magnetometer::NJCoarseTAM<Env> ST4;
	typedef devicedriver::magnetometer::NJFineTAM<Env> ST5;

	//DataPool
	this->global_->nj_aocsdatapool = new core::datapool::AocsDataPool();
	this->global_->nj_eventdatapool = new core::datapool::EventDataPool();

	// MTQ
	this->global_->nj_mtqx = new MTQ(datatype::TypeConverter::toDCM(0, -90, 0));
	this->global_->nj_mtqy = new MTQ(datatype::TypeConverter::toDCM(0, 0, 90));
	this->global_->nj_mtqz = new MTQ(datatype::TypeConverter::toDCM(0, 0, 0));
	this->global_->nj_mtq = new ThreeAxisMTQ(datatype::TypeConverter::toDCM(0, 0, 0));
	this->global_->nj_mtq->append_child(this->global_->nj_mtqx);
	this->global_->nj_mtq->append_child(this->global_->nj_mtqy);
	this->global_->nj_mtq->append_child(this->global_->nj_mtqz);

	//MC
	this->global_->nj_mcx = new MC(datatype::TypeConverter::toDCM(0,-90, 0));
	this->global_->nj_mcy = new MC(datatype::TypeConverter::toDCM(0, 0, 90));
	this->global_->nj_mcz = new MC(datatype::TypeConverter::toDCM(0, 0, 0));
	this->global_->nj_mc = new ThreeAxisMC(datatype::TypeConverter::toDCM(0, 0, 0));
	this->global_->nj_mc->append_child(this->global_->nj_mcx);
	this->global_->nj_mc->append_child(this->global_->nj_mcy);
	this->global_->nj_mc->append_child(this->global_->nj_mcz);

	// Gyro
	this->global_->nj_gyrox = new GYRO(datatype::TypeConverter::toDCM(0,-90, 0));
	this->global_->nj_gyroy = new GYRO(datatype::TypeConverter::toDCM(0, 0, 90));
	this->global_->nj_gyroz = new GYRO(datatype::TypeConverter::toDCM(0, 0, 0));
	this->global_->nj_gyro =  new ThreeAxisGyro(datatype::TypeConverter::toDCM(0, 0, 0));
	this->global_->nj_gyro->append_child(this->global_->nj_gyrox);
	this->global_->nj_gyro->append_child(this->global_->nj_gyroy);
	this->global_->nj_gyro->append_child(this->global_->nj_gyroz);

	this->global_->nj_fogx = new FOG(datatype::TypeConverter::toDCM(0,-90, 0));
	this->global_->nj_fogy = new FOG(datatype::TypeConverter::toDCM(0, 0, 90));
	this->global_->nj_fogz = new FOG(datatype::TypeConverter::toDCM(0, 0, 0));
	this->global_->nj_fog =  new ThreeAxisFOG(datatype::TypeConverter::toDCM(0, 0, 0));
	this->global_->nj_fog->append_child(this->global_->nj_fogx);
	this->global_->nj_fog->append_child(this->global_->nj_fogy);
	this->global_->nj_fog->append_child(this->global_->nj_fogz);

	// Sun Sensor
	this->global_->nj_sspx = new Sunsensor(datatype::TypeConverter::toDCM(0,-90, 0));
	this->global_->nj_sspy = new Sunsensor(datatype::TypeConverter::toDCM(0, 0, 90));
	this->global_->nj_sspz = new Sunsensor(datatype::TypeConverter::toDCM(0, 0, 0));
	this->global_->nj_ssmx = new Sunsensor(datatype::TypeConverter::toDCM(180,-90, 0));
	this->global_->nj_ssmy = new Sunsensor(datatype::TypeConverter::toDCM(180, 0, 90));
	this->global_->nj_ssmz = new Sunsensor(datatype::TypeConverter::toDCM(180, 0, 0));
	this->global_->nj_ss = new SixAxisSunsensor(datatype::TypeConverter::toDCM(0, 0, 0));
	this->global_->nj_ss->append_child(this->global_->nj_sspx);
	this->global_->nj_ss->append_child(this->global_->nj_sspy);
	this->global_->nj_ss->append_child(this->global_->nj_sspz);
	this->global_->nj_ss->append_child(this->global_->nj_ssmx);
	this->global_->nj_ss->append_child(this->global_->nj_ssmy);
	this->global_->nj_ss->append_child(this->global_->nj_ssmz);

	// MagnetoMeter
	this->global_->nj_st4 = new ST4(datatype::TypeConverter::toDCM(0, 0, 0));
	this->global_->nj_st5 = new ST5(datatype::TypeConverter::toDCM(0, 0, 0));

	// Star Tracker
	this->global_->nj_sttx = new STT(datatype::TypeConverter::toDCM(0,-90, 0));
	this->global_->nj_stty = new STT(datatype::TypeConverter::toDCM(0, 0, 0));
	this->global_->nj_stt = new TwoAxisSTT(datatype::TypeConverter::toDCM(0, 0, 0));
	this->global_->nj_stt->append_child(this->global_->nj_sttx);
	this->global_->nj_stt->append_child(this->global_->nj_stty);

	// Reaction Wheel
	this->global_->nj_rw1 = new RW(datatype::TypeConverter::toDCM(0, 0, 0));
	this->global_->nj_rw2 = new RW(datatype::TypeConverter::toDCM(0, 0, 0));
	this->global_->nj_rw3 = new RW(datatype::TypeConverter::toDCM(0, 0, 0));
	this->global_->nj_rw4 = new RW(datatype::TypeConverter::toDCM(0, 0, 0));
	this->global_->nj_rw  = new SkewRW(datatype::TypeConverter::toDCM(0, 0, 0));
	this->global_->nj_rw->append_child(this->global_->nj_rw1);
	this->global_->nj_rw->append_child(this->global_->nj_rw2);
	this->global_->nj_rw->append_child(this->global_->nj_rw3);
	this->global_->nj_rw->append_child(this->global_->nj_rw4);

	// GPS,RTC
	this->global_->nj_rtc = new RTC(App::year, App::month, App::date);
	this->global_->nj_gps = new GPS();

	// ADC, 温度計，電圧計，電流計
	this->global_->nj_adc  = new devicedriver::NJADC<Env>();
	this->global_->nj_temp1 = new devicedriver::NJCoarseTempSensor<Env>(global_->nj_adc);
	this->global_->nj_temp2 = new devicedriver::NJFineTempSensor<Env>(global_->nj_adc);
	this->global_->nj_currentsensor = new devicedriver::NJCurrentSensor<Env>(global_->nj_adc);
	this->global_->nj_voltagesensor = new devicedriver::NJVoltageSensor<Env>(global_->nj_adc);

	// SDCard, Command Recv
	this->global_->nj_tmhandler = new devicedriver::tmhandler::NJTelemetryHandler<Env>("NJTelemetry.csv", false);
	this->global_->nj_commandreceiver = new devicedriver::cmhandler::NJCommandReceiver<Env>(this->global_->nj_commman, "command.txt", this->global_);

	// Other Components
	this->global_->nj_tdi = new devicedriver::nj::NJTDI<Env>();
	this->global_->nj_batterymanager = new devicedriver::nj::NJBatteryManager<Env>();
	this->global_->nj_battheater = new devicedriver::nj::NJHeaterManager<Env>();
	this->global_->nj_rx = new devicedriver::nj::NJRX<Env>();
	this->global_->nj_tx = new devicedriver::nj::NJTX<Env>();
}

template<class Env, class App>
void NJFactory<Env, App>::create_funcmanager(){
	this->global_->nj_modeman = new core::manager::ModeManagerBase();
	this->global_->nj_conman = new core::manager::ControlManagerBase();
	this->global_->nj_uniman1 = new core::manager::UnitManagerBase();
	this->global_->nj_uniman2 = new core::manager::UnitManagerBase();
	this->global_->nj_telman = new core::manager::TelemetryManagerBase();
	this->global_->nj_sysman = new core::manager::SystemManagerBase();
	this->global_->nj_commman = new core::manager::CommandManagerBase();

	this->global_->add_function_manager(this->global_->nj_modeman);
	this->global_->add_function_manager(this->global_->nj_conman);
	this->global_->add_function_manager(this->global_->nj_uniman1);
	this->global_->add_function_manager(this->global_->nj_uniman2);
	this->global_->add_function_manager(this->global_->nj_telman);
	this->global_->add_function_manager(this->global_->nj_sysman);
	this->global_->add_function_manager(this->global_->nj_commman);
}

template<class Env, class App>
void NJFactory<Env, App>::create_controller(){
	typedef core::strategy::control::ControlBlock CONTROLLER;
	typedef core::strategy::control::PID SimplePID;
	typedef core::strategy::control::DynamicPID PID;
	typedef core::strategy::control::NJSunMagTRIAD TRIAD;
	typedef core::strategy::control::SolarPointing SOLAR_POINTING;
	typedef core::strategy::control::CrossProduct CROSS_PRODUCT;
	typedef core::strategy::control::NJEKF EKF;
	typedef core::strategy::control::NJRMMEKF RMMEKF;
	typedef core::strategy::control::nj::QuaternionAveraging QUATERNION_AVE;
	typedef core::strategy::control::RateDumping RATE_DUMPING;
	typedef core::strategy::control::LiniarCorrection<datatype::MagneticMoment> RMMCOMP;
	typedef core::strategy::control::Combining_3<datatype::MagneticMoment> MAG_COMBINE_3;
	typedef core::strategy::control::Combining_2<datatype::MagneticMoment> MAG_COMBINE_2;
	typedef core::strategy::control::nj::StarImageEKF STAR_EKF;
	typedef core::strategy::control::nj::LongRangeSpinController SPINAXIS_CONTROLLER;
	typedef core::strategy::control::nj::MidRangeSpinController MIDRANGE_SPINCONTROLLER;
	typedef core::strategy::control::WheelUnloading<Env> UNLOADING;
	typedef core::strategy::control::nj::QuaternionForRMMEstimation QUATERNION_RMMESTM;
	typedef core::strategy::control::nj::MCConstantOutput MC_CONSTANT;
	typedef core::strategy::control::nj::RWConstantOutput RW_CONSTANT;

	CONTROLLER* NJ_CONTROLLER_SFEM = new CONTROLLER();
	CONTROLLER* NJ_CONTROLLER_INIM = new CONTROLLER();
	CONTROLLER* NJ_CONTROLLER_CTRM = new CONTROLLER();
	CONTROLLER* NJ_CONTROLLER_CCDM = new CONTROLLER();
	CONTROLLER* NJ_CONTROLLER_MISM = new CONTROLLER();
	CONTROLLER* NJ_CONTROLLER_RWUM = new CONTROLLER();
	CONTROLLER* NJ_CONTROLLER_STBM = new CONTROLLER();
	CONTROLLER* NJ_CONTROLLER_ESTM_FOG = new CONTROLLER();
	CONTROLLER* NJ_CONTROLLER_ESTM_RMM = new CONTROLLER();
	CONTROLLER* NJ_CONTROLLER_ESTM_RW = new CONTROLLER();
	CONTROLLER* NJ_CONTROLLER_ESTM_MC = new CONTROLLER();

	/////////////////////////////////////
	// セーフモード用の姿勢制御ブロック
	// 姿勢決定:なし
	// 姿勢制御:なし
	this->global_->nj_sfem->add_list<core::strategy::control::IControlStrategy>(NJ_CONTROLLER_SFEM);

	/////////////////////////////////////
	// スタンバイモード用の姿勢制御ブロック
	// 姿勢決定:なし
	// 姿勢制御:磁気センサのみの太陽捕捉制御(制御ハンドブック9.3.3.3)
	SOLAR_POINTING* stbm_pointing = new SOLAR_POINTING(1);

	stbm_pointing->connect_source<0>(this->global_->nj_st4);
	stbm_pointing->connect_source<1>(this->global_->nj_ss);

	NJ_CONTROLLER_STBM->set_actuator(this->global_->nj_mtq, stbm_pointing);
	this->global_->nj_stbm->add_list<core::strategy::control::IControlStrategy>(NJ_CONTROLLER_STBM);

	//////////////////////////////////////
    // 初期安定化モード用の姿勢制御ブロック
	// 姿勢決定:なし(角速度のみ取得)
	// 姿勢制御:Date-Dumping + CrossProduct
	RATE_DUMPING* inim_ratedumping = new RATE_DUMPING(1, 0.1, 0.1, App::steptime);
	CROSS_PRODUCT* inim_crossproduct = new CROSS_PRODUCT();

	inim_ratedumping->connect_source<0>(this->global_->nj_gyro);

	inim_crossproduct->connect_source<0>(inim_ratedumping);
	inim_crossproduct->connect_source<1>(this->global_->nj_st4);

	NJ_CONTROLLER_INIM->set_actuator(this->global_->nj_mtq, inim_crossproduct);
	this->global_->nj_inim->add_list<core::strategy::control::IControlStrategy>(NJ_CONTROLLER_INIM);

	//////////////////////////////////////
    // 粗姿勢制御モード用の姿勢制御ブロック
	// 姿勢決定:ST4 & SunsensorTRIAD(EKFなし) + EKF(FOG)
	// 姿勢制御:Quaternion FB
	TRIAD* ctrm_triad = new TRIAD();
	EKF* ctrm_ekf = new EKF(this->global_->nj_mism);
	SimplePID* ctrm_pid = new SimplePID(1, 0.01, 0.5, App::steptime, *(new datatype::Quaternion));
	CROSS_PRODUCT* ctrm_crossproduct = new CROSS_PRODUCT();

	ctrm_crossproduct->connect_source<0>(ctrm_pid);
	ctrm_crossproduct->connect_source<1>(this->global_->nj_st4);

	ctrm_pid->connect_source<0>(ctrm_ekf);
	ctrm_pid->connect_source<1>(ctrm_ekf);//TRIADから直接QuaternionをとるのではなくEKFを挟むことで，蝕時にはFOGからの伝搬値が自動的に用いられる

	ctrm_ekf->connect_source<0>(ctrm_triad);
	ctrm_ekf->connect_source<1>(this->global_->nj_fog);

	ctrm_triad->connect_source<0>(this->global_->nj_ss);
	ctrm_triad->connect_source<1>(this->global_->nj_st4);
	ctrm_triad->connect_source<2>(this->global_->nj_gps);

	NJ_CONTROLLER_CTRM->set_actuator(this->global_->nj_mtq, ctrm_crossproduct);
	this->global_->nj_ctrm->add_list<core::strategy::control::IControlStrategy>(NJ_CONTROLLER_CTRM);

	//////////////////////////////////////
	//精姿勢制御モード用の姿勢制御ブロック
	// 姿勢決定:STT-FOG EKF & RMM補償
	// 姿勢制御:
	EKF* ccdm_ekf = new EKF(this->global_->nj_mism);//->推定値を引き継ぐので観測モードでも使う
	RMMEKF* ccdm_rmmekf = new RMMEKF();//->推定値を引き継ぐので観測モードでも使う
	QUATERNION_AVE* ccdm_q_average = new QUATERNION_AVE();
	RMMCOMP* ccdm_rmmcomp = new RMMCOMP(-1);
	PID* ccdm_pid = new PID(0.1, 0.001, 0.004, App::steptime);

	ccdm_rmmcomp->connect_source<0>(ccdm_rmmekf);

	ccdm_rmmekf->connect_source<0>(this->global_->nj_st5);
	ccdm_rmmekf->connect_source<1>(ccdm_ekf);

	ccdm_pid->connect_source<0>(ccdm_ekf);
	ccdm_pid->connect_source<1>(ccdm_ekf);
	

	ccdm_ekf->connect_source<0>(ccdm_q_average);
	ccdm_ekf->connect_source<1>(this->global_->nj_fog);

	ccdm_q_average->connect_source<0>(this->global_->nj_sttx);
	ccdm_q_average->connect_source<1>(this->global_->nj_stty);

	//制御トルクはRWへ出力
	NJ_CONTROLLER_CCDM->set_actuator(this->global_->nj_rw, ccdm_pid);
	//推定された残留磁気モーメントの補償成分は磁気キャンセラへ出力
	NJ_CONTROLLER_CCDM->set_actuator(this->global_->nj_mc, ccdm_rmmcomp);

	this->global_->nj_ccdm->add_list<core::strategy::control::IControlStrategy>(NJ_CONTROLLER_CCDM);

	////////////////////////////////////
	//観測モード用の姿勢制御ブロック．星像EKFやスピン軸の長期制御を除いて精制御モードの制御ブロックを引き継ぐ
	// 姿勢決定：星像EKF?
	// 姿勢制御：
	STAR_EKF* mism_starekf = new STAR_EKF();
	PID* mism_pid = new PID(0.1, 0.001, 0.004, App::steptime);
	SPINAXIS_CONTROLLER* mism_spincond = new SPINAXIS_CONTROLLER();

	mism_pid->connect_source<0>(ccdm_ekf);//QuaternionはジャイロバイアスEKFから取得
	mism_pid->connect_source<1>(mism_starekf);//角速度は星像EKFから取得．星像取得失敗時にはジャイロバイアスEKFの値がそのまま伝搬される
	mism_pid->connect_source<2>(mism_spincond);//長期要求に基づいて目標Quaterionを更新

	mism_starekf->connect_source<0>(ccdm_ekf);
	//mism_starekf->connect_source<1>(this->global_->nj_rw);

	//制御トルクはRWへ出力
	NJ_CONTROLLER_MISM->set_actuator(this->global_->nj_rw, mism_pid);
	//RMMは精制御モードと同じ経路でキャンセラへ
	NJ_CONTROLLER_MISM->set_actuator(this->global_->nj_mc, ccdm_rmmcomp);

	//////////////////////////////////////
	//アンローディングモード用の姿勢制御ブロック
	// 姿勢決定：STT-サンセンサQUEST
	// 姿勢制御：MTQ-RW分散
	UNLOADING* unloading = new UNLOADING();
	CROSS_PRODUCT* unloading_crossp = new CROSS_PRODUCT();
	
	unloading->add_wheel(this->global_->nj_rw1);
	unloading->add_wheel(this->global_->nj_rw2);
	unloading->add_wheel(this->global_->nj_rw3);
	unloading->add_wheel(this->global_->nj_rw4);
	
	unloading->connect_source<0>(this->global_->nj_gps);

	unloading_crossp->connect_source<0>(&unloading->outputport<1, datatype::StaticVector<3>>());

	NJ_CONTROLLER_RWUM->set_actuator(this->global_->nj_rw, &unloading->outputport<0, datatype::StaticVector<3>>());
	NJ_CONTROLLER_RWUM->set_actuator(this->global_->nj_mtq, unloading_crossp);

	/////////////////////////////////////
	// RMM推定用の姿勢制御ブロック
	// 姿勢決定：STT-FOG EKF
	// 姿勢制御：6面一定時間ずつ太陽指向制御
	PID* estmrmm_pid = new PID(0.1, 0.01, 0.01, App::steptime);
	datatype::Time t(1000, 0);
	QUATERNION_RMMESTM* estmrmm_q = new QUATERNION_RMMESTM(this->global_->nj_rtc, t);//1000秒ごとに別の面を太陽指向させる

	estmrmm_pid->connect_source<0>(ccdm_ekf);
	estmrmm_pid->connect_source<1>(ccdm_ekf);
	estmrmm_pid->connect_source<2>(estmrmm_q);

	NJ_CONTROLLER_ESTM_RMM->set_actuator(this->global_->nj_rw, estmrmm_pid);
	this->global_->nj_estm_rmm->add_list<core::strategy::control::IControlStrategy>(NJ_CONTROLLER_ESTM_RMM);

	/////////////////////////////////////
	// FOG推定用の姿勢制御ブロック
	// 姿勢決定：STT-FOG EKF
	// 姿勢制御：FOG3軸それぞれ±1e-3rad/s,±1e-2rad/sの計12モード
	PID* estmfog_pid = new PID(0.1, 0.01, 0.01, App::steptime);

	NJ_CONTROLLER_ESTM_FOG->set_actuator(this->global_->nj_rw, estmfog_pid);
	this->global_->nj_estm_fog->add_list<core::strategy::control::IControlStrategy>(NJ_CONTROLLER_ESTM_FOG);

	/////////////////////////////////////
	// MC推定用の姿勢制御ブロック
	// 姿勢決定：STT-FOG EKF
	// 姿勢制御：MC3軸それぞれ±0.2Am2,±0.4Am2,±0.6Am2の計18モード
	MC_CONSTANT* estmmc = new MC_CONSTANT(this->global_->nj_rtc, t);

	NJ_CONTROLLER_ESTM_MC->set_actuator(this->global_->nj_mc, estmmc);
	this->global_->nj_estm_mc->add_list<core::strategy::control::IControlStrategy>(NJ_CONTROLLER_ESTM_MC);

	/////////////////////////////////////
	// RW推定用の姿勢制御ブロック
	// 姿勢決定：STT-FOG EKF
	// 姿勢制御：RW4基それぞれ±5e-5Nm,±2.5e-5Nmの計16モード
	RW_CONSTANT* estmrw = new RW_CONSTANT(this->global_->nj_rtc, t);

	//NJ_CONTROLLER_ESTM_RW->set_actuator(this->global_->nj_rw1, &estmrw->outputport<0, datatype::StaticVector<3>>());
	this->global_->nj_estm_rw->add_list<core::strategy::control::IControlStrategy>(NJ_CONTROLLER_ESTM_RW);

	///////////////////////////////////////////////////
	// 制御ブロックへのアクセスが必要な初期化処理

	// EKFの状態量をテレメトリに出力
	this->global_->nj_telemetrystrategy->add_tmlist(new interface::NJEKFIterator<1000>(ccdm_ekf));
	this->global_->nj_telemetrystrategy->add_tmlist(new interface::NJRMMEKFIterator<1000>(ccdm_rmmekf));
	this->global_->nj_telemetrystrategy->add_tmlist(new interface::NJSunMagTRIADIterator<1000>(ctrm_triad));

	///////////////////////////////////////////////////
	// 制御則をモードに登録
	this->global_->nj_sfem->add_list<core::strategy::control::IControlStrategy>(NJ_CONTROLLER_SFEM);
	this->global_->nj_inim->add_list<core::strategy::control::IControlStrategy>(NJ_CONTROLLER_INIM);
	this->global_->nj_ctrm->add_list<core::strategy::control::IControlStrategy>(NJ_CONTROLLER_CTRM);
	this->global_->nj_ccdm->add_list<core::strategy::control::IControlStrategy>(NJ_CONTROLLER_CCDM);
	this->global_->nj_mism->add_list<core::strategy::control::IControlStrategy>(NJ_CONTROLLER_MISM);
	this->global_->nj_rwum->add_list<core::strategy::control::IControlStrategy>(NJ_CONTROLLER_RWUM);
	this->global_->nj_stbm->add_list<core::strategy::control::IControlStrategy>(NJ_CONTROLLER_STBM);
	this->global_->nj_estm_fog->add_list<core::strategy::control::IControlStrategy>(NJ_CONTROLLER_ESTM_FOG);
	this->global_->nj_estm_rmm->add_list<core::strategy::control::IControlStrategy>(NJ_CONTROLLER_ESTM_RMM);
	this->global_->nj_estm_rw->add_list<core::strategy::control::IControlStrategy>(NJ_CONTROLLER_ESTM_RW);
	this->global_->nj_estm_mc->add_list<core::strategy::control::IControlStrategy>(NJ_CONTROLLER_ESTM_MC);
}

template<class Env, class App>
void NJFactory<Env, App>::create_command(){

}

template<class Env, class App>
void NJFactory<Env, App>::create_telemetry(){
	this->global_->nj_telemetrystrategy = new core::strategy::telemetry::SelectingOutput<unsigned int, 1000>
		(this->global_->nj_tmhandler, this->global_->nj_aocsdatapool, this->global_->nj_eventdatapool);

	//ADCの取得値を全チャネルテレメトリに追加
	this->global_->nj_telemetrystrategy->add_tmlist(new interface::CDHComponentIterator<Env, datatype::Voltage,NJ__ADC__CHANNELS>(this->global_->nj_adc));

	///////////////////////////////////////////////////
	// テレメトリストラテジをモードに登録
	this->global_->nj_sfem->add_list<core::strategy::telemetry::ITelemetryStrategy>(this->global_->nj_telemetrystrategy);
	this->global_->nj_inim->add_list<core::strategy::telemetry::ITelemetryStrategy>(this->global_->nj_telemetrystrategy);
	this->global_->nj_ctrm->add_list<core::strategy::telemetry::ITelemetryStrategy>(this->global_->nj_telemetrystrategy);
	this->global_->nj_ccdm->add_list<core::strategy::telemetry::ITelemetryStrategy>(this->global_->nj_telemetrystrategy);
	this->global_->nj_mism->add_list<core::strategy::telemetry::ITelemetryStrategy>(this->global_->nj_telemetrystrategy);
	this->global_->nj_rwum->add_list<core::strategy::telemetry::ITelemetryStrategy>(this->global_->nj_telemetrystrategy);
	this->global_->nj_stbm->add_list<core::strategy::telemetry::ITelemetryStrategy>(this->global_->nj_telemetrystrategy);
	this->global_->nj_estm_rmm->add_list<core::strategy::telemetry::ITelemetryStrategy>(this->global_->nj_telemetrystrategy);
	this->global_->nj_estm_rw->add_list<core::strategy::telemetry::ITelemetryStrategy>(this->global_->nj_telemetrystrategy);
	this->global_->nj_estm_fog->add_list<core::strategy::telemetry::ITelemetryStrategy>(this->global_->nj_telemetrystrategy);
	this->global_->nj_estm_mc->add_list<core::strategy::telemetry::ITelemetryStrategy>(this->global_->nj_telemetrystrategy);
}

template<class Env, class App>
void NJFactory<Env, App>::create_dataupdates(){
	// 全モード共通でONの機器は最初にまとめてリストに加える
	datatype::List<core::devicedriver::IDataUpdatable> defaultUpdateList;
	defaultUpdateList.add(*this->global_->nj_rtc);
	defaultUpdateList.add(*this->global_->nj_adc);
	defaultUpdateList.add(*this->global_->nj_currentsensor);
	defaultUpdateList.add(*this->global_->nj_voltagesensor);
	defaultUpdateList.add(*this->global_->nj_temp1);
	defaultUpdateList.add(*this->global_->nj_temp2);
	defaultUpdateList.add(*this->global_->nj_batterymanager);
	defaultUpdateList.add(*this->global_->nj_battheater);
	defaultUpdateList.add(*this->global_->nj_rx);

	datatype::List<core::devicedriver::IDataUpdatable>::iterator it = defaultUpdateList.begin();
	while(it != defaultUpdateList.end()){
		this->global_->nj_sfem->add_list<core::devicedriver::IDataUpdatable>(&(*it));
		this->global_->nj_stbm->add_list<core::devicedriver::IDataUpdatable>(&(*it));
		this->global_->nj_ctrm->add_list<core::devicedriver::IDataUpdatable>(&(*it));
		this->global_->nj_ccdm->add_list<core::devicedriver::IDataUpdatable>(&(*it));
		this->global_->nj_mism->add_list<core::devicedriver::IDataUpdatable>(&(*it));
		this->global_->nj_rwum->add_list<core::devicedriver::IDataUpdatable>(&(*it));
		this->global_->nj_estm_fog->add_list<core::devicedriver::IDataUpdatable>(&(*it));
		this->global_->nj_estm_rmm->add_list<core::devicedriver::IDataUpdatable>(&(*it));
		this->global_->nj_estm_rw->add_list<core::devicedriver::IDataUpdatable>(&(*it));
		this->global_->nj_estm_mc->add_list<core::devicedriver::IDataUpdatable>(&(*it));
		++it;
	}
	//以下各モード固有のコンポーネント群

	//Safe Mode ->defaultのみ

	//Standby Mode
	this->global_->nj_stbm->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_ss));
	this->global_->nj_stbm->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_gyro));
	this->global_->nj_stbm->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_st4));
	this->global_->nj_stbm->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_gps));

	//Coarse Control Mode
	this->global_->nj_ctrm->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_ss));
	this->global_->nj_ctrm->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_gyro));
	this->global_->nj_ctrm->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_st4));
	this->global_->nj_ctrm->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_gps));
	this->global_->nj_ctrm->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_mtq));

	//Fine Control Mode
	this->global_->nj_ccdm->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_stt));
	this->global_->nj_ccdm->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_rw));
	this->global_->nj_ccdm->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_fog));
	this->global_->nj_ccdm->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_st5));
	this->global_->nj_ccdm->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_gps));
	this->global_->nj_ccdm->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_mc));
	this->global_->nj_ccdm->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_tdi));

	//Mission Mode
	this->global_->nj_mism->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_stt));
	this->global_->nj_mism->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_rw));
	this->global_->nj_mism->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_fog));
	this->global_->nj_mism->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_st5));
	this->global_->nj_mism->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_gps));
	this->global_->nj_mism->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_mc));
	this->global_->nj_mism->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_tdi));

	//Unloading Mode
	this->global_->nj_rwum->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_stt));
	this->global_->nj_rwum->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_rw));
	this->global_->nj_rwum->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_fog));
	this->global_->nj_rwum->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_st4));
	this->global_->nj_rwum->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_gps));
	this->global_->nj_rwum->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_mc));
	this->global_->nj_rwum->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_mtq));

	//Estimation Mode - RMM
	this->global_->nj_estm_rmm->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_fog));
	this->global_->nj_estm_rmm->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_stt));
	this->global_->nj_estm_rmm->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_mc));
	this->global_->nj_estm_rmm->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_st5));
	this->global_->nj_estm_rmm->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_gps));

	//Estimation Mode - FOG
	this->global_->nj_estm_fog->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_fog));
	this->global_->nj_estm_fog->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_stt));
	this->global_->nj_estm_fog->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_mc));
	this->global_->nj_estm_fog->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_rw));
	this->global_->nj_estm_fog->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_st5));
	this->global_->nj_estm_fog->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_gps));
	this->global_->nj_estm_fog->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_mtq));

	//Estimation Mode - MC
	this->global_->nj_estm_mc->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_fog));
	this->global_->nj_estm_mc->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_stt));
	this->global_->nj_estm_mc->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_mc));
	this->global_->nj_estm_mc->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_rw));
	this->global_->nj_estm_mc->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_st5));
	this->global_->nj_estm_mc->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_gps));

	//Estimation Mode - RW
	this->global_->nj_estm_rw->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_fog));
	this->global_->nj_estm_rw->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_stt));
	this->global_->nj_estm_rw->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_mc));
	this->global_->nj_estm_rw->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_rw));
	this->global_->nj_estm_rw->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_st5));
	this->global_->nj_estm_rw->add_list<core::devicedriver::IDataUpdatable>((core::devicedriver::IDataUpdatable*)(this->global_->nj_gps));

}

template<class Env, class App>
void NJFactory<Env, App>::create_switches(){
	// 全モード共通でONの機器は最初にまとめてリストに加える
	datatype::List<core::devicedriver::ISwitchable> defaultSwitchList;
	defaultSwitchList.add(*this->global_->nj_rtc);
	defaultSwitchList.add(*this->global_->nj_adc);
	defaultSwitchList.add(*this->global_->nj_currentsensor);
	defaultSwitchList.add(*this->global_->nj_voltagesensor);
	defaultSwitchList.add(*this->global_->nj_temp1);
	defaultSwitchList.add(*this->global_->nj_temp2);
	defaultSwitchList.add(*this->global_->nj_batterymanager);
	defaultSwitchList.add(*this->global_->nj_battheater);
	defaultSwitchList.add(*this->global_->nj_rx);

	datatype::List<core::devicedriver::ISwitchable>::iterator it = defaultSwitchList.begin();
	while(it != defaultSwitchList.end()){
		this->global_->nj_sfem->add_list<core::devicedriver::ISwitchable>(&(*it));
		this->global_->nj_stbm->add_list<core::devicedriver::ISwitchable>(&(*it));
		this->global_->nj_ctrm->add_list<core::devicedriver::ISwitchable>(&(*it));
		this->global_->nj_ccdm->add_list<core::devicedriver::ISwitchable>(&(*it));
		this->global_->nj_mism->add_list<core::devicedriver::ISwitchable>(&(*it));
		this->global_->nj_rwum->add_list<core::devicedriver::ISwitchable>(&(*it));
		this->global_->nj_estm_fog->add_list<core::devicedriver::ISwitchable>(&(*it));
		this->global_->nj_estm_rmm->add_list<core::devicedriver::ISwitchable>(&(*it));
		this->global_->nj_estm_rw->add_list<core::devicedriver::ISwitchable>(&(*it));
		this->global_->nj_estm_mc->add_list<core::devicedriver::ISwitchable>(&(*it));
		++it;
	}
	//以下各モード固有のコンポーネント群

	//Safe Mode ->defaultのみ

	//Standby Mode
	this->global_->nj_stbm->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_ss));
	this->global_->nj_stbm->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_gyro));
	this->global_->nj_stbm->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_st4));
	this->global_->nj_stbm->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_gps));

	//Coarse Control Mode
	this->global_->nj_ctrm->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_ss));
	this->global_->nj_ctrm->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_gyro));
	this->global_->nj_ctrm->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_st4));
	this->global_->nj_ctrm->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_gps));
	this->global_->nj_ctrm->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_mtq));

	//Fine Control Mode
	this->global_->nj_ccdm->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_stt));
	this->global_->nj_ccdm->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_rw));
	this->global_->nj_ccdm->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_fog));
	this->global_->nj_ccdm->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_st5));
	this->global_->nj_ccdm->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_gps));
	this->global_->nj_ccdm->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_mc));
	this->global_->nj_ccdm->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_tdi));

	//Mission Mode
	this->global_->nj_mism->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_stt));
	this->global_->nj_mism->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_rw));
	this->global_->nj_mism->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_fog));
	this->global_->nj_mism->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_st5));
	this->global_->nj_mism->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_gps));
	this->global_->nj_mism->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_mc));
	this->global_->nj_mism->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_tdi));

	//Unloading Mode
	this->global_->nj_rwum->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_stt));
	this->global_->nj_rwum->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_rw));
	this->global_->nj_rwum->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_fog));
	this->global_->nj_rwum->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_st4));
	this->global_->nj_rwum->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_gps));
	this->global_->nj_rwum->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_mc));
	this->global_->nj_rwum->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_mtq));

	//Estimation Mode - RMM
	this->global_->nj_estm_rmm->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_fog));
	this->global_->nj_estm_rmm->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_stt));
	this->global_->nj_estm_rmm->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_mc));
	this->global_->nj_estm_rmm->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_st5));
	this->global_->nj_estm_rmm->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_gps));

	//Estimation Mode - FOG
	this->global_->nj_estm_fog->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_fog));
	this->global_->nj_estm_fog->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_stt));
	this->global_->nj_estm_fog->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_mc));
	this->global_->nj_estm_fog->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_rw));
	this->global_->nj_estm_fog->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_st5));
	this->global_->nj_estm_fog->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_gps));
	this->global_->nj_estm_fog->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_mtq));

	//Estimation Mode - MC
	this->global_->nj_estm_mc->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_fog));
	this->global_->nj_estm_mc->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_stt));
	this->global_->nj_estm_mc->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_mc));
	this->global_->nj_estm_mc->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_rw));
	this->global_->nj_estm_mc->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_st5));
	this->global_->nj_estm_mc->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_gps));

	//Estimation Mode - RW
	this->global_->nj_estm_rw->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_fog));
	this->global_->nj_estm_rw->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_stt));
	this->global_->nj_estm_rw->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_mc));
	this->global_->nj_estm_rw->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_rw));
	this->global_->nj_estm_rw->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_st5));
	this->global_->nj_estm_rw->add_list<core::devicedriver::ISwitchable>((core::devicedriver::ISwitchable*)(this->global_->nj_gps));

}

template<class Env, class App>
void NJFactory<Env, App>::create_functor(){
	////////////////////////////////
	// モード変更関係のファンクタ
	
	//MEMSジャイロの値が0.001rad/s以下になったら初期安定化モード→粗姿勢制御モードへ
	this->global_->nj_inim->add_list<functor::IFunctor>(
		new functor::Functor<functor::Is_Under<datatype::StaticVector<3>>, functor::ModeChangeFunc>
			(
			new functor::Is_Under<datatype::StaticVector<3>>(this->global_->nj_aocsdatapool, this->global_->nj_gyro->get_datapoolKey(), 0.001),
			new functor::ModeChangeFunc(this->global_->nj_modeman, *this->global_->nj_ctrm)
			)
		);

	//MEMSジャイロの値が0.002rad/s以上になったら粗姿勢制御モード→初期安定化モードへ
	this->global_->nj_ctrm->add_list<functor::IFunctor>(
		new functor::Functor<functor::Is_Over<datatype::StaticVector<3>>, functor::ModeChangeFunc>
			(
			new functor::Is_Over<datatype::StaticVector<3>>(this->global_->nj_aocsdatapool, this->global_->nj_gyro->get_datapoolKey(), 0.002),
			new functor::ModeChangeFunc(this->global_->nj_modeman, *this->global_->nj_inim)
			)
		);

	//FOGの値が0.0001rad/s以下になったら粗姿勢制御モード→精姿勢制御モードへ
	this->global_->nj_ctrm->add_list<functor::IFunctor>(
		new functor::Functor<functor::Is_Under<datatype::StaticVector<3>>, functor::ModeChangeFunc>
			(
			new functor::Is_Under<datatype::StaticVector<3>>(this->global_->nj_aocsdatapool, this->global_->nj_fog->get_datapoolKey(), 0.0001),
			new functor::ModeChangeFunc(this->global_->nj_modeman, *this->global_->nj_ccdm)
			)
		);

	//FOGの値が0.0002rad/s以上になったら精姿勢制御モード→粗姿勢制御モードへ
	this->global_->nj_ccdm->add_list<functor::IFunctor>(
		new functor::Functor<functor::Is_Over<datatype::StaticVector<3>>, functor::ModeChangeFunc>
			(
			new functor::Is_Over<datatype::StaticVector<3>>(this->global_->nj_aocsdatapool, this->global_->nj_fog->get_datapoolKey(), 0.0002),
			new functor::ModeChangeFunc(this->global_->nj_modeman, *this->global_->nj_ctrm)
			)
		);

	//FOGの値が0.00001rad/s以下になったら精姿勢制御モード→観測モードへ
	this->global_->nj_ctrm->add_list<functor::IFunctor>(
		new functor::Functor<functor::Is_Under<datatype::StaticVector<3>>, functor::ModeChangeFunc>
			(
			new functor::Is_Under<datatype::StaticVector<3>>(this->global_->nj_aocsdatapool, this->global_->nj_fog->get_datapoolKey(), 0.00001),
			new functor::ModeChangeFunc(this->global_->nj_modeman, *this->global_->nj_ccdm)
			)
		);

	//FOGの値が0.00002rad/s以上になったら観測モード→精姿勢制御モードへ
	this->global_->nj_ccdm->add_list<functor::IFunctor>(
		new functor::Functor<functor::Is_Over<datatype::StaticVector<3>>, functor::ModeChangeFunc>
			(
			new functor::Is_Over<datatype::StaticVector<3>>(this->global_->nj_aocsdatapool, this->global_->nj_fog->get_datapoolKey(), 0.00002),
			new functor::ModeChangeFunc(this->global_->nj_modeman, *this->global_->nj_ctrm)
			)
		);
	typedef devicedriver::rw::RWBase<Env> RW;

	//RWが1つでも飽和したらアンローディングモードへ
	functor::IFunctor* rwfunc1 = new functor::Functor<functor::Getter_Is<RW>, functor::ModeChangeFunc>
		(
			new functor::Getter_Is<RW>(this->global_->nj_rw1, &RW::is_saturated),
			new functor::ModeChangeFunc(this->global_->nj_modeman, *this->global_->nj_ctrm)
		);
	functor::IFunctor* rwfunc2 = new functor::Functor<functor::Getter_Is<RW>, functor::ModeChangeFunc>
		(
			new functor::Getter_Is<RW>(this->global_->nj_rw2, &RW::is_saturated),
			new functor::ModeChangeFunc(this->global_->nj_modeman, *this->global_->nj_ctrm)
		);
	functor::IFunctor* rwfunc3 = new functor::Functor<functor::Getter_Is<RW>, functor::ModeChangeFunc>
		(
			new functor::Getter_Is<RW>(this->global_->nj_rw3, &RW::is_saturated),
			new functor::ModeChangeFunc(this->global_->nj_modeman, *this->global_->nj_ctrm)
		);
	functor::IFunctor* rwfunc4 = new functor::Functor<functor::Getter_Is<RW>, functor::ModeChangeFunc>
		(
			new functor::Getter_Is<RW>(this->global_->nj_rw4, &RW::is_saturated),
			new functor::ModeChangeFunc(this->global_->nj_modeman, *this->global_->nj_ctrm)
		);

	this->global_->nj_mism->add_list(rwfunc1);
	this->global_->nj_mism->add_list(rwfunc2);
	this->global_->nj_mism->add_list(rwfunc3);
	this->global_->nj_mism->add_list(rwfunc4);

	this->global_->nj_ctrm->add_list(rwfunc1);
	this->global_->nj_ctrm->add_list(rwfunc2);
	this->global_->nj_ctrm->add_list(rwfunc3);
	this->global_->nj_ctrm->add_list(rwfunc4);

	this->global_->nj_ccdm->add_list(rwfunc1);
	this->global_->nj_ccdm->add_list(rwfunc2);
	this->global_->nj_ccdm->add_list(rwfunc3);
	this->global_->nj_ccdm->add_list(rwfunc4);

	//RWの角運動量が解放されたらふたたび粗制御モードへ
}

template<class Env, class App>
void NJFactory<Env, App>::create_additional_hotspot(){

}

template<class Env, class App>
void NJFactory<Env, App>::create_datapool(){
	this->global_->nj_mtqx->connect(global_->nj_aocsdatapool, 10, "NJ_MTQ1");
	this->global_->nj_mtqy->connect(global_->nj_aocsdatapool, 10, "NJ_MTQ2");
	this->global_->nj_mtqz->connect(global_->nj_aocsdatapool, 10, "NJ_MTQ3");
	this->global_->nj_mtq->connect(global_->nj_aocsdatapool, 10, "NJ_MTQ");

	this->global_->nj_sttx->connect(global_->nj_aocsdatapool, 10, "NJ_STTX");
	this->global_->nj_stty->connect(global_->nj_aocsdatapool, 10, "NJ_STTY");
	this->global_->nj_stt->connect(global_->nj_aocsdatapool, 10, "NJ_STT");

	this->global_->nj_rw1->connect(global_->nj_aocsdatapool, 10, "NJ_RW1");
	this->global_->nj_rw2->connect(global_->nj_aocsdatapool, 10, "NJ_RW2");
	this->global_->nj_rw3->connect(global_->nj_aocsdatapool, 10, "NJ_RW3");
	this->global_->nj_rw4->connect(global_->nj_aocsdatapool, 10, "NJ_RW4");
	this->global_->nj_rw->connect(global_->nj_aocsdatapool, 10, "NJ_RW");

	this->global_->nj_fogx->connect(global_->nj_aocsdatapool, 10, "NJ_FOGX");
	this->global_->nj_fogy->connect(global_->nj_aocsdatapool, 10, "NJ_FOGY");
	this->global_->nj_fogz->connect(global_->nj_aocsdatapool, 10, "NJ_FOGZ");
	this->global_->nj_fog->connect(global_->nj_aocsdatapool, 10, "NJ_FOG");

	this->global_->nj_gyrox->connect(global_->nj_aocsdatapool, 10, "NJ_GYROX");
	this->global_->nj_gyroy->connect(global_->nj_aocsdatapool, 10, "NJ_GYROY");
	this->global_->nj_gyroz->connect(global_->nj_aocsdatapool, 10, "NJ_GYROZ");
	this->global_->nj_gyro->connect(global_->nj_aocsdatapool, 10, "NJ_GYRO");

	this->global_->nj_st4->connect(global_->nj_aocsdatapool, 10, "NJ_ST4");
	this->global_->nj_st5->connect(global_->nj_aocsdatapool, 10, "NJ_ST5");

	//this->global_->nj_gps->connect(global_->nj_aocsdatapool, 10, "NJ_GPS");
}

} /* End of namespace stf::core::factory */
} /* End of namespace stf::core */ 
} /* End of namespace stf */




#endif // factory_NJFactory_h