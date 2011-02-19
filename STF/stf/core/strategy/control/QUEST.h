#ifndef stf_core_strategy_control_QUEST_h
#define stf_core_strategy_control_QUEST_h

#include "../StrategyBase.h"
#include "../../../datatype/StaticVector.h"
#include "../../../datatype/Quaternion.h"
#include "../../../datatype/DateTime.h"
#include "../../../datatype/OrbitInfo.h"
#include "../../devicedriver/IOPort.h"

namespace stf {
namespace datatype {
class Time;
}
namespace core {
namespace strategy {
namespace control {


//Quaternion Estimator
//太陽方向-地球方向の2-Inputの場合のQUESTとして，固有値計算を簡略化している
class QUEST
	: virtual public StrategyBase, 
	public devicedriver::InputPorts< TYPELIST_4( datatype::StaticVector<2>, datatype::StaticVector<2>, datatype::PositionInfo, datatype::DateTime ) >,
	public devicedriver::OutputPorts< TYPELIST_1( datatype::Quaternion ) >
{
public:
	QUEST(int instance_id, double sigma_sun, double sigma_earth) : StrategyBase(instance_id, "QUEST"), 
		sigma_sun_(sigma_sun),sigma_earth_(sigma_earth){ init_(); }
	QUEST(int instance_id, double sigma_sun, double sigma_earth, 
		devicedriver::OutputPort<datatype::StaticVector<2>>* sunvector_source,
		devicedriver::OutputPort<datatype::StaticVector<2>>* earthvector_source,
		devicedriver::OutputPort<datatype::PositionInfo>* position_source,
		devicedriver::OutputPort<datatype::DateTime>* time_source,		
		devicedriver::InputPort<datatype::Quaternion>* q_out = 0
		);
	~QUEST(){}
	virtual void do_compute(const datatype::Time& t);
protected:
	void init_();
	datatype::Quaternion estimate_(datatype::StaticVector<3> v1, datatype::StaticVector<3> v2, 
		datatype::StaticVector<3> w1, datatype::StaticVector<3> w2);
	double sigma_sun_;//太陽方向ベクトルの観測分散
	double sigma_earth_;//地球方向ベクトルの観測分散
	double a1_;
	double a2_;
};


} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_strategy_control_input_QUEST_h
