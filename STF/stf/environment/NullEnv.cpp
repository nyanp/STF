/**
 * @file   NullEnv.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "NullEnv.h"

namespace stf {
namespace environment {

NullEnv& NullEnv::get_instance(){
	static NullEnv instance;
	return instance;
}

} /* End of namespace stf::environment */
} /* End of namespace stf */
