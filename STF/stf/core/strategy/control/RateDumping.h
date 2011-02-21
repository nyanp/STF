/**
 * @file   RateDumping.h
 * @brief  レートダンピング則による3軸独立のトルク計算を行う制御ブロック．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_control_RateDumping_h
#define stf_core_strategy_control_RateDumping_h
#include <assert.h>

#include "../StrategyBase.h"
#include "../../devicedriver/IOPort.h"
#include "../../../datatype/StaticVector.h"

namespace stf {
namespace datatype {
class Time;
}
namespace core {
namespace strategy {
namespace control {

//! レートダンピング則による3軸独立のトルク計算を行う制御ブロック．
/*! 
	3軸それぞれに角速度PIDを適用する．クロスカップリング項が無視できない場合，CouplingCompensationブロックを併用して打ち消す必要がある
	入力:3軸角速度
	出力:3軸トルク
*/
class RateDumping : public StrategyBase,
	public devicedriver::InputPorts< TYPELIST_1(datatype::StaticVector<3>)>,
	public devicedriver::OutputPorts< TYPELIST_1(datatype::StaticVector<3>)>{
public:
    RateDumping(int instance_id, double kp, double ki, double kd, double dt);
	RateDumping(int instance_id, double kp, double ki, double kd, double dt,
		devicedriver::OutputPort<datatype::StaticVector<3>>* omega_source,
		devicedriver::InputPort<datatype::StaticVector<3>>* torque_target );

	virtual ~RateDumping(){}
	virtual void do_compute(const datatype::Time& t);
protected:
    datatype::StaticVector<3> compute_torque_(const datatype::StaticVector<3>& input);
    double ki_;
    double kd_;
    double kp_;
	double dt_;
	datatype::StaticVector<3> omega_before_;
    datatype::StaticVector<3> omega_total_;
};


} /* End of namespace core::mode::strategy::control */
} /* End of namespace core::mode::strategy */
} /* End of namespace core::mode */
} /* End of namespace core */

#endif // aocs_strategy_control_RateDumping_h
