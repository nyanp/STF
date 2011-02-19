/**
 * @file   ImpulseNoise.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef aocs_environment_torquesource_ImpulseNoise_h
#define aocs_environment_torquesource_ImpulseNoise_h

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

class ImpulseNoise : virtual public NoiseBase {
public:
    ImpulseNoise(double magnitude, const datatype::Vector &vector, const int &startTimeInSecond, const double &durationInMillisec, environment::Simulator *env);
    ImpulseNoise(double magnitude, environment::Simulator *env);
    virtual ~ImpulseNoise();
    virtual double getTorque() const ;
    virtual datatype::Vector getTorqueInBodyFrame() const ;
    virtual void setTorque(double value);
private:
    ImpulseNoise();
    datatype::Time starttime_;
    datatype::Time duration_;
    datatype::Vector vector_;
    double magnitude_;
};

} /* End of namespace stf::environment::torquesource */
} /* End of namespace stf::environment */
} /* End of namespace stf */

#endif // aocs_environment_torquesource_ImpulseNoise_h
