/**
 * @file   PRISMGlobal.h
 * @brief  PRISMのオブジェクト群を保持するクラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef satellite_prism_PRISMGlobal_h
#define satellite_prism_PRISMGlobal_h
#include "../../../GlobalObject.h"

#include "../../../core/devicedriver/Includes.h"
#include "../../../core/manager/Includes.h"
#include "../../../core/datapool/Datapool.h"
#include "../../../core/mode/Mode.h"
#include "../../../core/strategy/control/IControlStrategy.h"
#include "../../../core/strategy/telemetry/ITelemetryStrategy.h"
#include "../../../datatype/SatelliteModel.h"

#include "../strategy/includes.h"
#include "../devicedriver/includes.h"
#include "../manager/PRISMCustomManager.h"
#include "../PRISMIterator.h"

namespace stf {

template <class Env>
struct PRISMGlobal : public Global<Env>{
	//! 衛星のOBC時刻を取得
	virtual const datatype::Time get_global_time(){
		return this->pr_clock->get_time();
	}

	//! 衛星のRTC時刻を取得
	virtual const datatype::DateTime get_global_datetime(){
		return this->pr_clock->get_datetime();
	}

	//! 衛星の質量特性モデルを取得
	virtual const datatype::SatelliteModel get_satellitemodel() const{
		return this->prism_body_;
	}

	//! Aocsデータプールのハンドラを取得．
	virtual const core::datapool::AocsDataPool* get_datapool() const {
		return this->pr_aocsdatapool;
	}

	//! Eventデータプールのハンドラを取得．
	virtual const core::datapool::EventDataPool* get_eventdatapool() const {
		return this->pr_eventdatapool;
	}

	/////////////////////////////////////////////////////
	// Mass Model
	/////////////////////////////////////////////////////
	datatype::SatelliteModel prism_body_;

	/////////////////////////////////////////////////////
	// Data Pool
	/////////////////////////////////////////////////////
	datapool::AocsDataPool* pr_aocsdatapool;
	datapool::EventDataPool* pr_eventdatapool;

	/////////////////////////////////////////////////////
	// Mode
	/////////////////////////////////////////////////////
	mode::Mode* pr_safemode;
	mode::Mode* pr_dpmode;
	mode::Mode* pr_dsmode;
	mode::Mode* pr_dmode;
	mode::Mode* pr_amode;
	mode::Mode* pr_resetmode;

	/////////////////////////////////////////////////////
	// Manager
	/////////////////////////////////////////////////////
	manager::ModeManagerBase* pr_modeman;
	manager::UnitManagerBase* pr_uniman1; // 10Hz, 通常のセンサ，アクチュエータ
	manager::UnitManagerBase* pr_uniman2; // 25Hz, AD変換
	manager::ControlManagerBase* pr_conman;
	manager::TelemetryManagerBase* pr_telman1;// CDHテレメ
	manager::TelemetryManagerBase* pr_telman2;// AOCSテレメ
	manager::SystemManagerBase* pr_sysman;
	manager::CommandManagerBase* pr_commman;
	manager::PRISMCustomManager<Env>* pr_customman;

	/////////////////////////////////////////////////////
	// Strategy
	/////////////////////////////////////////////////////
	core::strategy::control::IControlStrategy* pr_controlstrategy;
	core::strategy::telemetry::PRISMTelemetryStrategy<Env, 1000>* pr_tmstrategy;
	core::strategy::telemetry::PRISMTelemetryStrategy<Env, 1000>* pr_aocstmstrategy;

	/////////////////////////////////////////////////////
	// Device Driver
	/////////////////////////////////////////////////////
	//MTQ
	devicedriver::mtq::PRISMMTQ<Env>* pr_mtqx;
	devicedriver::mtq::PRISMMTQ<Env>* pr_mtqy;
	devicedriver::mtq::PRISMMTQ<Env>* pr_mtqz;
	devicedriver::CompositeOutput<devicedriver::mtq::PRISMMTQ<Env>, 3>* pr_mtq;

	//Gyro
	devicedriver::gyro::PRISMGyro<Env>* pr_gyrox;
	devicedriver::gyro::PRISMGyro<Env>* pr_gyroy;	
	devicedriver::gyro::PRISMGyro<Env>* pr_gyroz;
	devicedriver::CompositeInput<devicedriver::gyro::PRISMGyro<Env>, 3>* pr_gyro;

	//Sun Sensor
	devicedriver::sunsensor::PRISMSunSensor<Env>* pr_sspx;
	devicedriver::sunsensor::PRISMSunSensor<Env>* pr_sspy;
	devicedriver::sunsensor::PRISMSunSensor<Env>* pr_sspz;
	devicedriver::sunsensor::PRISMSunSensor<Env>* pr_ssmx;
	devicedriver::sunsensor::PRISMSunSensor<Env>* pr_ssmy;
	devicedriver::sunsensor::PRISMSunSensor<Env>* pr_ssmz;
	devicedriver::CompositeInput<devicedriver::sunsensor::PRISMSunSensor<Env>, 6>* pr_ss;

	//Magnetrometer
	devicedriver::magnetometer::PRISMTAM<Env>* pr_tam;
	//GPS
	devicedriver::gps::DummyGPS<Env>* pr_gpsdummy;
	//
	devicedriver::clock::PRISMDummyClock<Env>* pr_clock;
	
	devicedriver::PRISMADC<Env>* pr_adc;

	devicedriver::PRISMTempSensor<Env>* pr_tempsensor;
	devicedriver::PRISMCurrentSensor<Env>* pr_currentsensor;
	devicedriver::PRISMVoltageSensor<Env>* pr_voltagesensor;

	// Command / Telemetry Handler 
	devicedriver::cmhandler::PRISMCommandReceiver<Env>* pr_commandreceiver;
	devicedriver::tmhandler::PRISMTelemetryHandler<Env>* pr_tmhandler;

	/////////////////////////////////////////////////////
	// Iterator
	/////////////////////////////////////////////////////
	// CDH/AOCSのステータスとテレメをダウンリンクするためのイテレータ
	interface::PRISMTelemetryIterator<Env, 100, 1>* pr_statusiterator;
	interface::PRISMTelemetryIterator<Env, 100, 4>* pr_telemetryiterator;
	interface::PRISMTelemetryIterator<Env, 100, 1>* pr_aocsstatusiterator;
	interface::PRISMTelemetryIterator<Env, 100, 4>* pr_aocstelemetryiterator;

	/////////////////////////////////////////////////////
	// Command-Prototypes
	/////////////////////////////////////////////////////
	// CDH
	command::Command* pr_c_alv;//生存信号
	command::Command* pr_c_hta;//ヒーター有効
	command::Command* pr_c_htd;//ヒーター無効
	command::Command* pr_c_htg;//ヒーター状態取得
	command::Command* pr_c_hts;//ヒーター状態設定
	command::Command* pr_c_rtg;//RTC時刻取得
	command::Command* pr_c_rts;//RTC時刻セット
	command::Command* pr_c_tmg;//OBC時刻取得
	command::Command* pr_c_tms;//OBC時刻セット
	command::Command* pr_c_tlg;//テレメトリ取得
	command::Command* pr_c_tos;//詳細履歴取得開始時刻の設定
	command::Command* pr_c_trs;//詳細履歴取得開始時刻の設定
	command::Command* pr_c_tss;//詳細履歴取得
	command::Command* pr_c_sgs;//ステータス取得
	// Power
	command::Command* pr_c_pd;//電源OFF
	command::Command* pr_c_pu;//電源ON
	command::Command* pr_c_mds;//セーフモード移行
	command::Command* pr_c_mdn;//ノーマルモード移行
	command::Command* pr_c_md;//モード取得
	command::Command* pr_c_hth;//電池ヒーター状態取得
	command::Command* pr_c_hdt;//電池ヒーター状態設定
	// ADCS
	command::Command* pr_c_aen0;//AOCS系有効
	command::Command* pr_c_aen1;//AOCS系無効
	command::Command* pr_c_ams;//AOCSモード変更
	command::Command* pr_c_amG;//AOCSモード取得
	command::Command* pr_c_atw;//AOCSテレメトリの有効・無効
	command::Command* pr_c_atg;//AOCSテレメトリ取得
	command::Command* pr_c_atr;//AOCSテレメトリ開始時刻の設定
	command::Command* pr_c_ato;//
	command::Command* pr_c_aps;//AOCSパラメータセット
	command::Command* pr_c_apg;//AOCSパラメータ取得
	//command::Command* pr_c_amq;
	//
	core::manager::HeaterControl<Env>* pr_heater;
	core::manager::HeaterControl<Env>* pr_battheater;
};

} /* End of namespace stf */

#endif // satellite_prism_PRISMGlobal_h