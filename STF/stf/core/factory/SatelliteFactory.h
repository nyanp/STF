/**
 * @file   SatelliteFactory.h
 * @brief  衛星ファクトリの基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef factory_SatelliteFactory_h
#define factory_SatelliteFactory_h

#include "../../GlobalObject.h"

namespace stf {
namespace core {
namespace factory {

//! 衛星ファクトリの基底クラス．
/*! 
	Factory Methodパターンによる衛星オブジェクト群の生成を行うクラスの抽象インターフェース．
	createメソッドのみ実装が既定されており，初期化の順序が決まっている（Template Method）．

	@tparam Env     コンポーネントの環境クラス．
	@tparam Derived CRTPによるSingletonパターンの実装のために導入される派生クラスパラメータ．

	これを継承したクラスは，以下のようなインターフェースを有している必要がある．

	@code
	// すべてのメソッドとデータはprivateとし，SatelliteFactoryをfriendとする．
	template<class Environment>
	class SomeFactory : public SatelliteFactory<Environment, SomeFactory<Environment> >
	{
		friend class SatelliteFactory<Environment, NJFactory<Environment>>;

		// Constructor & Destructor
		SomeFactory(){ this->global_ = new SomeGlobal<Environment>();}
		virtual ~SomeFactory(){ delete this->global_; }

		// Virtual method implementations
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

		// Global object for concrete satellite
		SomeGlobal<Environment>* global_;
	};

	int main(void){
		SomeFactory<Environment>& factory = SomeFactory<Environment>::getInstance();
		Global<Environment>* g = factory.create();

		return 0;
	}
	@endcode

*/
template<class Env, class App, class Derived>
class SatelliteFactory {
public:
	static Derived& getInstance(){
		static Derived instance;
		return instance;
	}

	Global<Env>* create(){
		if(is_created_ == false){
			create_funcmanager();
			create_component();
			create_datapool();
			create_mode();
			create_command();
			create_telemetry();
			create_controller();
			create_functor();
			create_dataupdates();
			create_switches();
			create_additional_hotspot();
			satellite_initialize();
			is_created_ = true;
		}
		return return_created_object();
	}
protected:
	//! デバイスドライバを生成するファクトリ
	virtual void create_component() = 0;
	//! 機能マネージャを生成するファクトリ
	virtual void create_funcmanager() = 0;
	//! モードを生成するファクトリ
	virtual void create_mode() = 0;
	//! 各モードにおけるControl Strategyを生成するファクトリ
	virtual void create_controller() = 0;
	//! Commandを生成するファクトリ
	virtual void create_command() = 0;
	//! 各モードにおけるTelemetry Strategyを生成するファクトリ
	virtual void create_telemetry() = 0;
	//! 各モードにおけるFunctor Strategyを生成するファクトリ
	virtual void create_functor() = 0;
	//! 各モードにおけるUpdate Strategyを生成するファクトリ
	virtual void create_dataupdates() = 0;
	//! 各モードにおけるSwitch Strategyを生成するファクトリ
	virtual void create_switches() = 0;
	//! 各モードにおけるユーザー定義のStrategyを生成するファクトリ
	virtual void create_additional_hotspot() = 0;
	//! データプールへの接続を生成するファクトリ
	virtual void create_datapool() = 0;
	//! 最初のモード指定など，衛星固有の初期化処理を実行．
	virtual void satellite_initialize() = 0;
	//! 生成されたオブジェクトを、Globalのポインタで返却
	virtual Global<Env>* return_created_object() = 0;

	SatelliteFactory() : is_created_(false){}
	virtual ~SatelliteFactory(){}
private:
	bool is_created_;
};

} /* End of namespace stf::core::factory */
} /* End of namespace stf::core */
} /* End of namespace stf */


#endif // factory_SatelliteFactory_h