/**
 * @file   GlobalObject.h
 * @brief  RTOSとのインターフェースとなる，衛星アプリケーションが生成するオブジェクト群の基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 * @todo   Singleton Patternの適用
 */
#ifndef stf_GlobalObject_h
#define stf_GlobalObject_h

#include <fstream>
#include "InstanceID.h"
#include "datatype/List.h"
#include "datatype/Time.h"
#include "datatype/DateTime.h"
#include "datatype/SatelliteModel.h"

namespace stf {
namespace core {
namespace datapool {
class AocsDataPool;
class EventDataPool;
}
namespace manager {
class ManagerBase;
}
}
}

namespace stf {

using namespace core;

//! RTOSとのインターフェースとなる，衛星アプリケーションが生成するオブジェクト群の基底クラス．
/*! 
	@tparam Env アプリケーションの環境クラス．
*/
template<class Env>
class Global{
public:
	//static Global<Env>& get_instance();//Environmentごとに単一のインスタンスのみを生成
	virtual const core::datapool::AocsDataPool* get_datapool() const = 0;
	virtual const core::datapool::EventDataPool* get_eventdatapool() const = 0;

	virtual const datatype::Time get_global_time() = 0;//衛星のOBC時刻を取得
	virtual const datatype::DateTime get_global_datetime() = 0;//衛星のRTC時刻を取得
	virtual const datatype::SatelliteModel get_satellitemodel() const = 0;//衛星の質量特性モデルを取得
	virtual datatype::List<core::manager::ManagerBase>* getFunctionManager() {return &(this->managers_);}

	virtual ~Global(){}//デストラクタ
	Global(){}//コンストラクタを禁止（シングルトンパターン）
	Global(const Global<Env>&);
	void operator=(const Global<Env>&);
	datatype::List<core::manager::ManagerBase> managers_;
};

} /* End of namespace stf */

#endif // stf_GlobalObject_h