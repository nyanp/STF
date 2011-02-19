#ifndef util_math_RungeKutta_h
#define util_math_RungeKutta_h

#include "../../datatype/Vector.h"

namespace stf { 
namespace util {
namespace math {
/** 
 *  ŒÃ“T“I‚È4Ÿ‚Ìƒ‹ƒ“ƒQƒNƒbƒ^D
*/
namespace RungeKutta {

//y' = f(t,y)Œ^‚Ì”÷•ª•û’ö®
template <class T> inline T slope(T yn, T(*df)(double,T), double tn, double dt){
    T k1 = df(tn, yn);
    T k2 = df(tn + 0.5 * dt, yn + 0.5 * dt * k1);
    T k3 = df(tn + 0.5 * dt, yn + 0.5 * dt * k2);
    T k4 = df(tn + dt, yn + dt * k3);

    return dt * (k1 + 2 * k2 + 2 * k3 + k4) / 6;
}

// y' = Ay + BŒ^‚Ì”÷•ª•û’ö®
template <class T,class A> inline T slope(T yn, A A, T B, double dt){
    T k1 = A * yn + B;
    T k2 = A * (yn + 0.5 * dt * k1) + B;
    T k3 = A * (yn + 0.5 * dt * k2) + B;
    T k4 = A * (yn + dt * k3) + B;
    return dt * (k1 + 2 * k2 + 2 * k3 + k4) / 6;
}

// y' = AyŒ^‚Ì”÷•ª•û’ö®
template <class T,class A> inline T slope(T yn, A A, double dt){
    T k1 = A * yn;
    T k2 = A * (yn + 0.5 * dt * k1);
    T k3 = A * (yn + 0.5 * dt * k2);
    T k4 = A * (yn + dt * k3);
    return dt * (k1 + 2 * k2 + 2 * k3 + k4) / 6;
}

} /* End of namespace stf::util::math::RungeKutta */
} /* End of namespace stf::util::math */
} /* End of namespace stf::util */
} /* End of namespace stf */

#endif // util_math_RungeKutta_h
