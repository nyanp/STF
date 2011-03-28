/**
 * @file   NullEnv.cpp
 * @brief  空の環境クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "NullEnv.h"

namespace stf {
namespace core {
namespace environment {

NullEnv& NullEnv::get_instance(){
	static NullEnv instance;
	return instance;
}

} /* End of namespace stf::core::environment */
} /* End of namespace stf::core */
} /* End of namespace stf */
