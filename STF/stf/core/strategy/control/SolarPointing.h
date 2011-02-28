/**
 * @file   SolarPointing.h
 * @brief  MTQで太陽指向制御を行うための制御ブロック．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_control_SolarPointing_h
#define stf_core_strategy_control_SolarPointing_h

#include "../StrategyBase.h"
#include "../../../datatype/StaticVector.h"
#include "../../../datatype/Magnetic.h"
#include "../../devicedriver/IOPort.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {

//! MTQで太陽指向制御を行うための制御ブロック．
/*!
	原理は制御ハンドブック9.3.3.3項参照．
	入力:衛星周辺磁場，太陽方向ベクトル
	出力:MTQ出力磁気モーメント
*/
class SolarPointing
	: virtual public StrategyBase, 
	public devicedriver::InputPorts< TYPELIST_2( datatype::MagneticField, datatype::StaticVector<2> ) >,
	public devicedriver::OutputPorts< TYPELIST_1( datatype::MagneticMoment ) >
{
public:
	SolarPointing(int instance_id, double k) : StrategyBase(instance_id, "SolarPointing"){}
	SolarPointing(int instance_id, double k, 
		devicedriver::OutputPort<datatype::MagneticField>* mag_source,
		devicedriver::OutputPort<datatype::StaticVector<2>>* sunvector_source = 0,
		devicedriver::InputPort<datatype::MagneticMoment>* mag_out = 0
		);
	~SolarPointing(){}
	virtual void do_compute(const datatype::Time& t);
protected:
	double K_;//gain
};


} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_strategy_control_input_SolarPointing_h
