#ifndef util_math_Rand_h
#define util_math_Rand_h

#include<cmath>
#include<stdlib.h>
#include<float.h>
namespace stf { 
namespace util {
namespace math {

namespace mt {

/* initializes mt[N] with a seed */
void init_genrand(unsigned long s);

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
/* slight change for C++, 2004/2/26 */
void init_by_array(unsigned long init_key[], int key_length);

/* generates a random number on [0,0xffffffff]-interval */
unsigned long genrand_int32(void);

/* generates a random number on [0,0x7fffffff]-interval */
long genrand_int31(void);

/* generates a random number on [0,1]-real-interval */
double genrand_real1(void);

/* generates a random number on [0,1)-real-interval */
double genrand_real2(void);

/* generates a random number on (0,1)-real-interval */
double genrand_real3(void);

/* generates a random number on [0,1) with 53-bit resolution*/
double genrand_res53(void) ;
/* These real versions are due to Isaku Wada, 2002/01/09 added */

}

inline double Noise(){
	return (double)rand() / RAND_MAX;
}

inline double WhiteNoise(double sigma, double mu){
    const double PI = 3.14159265358979323846;
    //Box-Muller transform‚Å³‹K—”‚ğ¶¬
    double u1 = 0.0;
    while(-log(u1) >= (DBL_MAX / 2)){
        u1 = (double)rand() / RAND_MAX;
    }
    double u2 = (double)rand() / RAND_MAX;
    return sigma * sqrt( -2 * log(u1) ) * cos(2.0 * PI * u2) + mu;
}

inline void WhiteNoise_init(unsigned long i){
    mt::init_genrand(i);
}

inline double WhiteNoise2(double sigma, double mu){
    const double PI = 3.14159265358979323846;
    //Box-Muller transform‚Å³‹K—”‚ğ¶¬
    double u1 = mt::genrand_real3() ;
    double u2 = mt::genrand_real3() ;
    return sigma * sqrt( -2 * log(u1) ) * cos(2.0 * PI * u2) + mu;
}


} /* End of namespace stf::util::math */
} /* End of namespace stf::util */
} /* End of namespace stf */

#endif // util_math_Rand_h
