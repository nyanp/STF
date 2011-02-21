/**
 * @file   NullEnv.cpp
 * @brief  空の環境クラス．
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
