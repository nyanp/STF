/**
 * @file   RMMEKF.h
 * @brief  残留磁気モーメントの推定を行う拡張カルマンフィルタ制御ブロック．未実装．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 * @todo   実装を行う
 */
#ifndef stf_core_strategy_control_RMMEKF_h
#define stf_core_strategy_control_RMMEKF_h

#include "../StrategyBase.h"
#include "../../devicedriver/IOPort.h"
#include "../../../datatype/StaticVector.h"
#include "../../../datatype/Magnetic.h"
#include "../../../util/Trace.h"

namespace stf {
namespace datatype {
class Time;
}
namespace core {
namespace strategy {
namespace control {

//! 残留磁気モーメントの推定を行う拡張カルマンフィルタ制御ブロック．未実装．
/*! 
	3軸それぞれに角速度PIDを適用する．クロスカップリング項が無視できない場合，CouplingCompensationブロックを併用して打ち消す必要がある
	入力:磁場，角速度
	出力:3軸磁気モーメント
*/	
class RMMEKF : public StrategyBase,
	public devicedriver::InputPorts< TYPELIST_2( datatype::MagneticField, datatype::StaticVector<3> ) >,
	public devicedriver::OutputPorts< TYPELIST_1( datatype::MagneticMoment ) >
{
public:
	RMMEKF(int instance_id) : StrategyBase(instance_id, "RMMEKF"){}
	RMMEKF(int instance_id, 
		OutputPort<datatype::MagneticField>* mag_source, OutputPort<datatype::StaticVector<3>>* omega_source,
		InputPort<datatype::MagneticMoment>* mag_out = 0) : StrategyBase(instance_id, "RMMEKF")
	{
	
	}
	virtual ~RMMEKF(){}
	virtual void do_compute(const datatype::Time& t){
		util::Trace trace(util::Trace::kControlBlock, name_);
	}//伝搬，更新処理
};


} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_strategy_control_input_RMMEKF_h
