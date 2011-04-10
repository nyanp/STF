/**
 * @file   NJfwd.h
 * @brief  NJ固有クラスの前方宣言．
 *
 * @author Taiga Nomi
 * @date   2011.04.09
 */
#ifndef stf_satellite_NJ_NJfwd_h
#define stf_satellite_NJ_NJfwd_h

namespace stf {

template<class T> struct NJGlobal;

namespace app {
struct NJ;
}

namespace core {

namespace factory {
template<class Env, class App> class NJFactory;
}

}

}




#endif