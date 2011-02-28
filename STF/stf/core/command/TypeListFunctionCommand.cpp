/**
 * @file   TypeListFunctionCommand.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 * @todo   修正OR削除
 */
#include "UnaryFunctionCommand.h"

namespace stf {
namespace core {
namespace command {

template<>
void UnaryFunctorCommand<int>::init(int* params, int paramsize){
	if(paramsize == 1)
		this->arg_ = params[0];//
}


} /* End of namespace stf::core::command */
} /* End of namespace stf::core */
} /* End of namespace stf */