/**
 * @file   UnaryFunctionCommand.cpp
 * @brief  １引数のファンクタやメンバ関数を起動するコマンド．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "UnaryFunctionCommand.h"

namespace stf {
namespace core {
namespace command {

//! コマンド引数をparamsの第一要素に置き換える．
template<>
void UnaryFunctorCommand<int>::init(int* params, int paramsize){
	if(paramsize >= 1)
		this->arg_ = params[0];//
}


} /* End of namespace stf::core::command */
} /* End of namespace stf::core */
} /* End of namespace stf */