#ifndef util_math_Exp_h
#define util_math_Exp_h

#include<assert.h>
#include"../../datatype/Matrix.h"

namespace stf { 
namespace util {
namespace math {


//行列の指数をn次のマクローリン展開まで計算して返す関数．
datatype::Matrix exp(datatype::Matrix m,int n);

datatype::Matrix exp(datatype::Matrix m);

} /* End of namespace stf::util::math */
} /* End of namespace stf::util */
} /* End of namespace stf */

#endif // util_math_Exp_h
