/**
 * @file   NoiseBase.h
 * @brief  ノイズ源クラスの抽象インターフェース．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_environment_torquesource_NoiseBase_h
#define stf_core_environment_torquesource_NoiseBase_h

#include "../../../datatype/StaticVector.h"

namespace stf {
namespace core {
namespace environment {
class SimulatorBase;
} /* End of namespace stf::core::environment */
} /* End of namespace stf::core */
} /* End of namespace stf */

namespace stf {
namespace core {
namespace environment {
namespace torquesource {

//! ノイズ源クラスの抽象インターフェース．
/*! */
class NoiseBase {
public:
	NoiseBase(environment::SimulatorBase* env) : environment_(env) {}
	virtual ~NoiseBase(){}
    virtual double get_torque() const = 0;
    virtual datatype::StaticVector<3> get_torque_bodyframe() const = 0;
    virtual void set_torque(double value) = 0;
 public:
    environment::SimulatorBase *environment_;
};

} /* End of namespace stf::core::environment::torquesource */
} /* End of namespace stf::core::environment */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_environment_torquesource_WhiteNoise_h
