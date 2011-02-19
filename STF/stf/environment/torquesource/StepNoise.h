/**
 * @file   StepNoise.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef aocs_environment_torquesource_StepNoise_h
#define aocs_environment_torquesource_StepNoise_h

#include "NoiseBase.h"
#include "../../datatype/Vector.h"
#include "../../datatype/Time.h"


namespace stf {
namespace environment {
class Simulator;
} /* End of namespace stf::environment */
} /* End of namespace stf */

namespace stf {
namespace environment {
namespace torquesource {

class StepNoise : virtual public NoiseBase {
public:
    StepNoise(double magnitude, stf::environment::Simulator *env);
    StepNoise(double magnitude, const datatype::Vector &vector, const int &startTimeInSecond, environment::Simulator *env);
    virtual ~StepNoise();
    virtual double getTorque() const ;
    virtual void setTorque(double value);
    virtual datatype::Vector getTorqueInBodyFrame() const ;
private:
    StepNoise();
    datatype::Vector vector_;
    double magnitude_;
    datatype::Time starttime_;
};

} /* End of namespace stf::environment::torquesource */
} /* End of namespace stf::environment */
} /* End of namespace stf */

#endif // aocs_environment_torquesource_StepNoise_h
