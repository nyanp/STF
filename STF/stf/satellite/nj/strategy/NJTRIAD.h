/**
 * @file   NJTRIAD.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_control_NJTRIAD_h
#define stf_core_strategy_control_NJTRIAD_h

#include "../../../core/strategy/control/TRIAD.h"
#include "../../../interface/Iterator.h"

namespace stf {
namespace interface {
template<int U> class NJSunMagTRIADIterator;
}
namespace core {
namespace strategy {
namespace control {

//軌道情報と磁場，太陽方向ベクトルからquaternionを出力するNJTRIADブロック．
class NJSunMagTRIAD
	: public SunMagTRIAD2
{
public:
	NJSunMagTRIAD(int instance_id) : SunMagTRIAD2(instance_id), StrategyBase(instance_id, "NJTRIAD"){}
	NJSunMagTRIAD(int instance_id, 
		devicedriver::OutputPort<datatype::StaticVector<2>>* sunvector_source,
		devicedriver::OutputPort<datatype::MagneticField>* mag_source,
		devicedriver::OutputPort<datatype::PositionInfo>* position_source,
		devicedriver::clock::IAbsoluteTimeClock* clock,
		devicedriver::InputPort<datatype::Quaternion>* q_out = 0
		) : SunMagTRIAD2(instance_id, clock, sunvector_source, mag_source, position_source, q_out), StrategyBase(instance_id, "NJTRIAD"){}
	~NJSunMagTRIAD(){}
private:
	template<int U> friend class interface::NJSunMagTRIADIterator;
};

} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_strategy_control_input_NJTRIAD_h
