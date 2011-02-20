/**
 * @file   NoiseBase.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef aocs_environment_torquesource_NoiseBase_h
#define aocs_environment_torquesource_NoiseBase_h

#include "../../datatype/StaticVector.h"

namespace stf {
namespace environment {
class Simulator;
} /* End of namespace core::environment */
} /* End of namespace core */

namespace stf {
namespace environment {
namespace torquesource {

class NoiseBase {
public:
	NoiseBase(environment::Simulator* env) : environment_(env) {}
	virtual ~NoiseBase(){}
    virtual double get_torque() const = 0;
    virtual datatype::StaticVector<3> get_torque_bodyframe() const = 0;
    virtual void set_torque(double value) = 0;
 public:
    environment::Simulator *environment_;
};

} /* End of namespace stf::environment::torquesource */
} /* End of namespace stf::environment */
} /* End of namespace stf */

#endif // stf_environment_torquesource_WhiteNoise_h
