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
		createComponent();
		createDataPoolConnection();
		createFunctionManager();
		createMode();
	    createCommandHotSpot();
		createTelemetryHotSpot();
		createControlHotSpot();

		createFunctorHotSpot();
		createDataUpdateHotSpot();
		createSwitchHotSpot();
		createAdditionalHotSpot();

		return returnCreatedObject();
	}
protected:
	// デバイスドライバを生成するファクトリ
	virtual void createComponent() = 0;
	// 機能マネージャを生成するファクトリ
	virtual void createFunctionManager() = 0;
	// モードを生成するファクトリ
	virtual void createMode() = 0;
	// 各モードにおけるControl Strategyを生成するファクトリ
	virtual void createControlHotSpot() = 0;
	// Commandを生成するファクトリ
	virtual void createCommandHotSpot() = 0;
	// 各モードにおけるTelemetry Strategyを生成するファクトリ
	virtual void createTelemetryHotSpot() = 0;
	// 各モードにおけるFunctor Strategyを生成するファクトリ
	virtual void createFunctorHotSpot() = 0;
	// 各モードにおけるUpdate Strategyを生成するファクトリ
	virtual void createDataUpdateHotSpot() = 0;
	// 各モードにおけるSwitch Strategyを生成するファクトリ
	virtual void createSwitchHotSpot() = 0;
	// 各モードにおけるユーザー定義のStrategyを生成するファクトリ
	virtual void createAdditionalHotSpot() = 0;
	// データプールへの接続を生成するファクトリ
	virtual void createDataPoolConnection() = 0;
	// 生成されたオブジェクトを、Globalのポインタで返却
	virtual Global<Env>* returnCreatedObject() = 0;
};

} /* End of namespace stf::factory */
} /* End of namespace stf */


#endif // factory_SatelliteFactory_h