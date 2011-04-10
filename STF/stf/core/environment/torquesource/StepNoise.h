/**
 * @file   StepNoise.h
 * @brief  ステップノイズを発生させるトルク源．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_environment_torquesource_StepNoise_h
#define stf_core_environment_torquesource_StepNoise_h

#include "NoiseBase.h"
#include "../../../datatype/StaticVector.h"
#include "../../../datatype/Time.h"


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

//! ステップノイズを発生させるトルク源．
/*! */
class StepNoise : virtual public NoiseBase {
public:
    StepNoise(double magnitude, environment::SimulatorBase *env);
    StepNoise(double magnitude, const datatype::StaticVector<3> &vector, const int &startTimeInSecond, environment::SimulatorBase *env);
    virtual ~StepNoise();
    virtual double get_torque() const ;
    virtual void set_torque(double value);
    virtual datatype::StaticVector<3> get_torque_bodyframe() const ;
private:
    StepNoise();
    datatype::StaticVector<3> vector_;
    double magnitude_;
    datatype::Time starttime_;
};

} /* End of namespace stf::core::environment::torquesource */
} /* End of namespace stf::core::environment */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_environment_torquesource_StepNoise_h
