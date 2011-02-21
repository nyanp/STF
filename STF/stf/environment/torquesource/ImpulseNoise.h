/**
 * @file   ImpulseNoise.h
 * @brief  インパルスノイズを発生させるトルク源．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef aocs_environment_torquesource_ImpulseNoise_h
#define aocs_environment_torquesource_ImpulseNoise_h

#include "NoiseBase.h"
#include "../../datatype/StaticVector.h"
#include "../../datatype/Time.h"


namespace stf {
namespace environment {
class Simulator;
} /* End of namespace stf::environment */
} /* End of namespace stf */

namespace stf {
namespace environment {
namespace torquesource {

//! インパルスノイズを発生させるトルク源．
/*! */
class ImpulseNoise : virtual public NoiseBase {
public:
    ImpulseNoise(double magnitude, const datatype::StaticVector<3> &vector, const int &startTimeInSecond, const double &durationInMillisec, environment::Simulator *env);
    ImpulseNoise(double magnitude, environment::Simulator *env);
    virtual ~ImpulseNoise();
    virtual double get_torque() const ;
    virtual datatype::StaticVector<3> get_torque_bodyframe() const ;
    virtual void set_torque(double value);
private:
    ImpulseNoise();
    datatype::Time starttime_;
    datatype::Time duration_;
    datatype::StaticVector<3> vector_;
    double magnitude_;
};

} /* End of namespace stf::environment::torquesource */
} /* End of namespace stf::environment */
} /* End of namespace stf */

#endif // aocs_environment_torquesource_ImpulseNoise_h
