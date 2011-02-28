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

namespace stf {
namespace core {
namespace devicedriver {

//! アクチュエータの基底クラス．
/*! 
	@tparam T   アクチュエータが出力する物理量．
	@tparam U   アクチュエータが出力する次元での物理量．3軸アクチュエータならTと一致，1軸ならScalar．
	@tparam Env コンポーネントの環境クラス．
*/
template<class T, class U, class Env>
class AOCSActuator : public AOCSComponent<T, U, Env>, public InputPorts< TYPELIST_1(U) > {
public:
	AOCSActuator(int instance_id, const datatype::String& name, const datatype::DCM& dcm)
		: AOCSComponent<T, U, Env>(instance_id,name,dcm){}

	virtual ~AOCSActuator(){}

    virtual void set_torque(const U& value) { this->output_ = value; }

	virtual const U& get_torque() const { return output_; }

protected:
	U output_;
};
 
} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_AOCSActuator_h
