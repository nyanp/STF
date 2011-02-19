/**
 * @file   WhiteNoise.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef aocs_environment_torquesource_WhiteNoise_h
#define aocs_environment_torquesource_WhiteNoise_h

#include "NoiseBase.h"
#include "../../datatype/Vector.h"

namespace stf {
namespace environment {
class Simulator;
} /* End of namespace stf::environment */
} /* End of namespace stf */

namespace stf {
namespace environment {
namespace torquesource {

class WhiteNoise : virtual public NoiseBase {
public:
    virtual ~WhiteNoise();
    WhiteNoise(double sigma, double mu);
    virtual double getTorque() const ;
    virtual datatype::Vector getTorqueInBodyFrame() const ;
    virtual void setTorque(double value);
    environment::Simulator *environment_;
private:
    double sigma_;
    double mu_;
};

} /* End of namespace stf::environment::torquesource */
} /* End of namespace stf::environment */
} /* End of namespace stf */

#endif // aocs_environment_torquesource_WhiteNoise_h
