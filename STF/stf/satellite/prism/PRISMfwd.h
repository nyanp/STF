/**
 * @file   PRISMfwd.h
 * @brief  PRISM固有クラスの前方宣言．
 *
 * @author Taiga Nomi
 * @date   2011.04.09
 */
#ifndef stf_satellite_PRISM_PRISMfwd_h
#define stf_satellite_PRISM_PRISMfwd_h

namespace stf {

template<class T> struct PRISMGlobal;

namespace app {
struct PRISM;
}

namespace core {

namespace factory {
template<class Env, class App> class PRISMFactory;
}

}

}




#endif