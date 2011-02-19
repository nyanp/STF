#include "WhiteNoise.h"
#include "../../util/math/Rand.h"

namespace stf {
namespace environment {
namespace torquesource {


WhiteNoise::~WhiteNoise()
{
}

WhiteNoise::WhiteNoise(double sigma, double mu): sigma_(sigma), mu_(mu), NoiseBase(0)
{
}


double WhiteNoise::getTorque() const 
{
    return this->sigma_;//TBD:分散を返すのはインターフェースとして正しい？
}


datatype::Vector WhiteNoise::getTorqueInBodyFrame() const 
{
    datatype::Vector v(3);
    for(int i = 0; i < 3; i++){
        v[i] = util::math::WhiteNoise(this->sigma_,this->mu_);
    }
    return v;
}


void WhiteNoise::setTorque(double value)
{
    this->sigma_ = value;
}


} /* End of namespace stf::environment::torquesource */
} /* End of namespace stf::environment */
} /* End of namespace stf */
