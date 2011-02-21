/**
 * @file   AOCSActuator.h
 * @brief  アクチュエータの基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_AOCSActuator_h
#define stf_core_devicedriver_AOCSActuator_h

#include "AOCSComponent.h"
#include "../../util/Ostream.h"

namespace stf {
namespace core {
namespace devicedriver {

//! アクチュエータの基底クラス．
/*! 
	@tparam T   アクチュエータが出力する物理量．
	@tparam U   アクチュエータが出力する次元での物理量．3軸アクチュエータならTと一致，1軸ならScalar．
	@tparam Env コンポーネントの環境クラス．
*/
template<class T,class U = T,class Env = ENV>
class AOCSActuator : public AOCSComponent<T,U,Env>, public InputPorts< TYPELIST_1(U) > {
public:
	AOCSActuator(int instance_id, const datatype::String& name, const datatype::DCM& dcm) : AOCSComponent<T,U,Env>(instance_id,name,dcm){}
	virtual ~AOCSActuator(){}
	void setMaxOutput(const U& ref) { max_output_ = ref; }
    virtual void set_torque(U value) {
		if(value > this->max_output_) this->set_value(this->max_output_);//サチる
		else if(value < this->min_output_) this->set_value(this->min_output_);
		else 
			 this->set_value(value);
	}
protected:
	U max_output_;
	U min_output_;
	double sigma_;
private:
	AOCSActuator& operator = (const AOCSActuator& rhs);
    AOCSActuator();
	AOCSActuator(const AOCSActuator<T,U,Env>& rhs);
};

} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_AOCSActuator_h
