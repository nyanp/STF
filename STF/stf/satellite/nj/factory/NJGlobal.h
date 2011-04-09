/**
 * @file   NJGlobal.h
 * @brief  Nano-JASMINEのオブジェクト群を保持するクラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef satellite_nj_NJGlobal_h
#define satellite_nj_NJGlobal_h
#include "../../../GlobalObject.h"

#include "../../../core/devicedriver/Includes.h"
#include "../../../core/manager/Includes.h"
#include "../../../core/strategy/telemetry/SelectingOutput.h"

#include "../../../datatype/SatelliteModel.h"

#include "../strategy/includes.h"
#include "../devicedriver/includes.h"


namespace stf {

template <class Env>
struct NJGlobal : public Global<Env>{
	//! 衛星のOBC時刻を取得
	virtual const datatype::Time get_global_time(){
		return this->nj_rtc->get_time();
	}

	//! 衛星のRTC時刻を取得
	virtual const datatype::DateTime get_global_datetime(){
		return this->nj_gps->get_datetime();
	}

	//! 衛星の質量特性モデルを取得
	virtual const datatype::SatelliteModel get_satellitemodel() const{
		return this->nj_body_;
	}

	//! Aocsデータプールのハンドラを取得．
	virtual const core::datapool::AocsDataPool* get_datapool() const {
		return this->nj_aocsdatapool;
	}

	//! Eventデータプールのハンドラを取得．
	virtual const core::datapool::EventDataPool* get_eventdatapool() const {
		return this->nj_eventdatapool;
	}

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
	typedef devicedriver::clock::NJRTC RTC;
	typedef devicedriver::gps::NJGPS<Env> GPS;
	typedef devicedriver::gyro::NJGyro<Env> Gyro;
	typedef devicedriver::CompositeInput<Gyro, 3> ThreeAxisGyro;
	typedef devicedriver::gyro::NJFOG<Env> FOG;
	typedef devicedriver::CompositeInput<FOG, 3> ThreeAxisFOG;
	typedef devicedriver::magnetometer::NJCoarseTAM<Env> ST4;
	typedef devicedriver::magnetometer::NJFineTAM<Env> ST5;

	/////////////////////////////////////////////////////
	// Mass Model
	/////////////////////////////////////////////////////
	datatype::SatelliteModel nj_body_;

	/////////////////////////////////////////////////////
	// Data Pool
	/////////////////////////////////////////////////////
	datapool::AocsDataPool* nj_aocsdatapool;
	datapool::EventDataPool* nj_eventdatapool;


	/////////////////////////////////////////////////////
	// Mode
	/////////////////////////////////////////////////////
	mode::Mode* nj_sfem;
	mode::Mode* nj_stbm;
	mode::Mode* nj_inim;
	mode::Mode* nj_ctrm;
	mode::Mode* nj_ccdm;
	mode::Mode* nj_mism;
	mode::Mode* nj_rwum;
	mode::Mode* nj_estm_rmm;
	mode::Mode* nj_estm_rw;
	mode::Mode* nj_estm_fog;
	mode::Mode* nj_estm_mc;

	//Manager
	manager::ModeManager* nj_modeman;
	manager::UnitManager* nj_uniman1; // 10Hz, 通常のセンサ，アクチュエータ
	manager::UnitManager* nj_uniman2; // 10Hz, 通常のセンサ，アクチュエータ
	manager::ControlManager* nj_conman;
	manager::TelemetryManager* nj_telman;
	manager::CustomManager* nj_cusman;
	manager::SystemManager* nj_sysman;
	manager::CommandManager* nj_commman;

	//Control Strategy

	//Telemetry Strategy
	core::strategy::telemetry::SelectingOutput<unsigned int, 1000>* nj_telemetrystrategy;

	//Clock Device
	RTC* nj_rtc;
	GPS* nj_gps;

	//MTQ
	MTQ* nj_mtqx;
	MTQ* nj_mtqy;
	MTQ* nj_mtqz;
	ThreeAxisMTQ* nj_mtq;

	MC* nj_mcx;
	MC* nj_mcy;
	MC* nj_mcz;
	ThreeAxisMC* nj_mc;

	//RW
	RW* nj_rw1;
	RW* nj_rw2;
	RW* nj_rw3;
	RW* nj_rw4;
	SkewRW* nj_rw;

	//Gyro
	Gyro* nj_gyrox;
	Gyro* nj_gyroy;
	Gyro* nj_gyroz;
	ThreeAxisGyro* nj_gyro;

	FOG* nj_fogx;
	FOG* nj_fogy;
	FOG* nj_fogz;
	ThreeAxisFOG* nj_fog;

	//Sun Sensor
	Sunsensor* nj_sspx;
	Sunsensor* nj_sspy;
	Sunsensor* nj_sspz;
	Sunsensor* nj_ssmx;
	Sunsensor* nj_ssmy;
	Sunsensor* nj_ssmz;
	SixAxisSunsensor* nj_ss;

	//STT 
	STT* nj_sttx;
	STT* nj_stty;
	TwoAxisSTT* nj_stt;

	//Magnetrometer
	ST4* nj_st4;
	ST5* nj_st5;

	//ADC Sensors
	core::devicedriver::NJADC<Env>* nj_adc;//センサ類のためのデジタル値を取得するAD変換器
	core::devicedriver::NJCoarseTempSensor<Env>* nj_temp1;//2線式温度計
	core::devicedriver::NJFineTempSensor<Env>* nj_temp2;//4線式温度計
	core::devicedriver::NJVoltageSensor<Env>* nj_voltagesensor;//電圧センサ
	core::devicedriver::NJCurrentSensor<Env>* nj_currentsensor;//電流センサ

	// Command / Telemetry Handler 
	core::devicedriver::cmhandler::NJCommandReceiver<Env>* nj_commandreceiver;
	core::devicedriver::tmhandler::NJTelemetryHandler<Env>* nj_tmhandler;

	// Other Components
	core::devicedriver::nj::NJRX<Env>* nj_rx;
	core::devicedriver::nj::NJTX<Env>* nj_tx;
	core::devicedriver::nj::NJTDI<Env>* nj_tdi;
	core::devicedriver::nj::NJBatteryManager<Env>* nj_batterymanager;
	core::devicedriver::nj::NJHeaterManager<Env>* nj_battheater;

	// Command-Prototypes

};

} /* End of namespace stf */

#endif // satellite_nj_NJGlobal_h