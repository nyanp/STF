/**
 * @file   MagneticMomentToTorque.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_control_MagneticMomentToTorque_h
#define stf_core_strategy_control_MagneticMomentToTorque_h

#include "../StrategyBase.h"
#include "../../../datatype/StaticVector.h"
#include "../../../datatype/List.h"
#include "../../../datatype/Magnetic.h"
#include "../../devicedriver/IOPort.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {


//磁気モーメントをトルクに変換する制御ブロック．
//入力:衛星座標系における磁気モーメント，衛星出力磁気モーメント
//出力:3軸トルク
class MagneticMomentToTorque
	: virtual public StrategyBase, 
	public devicedriver::InputPorts< TYPELIST_2( datatype::MagneticMoment, datatype::MagneticMoment ) >,
	public devicedriver::OutputPorts< TYPELIST_1( datatype::StaticVector<3> ) >
{
public:
	MagneticMomentToTorque(int instance_id) : StrategyBase(instance_id, "MagneticMomentToTorque"){}
	MagneticMomentToTorque(int instance_id, 
		devicedriver::OutputPort<datatype::MagneticMoment>* mag_body_source,
		devicedriver::OutputPort<datatype::MagneticMoment>* mag_out_source,
		devicedriver::InputPort<datatype::StaticVector<3>>* torque_out = 0
		);
	~MagneticMomentToTorque(){}
	virtual void do_compute(const datatype::Time& t);
protected:
};


} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_strategy_control_input_MagneticMomentToTorque_h
