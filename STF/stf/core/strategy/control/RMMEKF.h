#ifndef stf_core_strategy_control_RMMEKF_h
#define stf_core_strategy_control_RMMEKF_h

#include "../StrategyBase.h"
#include "../../devicedriver/IOPort.h"

#include "../../../datatype/StaticVector.h"
#include "../../../datatype/Magnetic.h"
#include "../../../util/Ostream.h"

namespace stf {
namespace datatype {
class Time;
}
namespace core {
namespace devicedriver {
template<class T,class U,class Env> class AOCSComponent;
}
namespace strategy {
namespace control {

	
//残留磁気モーメントを推定するフィルタ（未実装）
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
	// virtual void update(const datatype::Quaternion &input,const datatype::Time& t);
    //virtual void propagate(const datatype::StaticVector<3>& omega,const datatype::Time& t);
	//virtual void reset();
	virtual void do_compute(const datatype::Time& t){
		util::cout << "compute: RMMEKF(not implemented)" << util::endl;
	}//伝搬，更新処理

private:
	/*datatype::StaticVector<3> omega_;
    datatype::Quaternion q_;
    datatype::Vector bref_;
	//伝搬頻度(sec)
	double dt_;
    datatype::Matrix A_;
    datatype::Matrix B_;
    datatype::Matrix G_;
    datatype::Matrix F_;
    datatype::Matrix H_;
    datatype::Matrix P_;
    datatype::Matrix K_;
    datatype::Matrix Q_;
    datatype::Matrix R_;
    datatype::Vector x_;
    datatype::Matrix Ht_;
    datatype::Matrix Omega_;
    */
};


} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_strategy_control_input_RMMEKF_h
