#include "NullEnv.h"

namespace stf {
namespace environment {

NullEnv& NullEnv::getInstance(){
	static NullEnv instance;
	return instance;
}

} /* End of namespace stf::environment */
} /* End of namespace stf */
