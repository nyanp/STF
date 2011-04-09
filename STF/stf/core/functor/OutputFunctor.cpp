/**
 * @file   OutputFunctor.cpp
 * @brief  出力ファンクタ群．STFではFunctorのコンストラクタに渡して使用される
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "OutputFunctor.h"
#include "../manager/ModeManagerBase.h"
#include "../../util/Cout.h"

namespace stf {
namespace core {
namespace functor {

void MSG::operator()() const {
	util::cout << this->msg_ << util::endl;
};


int ModeChangeFunc::operator()() const {
	this->modeman_->change_mode(&next_);	
	return 1;
};

} /* End of namespace stf::core::functor */
} /* End of namespace stf::core */
} /* End of namespace stf */

