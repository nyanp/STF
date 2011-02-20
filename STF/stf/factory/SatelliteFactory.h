/**
 * @file   SatelliteFactory.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef factory_SatelliteFactory_h
#define factory_SatelliteFactory_h

#include "../GlobalObject.h"

namespace stf {
namespace factory {

template<class Env>
class SatelliteFactory {
public:
	SatelliteFactory(){}
	virtual ~SatelliteFactory(){}
	Global<Env>* create(){
		create_component();
		create_datapool();
		create_funcmanager();
		create_mode();
	    create_command();
		create_telemetry();
		create_controller();

		create_functor();
		create_dataupdates();
		create_switches();
		create_additional_hotspot();

		return return_created_object();
	}
protected:
	// デバイスドライバを生成するファクトリ
	virtual void create_component() = 0;
	// 機能マネージャを生成するファクトリ
	virtual void create_funcmanager() = 0;
	// モードを生成するファクトリ
	virtual void create_mode() = 0;
	// 各モードにおけるControl Strategyを生成するファクトリ
	virtual void create_controller() = 0;
	// Commandを生成するファクトリ
	virtual void create_command() = 0;
	// 各モードにおけるTelemetry Strategyを生成するファクトリ
	virtual void create_telemetry() = 0;
	// 各モードにおけるFunctor Strategyを生成するファクトリ
	virtual void create_functor() = 0;
	// 各モードにおけるUpdate Strategyを生成するファクトリ
	virtual void create_dataupdates() = 0;
	// 各モードにおけるSwitch Strategyを生成するファクトリ
	virtual void create_switches() = 0;
	// 各モードにおけるユーザー定義のStrategyを生成するファクトリ
	virtual void create_additional_hotspot() = 0;
	// データプールへの接続を生成するファクトリ
	virtual void create_datapool() = 0;
	// 生成されたオブジェクトを、Globalのポインタで返却
	virtual Global<Env>* return_created_object() = 0;
};

} /* End of namespace stf::factory */
} /* End of namespace stf */


#endif // factory_SatelliteFactory_h