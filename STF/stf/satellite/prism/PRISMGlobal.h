/**
 * @file   PRISMGlobal.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef satellite_prism_PRISMGlobal_h
#define satellite_prism_PRISMGlobal_h
#include "../../GlobalObject.h"

#include "../../core/devicedriver/Includes.h"
#include "../../core/manager/Includes.h"

#include "../../datatype/SatelliteModel.h"

#include "PRISMADC.h"
#include "PRISMDummyClock.h"
#include "PRISMGyro.h"
#include "PRISMSunSensor.h"
#include "PRISMTAM.h"
#include "PRISMMTQ.h"
#include "PRISMEKF.h"
#include "PRISMRMMEKF.h"
#include "PRISMTRIAD.h"
#include "PRISMCommandReceiver.h"
#include "PRISMTelemetryHandler.h"
#include "PRISMCustomManager.h"
#include "PRISMIterator.h"
#include "PRISMTelemetryStrategy.h"
#include "PRISMControlBlock.h"

namespace stf {

namespace environment{
class Simulator;

class NullEnv;
} /* End of namespace stf::environment */

namespace util {
class Null;
}

namespace datatype {
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
class ModeBase;
} /* End of namespace stf::core::mode */
namespace event {
class EventBase;
} /* End of namespace stf::core::event */
namespace strategy {
class StrategyBase;
namespace telemetry {
class ITelemetryStrategy;
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

} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

namespace stf {
namespace factory {
template <class Env> class PRISMFactory;
}

template <class Env>
struct PRISMGlobal : public Global<Env>{

	virtual const datatype::Time getGlobalTime(){
		return this->pr_clock->getTime();
	}
	virtual const datatype::DateTime getGlobalDateTime(){
		return this->pr_clock->getAbsoluteTime();
	}
	virtual const datatype::SatelliteModel getSatelliteModel() const{
		return this->prism_body_;
	}
	virtual const core::datapool::AocsDataPool* getDataPool() const {
		return this->pr_aocsdatapool;
	}
	virtual const core::datapool::EventDataPool* getEventDataPool() const {
		return this->pr_eventdatapool;
	}

	//friend class factory::PRISMFactory<Env>;
	//friend core::command::Command* __prism_cdhcmd_analyze(char* cmd, int* params, int paramlength,const PRISMGlobal<Env>* g);
	//friend core::command::Command* __prism_powercmd_analyze(char* cmd, int* params, int paramlength,const PRISMGlobal<Env>* g);
	//friend core::command::Command* __prism_adcscmd_analyze(char* cmd, int* params, int paramlength,const PRISMGlobal<Env>* g);

	datatype::SatelliteModel prism_body_;
	//Data Pool
	datapool::AocsDataPool* pr_aocsdatapool;
	datapool::EventDataPool* pr_eventdatapool;


	//Mode
	mode::ModeBase* pr_safemode;
	mode::ModeBase* pr_dpmode;
	mode::ModeBase* pr_dsmode;
	mode::ModeBase* pr_dmode;
	mode::ModeBase* pr_amode;
	mode::ModeBase* pr_resetmode;

	//Manager
	manager::ModeManager* pr_modeman;
	manager::UnitManager* pr_uniman1; // 10Hz, 通常のセンサ，アクチュエータ
	manager::UnitManager* pr_uniman2; // 25Hz, AD変換
	manager::ControlManager* pr_conman;
	manager::TelemetryManager* pr_telman1;// CDHテレメ
	manager::TelemetryManager* pr_telman2;// AOCSテレメ
	manager::CustomManager* pr_cusman;
	manager::SystemManager* pr_sysman;
	manager::CommandManager* pr_commman;
	manager::PRISMCustomManager<Env>* pr_customman;

	//Control Strategy
	core::strategy::control::IControlStrategy* pr_controlstrategy;
	core::strategy::telemetry::PRISMTelemetryStrategy<1000>* pr_tmstrategy;
	core::strategy::telemetry::PRISMTelemetryStrategy<1000>* pr_aocstmstrategy;

	//MTQ
	devicedriver::mtq::PRISMMTQ<Env>* pr_mtqx;
	devicedriver::mtq::PRISMMTQ<Env>* pr_mtqy;
	devicedriver::mtq::PRISMMTQ<Env>* pr_mtqz;
	devicedriver::CompositeOutput<devicedriver::mtq::PRISMMTQ<Env>,3>* pr_mtq;

	//Gyro
	devicedriver::gyro::PRISMGyro<Env>* pr_gyrox;
	devicedriver::gyro::PRISMGyro<Env>* pr_gyroy;	
	devicedriver::gyro::PRISMGyro<Env>* pr_gyroz;
	devicedriver::CompositeInput<devicedriver::gyro::PRISMGyro<Env>,3>* pr_gyro;

	//Sun Sensor
	devicedriver::sunsensor::PRISMSunSensor<Env>* pr_sspx;
	devicedriver::sunsensor::PRISMSunSensor<Env>* pr_sspy;
	devicedriver::sunsensor::PRISMSunSensor<Env>* pr_sspz;
	devicedriver::sunsensor::PRISMSunSensor<Env>* pr_ssmx;
	devicedriver::sunsensor::PRISMSunSensor<Env>* pr_ssmy;
	devicedriver::sunsensor::PRISMSunSensor<Env>* pr_ssmz;
	devicedriver::CompositeInput<devicedriver::sunsensor::PRISMSunSensor<Env>,6>* pr_ss;

	//Magnetrometer
	devicedriver::magnetometer::PRISMTAM<Env>* pr_tam;
	//GPS
	devicedriver::gps::DummyGPS<Env>* pr_gpsdummy;
	//
	devicedriver::clock::PRISMDummyClock* pr_clock;
	
	devicedriver::PRISMADC<Env>* pr_adc;

	devicedriver::PRISMTempSensor<Env>* pr_tempsensor;
	devicedriver::PRISMCurrentSensor<Env>* pr_currentsensor;
	devicedriver::PRISMVoltageSensor<Env>* pr_voltagesensor;

	// Command / Telemetry Handler 
	devicedriver::cmhandler::PRISMCommandReceiver<Env>* pr_commandreceiver;
	devicedriver::tmhandler::PRISMTelemetryHandler<Env>* pr_tmhandler;
	// CDH/AOCSのステータスとテレメをダウンリンクするためのイテレータ
	interface::PRISMTelemetryIterator<100,1>* pr_statusiterator;
	interface::PRISMTelemetryIterator<100,4>* pr_telemetryiterator;
	interface::PRISMTelemetryIterator<100,1>* pr_aocsstatusiterator;
	interface::PRISMTelemetryIterator<100,4>* pr_aocstelemetryiterator;

	// Command-Prototypes
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
	command::Command* pr_c_aen1;//
	command::Command* pr_c_ams;//AOCSモード変更
	//command::Command* pr_c_amS;//AOCSモードヘンコウ
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