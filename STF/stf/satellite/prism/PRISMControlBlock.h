#ifndef stf_core_strategy_control_PRISMControlBlock_h
#define stf_core_strategy_control_PRISMControlBlock_h
#include "../../core/strategy/control/ControlBlock.h"
#include "../../datatype/List.h"

namespace stf {
namespace interface {
class PRISMControlBlockIterator;
}
namespace core {
namespace strategy {
namespace control {


class PRISMControlBlock : public ControlBlock
{
public:
	PRISMControlBlock(int instance_id) : ControlBlock(instance_id), ads_mode_(0), acs_mode_(0), obs_mode_(0) {}
	template<class T>
	PRISMControlBlock(int instance_id,devicedriver::OutputPort<typename T::Hold>* torque_source, T* torque_target)
		: ControlBlock(instance_id, torque_source, torque_target){}

	void set_mode(int mid, int value);

	enum PRISM_STRATEGY{
		TorqueCombiner,
		MagCombiner,
		CrossProduct,
		LiniarCorrection,
		Bdot,
		Decoupling,
		RateDumping,
		PID,
		PD,
		GGComp,
		EKF,
		TRIAD,
		RMMEKF,
	};
	void setStrategy(PRISM_STRATEGY str, core::strategy::StrategyBase* pt){
		this->strategylist_[str] = pt;
	}
private:
	friend class interface::PRISMControlBlockIterator;

	void set_ads_(int mode);
	void set_acs_(int mode);
	void set_obs_(int mode);
	int ads_mode_;
	int acs_mode_;
	int obs_mode_;
	// acrモード：ミッション系関連パラメータなので省略
	// memモード： Telemetry Strategyのパラメータ
	core::strategy::StrategyBase* strategylist_[13];

};

} /* End of namespace stf::core::mode::strategy::control */
} /* End of namespace stf::core::mode::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_mode_storategy_control_ControlBlock_h
