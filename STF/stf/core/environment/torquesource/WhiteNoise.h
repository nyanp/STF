/**
 * @file   WhiteNoise.h
 * @brief  ホワイトノイズを発生させるトルク源．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_environment_torquesource_WhiteNoise_h
#define stf_core_environment_torquesource_WhiteNoise_h

#include "NoiseBase.h"
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

//! ホワイトノイズを発生させるトルク源．
/*! */
class WhiteNoise : virtual public NoiseBase {
public:
    virtual ~WhiteNoise();
    WhiteNoise(double sigma, double mu);
    virtual double get_torque() const ;
    virtual datatype::StaticVector<3> get_torque_bodyframe() const ;
    virtual void set_torque(double value);
    environment::SimulatorBase* environment_;
private:
    double sigma_;
    double mu_;
};

} /* End of namespace stf::core::environment::torquesource */
} /* End of namespace stf::core::environment */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_environment_torquesource_WhiteNoise_h
