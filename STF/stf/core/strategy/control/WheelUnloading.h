/**
 * @file   WheelUnloading.h
 * @brief  RWのアンローディングをMTQを使用して行うための制御ブロック．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 * @todo アンローディング則の実装
 */
#ifndef stf_core_strategy_control_WheelUnloading_h
#define stf_core_strategy_control_WheelUnloading_h

#include "../StrategyBase.h"
#include "../../devicedriver/IOPort.h"
#include "../../devicedriver/rw/RWBase.h"

#include "../../../datatype/StaticVector.h"
#include "../../../datatype/List.h"
#include "../../../datatype/OrbitInfo.h"
#include "../../../util/Trace.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {

//! RWのアンローディングをMTQを使用して行うための制御ブロック．
/*!
	出力可能なトルク方向を計算するために軌道情報を必要とするほか，
	ポートとは別に角運動量を参照するために対象ホイールを直接接続する必要がある．

	入力:軌道情報
	出力:RW出力トルク，MTQ出力トルク
*/
template<class Env>
class WheelUnloading
	: virtual public StrategyBase, 
	public devicedriver::InputPorts< TYPELIST_1( datatype::PositionInfo ) >,
	public devicedriver::OutputPorts< TYPELIST_2( datatype::StaticVector<3>, datatype::StaticVector<3> ) >
{
public:
	WheelUnloading(int instance_id) : StrategyBase(instance_id, "WheelUnloading"){}
	WheelUnloading(int instance_id, 
		devicedriver::OutputPort<datatype::PositionInfo>* position_source,
		devicedriver::InputPort<datatype::StaticVector<3>>* torquer_out = 0,
		devicedriver::InputPort<datatype::StaticVector<3>>* wheel_out = 0
		);
	~WheelUnloading(){}
	void add_wheel(core::devicedriver::rw::RWBase<Env>* wheel) { this->unloading_wheels_.add(*wheel); }
	virtual void do_compute(const datatype::Time& t);
protected:
	datatype::List< core::devicedriver::rw::RWBase<Env> > unloading_wheels_;

};

template<class Env>
WheelUnloading<Env>::WheelUnloading(int instance_id, 
		devicedriver::OutputPort<datatype::PositionInfo>* position_source,
		devicedriver::InputPort<datatype::StaticVector<3>>* torquer_out,
		devicedriver::InputPort<datatype::StaticVector<3>>* wheel_out
		) : StrategyBase(instance_id, "WheelUnloading")
{
	this->connect_source<0>(position_source);
	if(torquer_out != 0){
		torquer_out->connect_source_(&outputport<0, datatype::StaticVector<3>>());
	}
	if(wheel_out != 0){
		wheel_out->connect_source_(&outputport<1, datatype::StaticVector<3>>());
	}
}

template<class Env>
void WheelUnloading<Env>::do_compute(const datatype::Time& t) {
	//if(t <= this->last_update_) return; //既に別のブロック経由で更新済みなら再計算しない
	util::Trace trace(util::Trace::kControlBlock, name_);
	//this->last_update_ = t;
}



} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_strategy_control_input_WheelUnloading_h
