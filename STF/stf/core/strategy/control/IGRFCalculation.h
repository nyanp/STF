#ifndef scube_core_strategy_control_IGRFCalculation_h
#define scube_core_strategy_control_IGRFCalculation_h

#include "../StrategyBase.h"
#include "../../../datatype/StaticVector.h"
#include "../../../datatype/Magnetic.h"
#include "../../../datatype/OrbitInfo.h"
#include "../../devicedriver/IOPort.h"

namespace scube {
namespace datatype {
class Time;
}
namespace core {
namespace strategy {
namespace control {

//IGRFモデルを計算し，磁気センサと軌道情報から地球方向を出力する制御ブロック．未実装
class IGRFCalculation
	: virtual public StrategyBase, 
	public devicedriver::InputPorts< TYPELIST_2( datatype::MagneticField, datatype::PositionInfo ) >,
	public devicedriver::OutputPorts< TYPELIST_1( datatype::StaticVector<2> ) >
{
public:
	IGRFCalculation(int instance_id) : StrategyBase(instance_id, "IGRFCalculation"){}
	IGRFCalculation(int instance_id, 
		devicedriver::OutputPort<datatype::MagneticField>* mag_source,
		devicedriver::OutputPort<datatype::PositionInfo>* orbitinfo_source,
		devicedriver::InputPort<datatype::StaticVector<2>>* earthvec_out = 0
		);
	~IGRFCalculation(){}
	virtual void doCompute(const datatype::Time& t);
private:
};


} /* End of namespace scube::core::strategy::control */
} /* End of namespace scube::core::strategy */
} /* End of namespace scube::core */
} /* End of namespace scube */

#endif // scube_core_strategy_control_input_IGRFCalculation_h
