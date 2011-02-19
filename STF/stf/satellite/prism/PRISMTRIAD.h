#ifndef stf_core_strategy_control_PRISMTRIAD_h
#define stf_core_strategy_control_PRISMTRIAD_h

#include "../../core/strategy/control/TRIAD.h"
#include "../../interface/Iterator.h"

namespace stf {
namespace interface {
template<int U> class PRISMSunMagTRIADIterator;
}
namespace core {
namespace strategy {
namespace control {

//軌道情報と磁場，太陽方向ベクトルからquaternionを出力するPRISMTRIADブロック．
class PRISMSunMagTRIAD
	: public SunMagTRIAD
{
public:
	PRISMSunMagTRIAD(int instance_id) : SunMagTRIAD(instance_id), StrategyBase(instance_id,"PRISMTRIAD"){}
	PRISMSunMagTRIAD(int instance_id, 
		devicedriver::OutputPort<datatype::StaticVector<2>>* sunvector_source,
		devicedriver::OutputPort<datatype::MagneticField>* mag_source,
		devicedriver::OutputPort<datatype::PositionInfo>* position_source,
		devicedriver::OutputPort<datatype::DateTime>* time_source,
		devicedriver::InputPort<datatype::Quaternion>* q_out = 0
		) : SunMagTRIAD(instance_id, sunvector_source, mag_source, position_source, time_source, q_out), StrategyBase(instance_id,"PRISMTRIAD"){}
	~PRISMSunMagTRIAD(){}
private:
	template<int U> friend class interface::PRISMSunMagTRIADIterator;
};

} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_strategy_control_input_PRISMTRIAD_h
