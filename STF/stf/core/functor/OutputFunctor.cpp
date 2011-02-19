/**
 * @file   OutputFunctor.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "OutputFunctor.h"
#include "../manager/ModeManager.h"
#include "../mode/Includes.h"
#include "../../util/Ostream.h"

namespace stf {
namespace core {
namespace functor {

void MSG::operator()() const {
	util::cout << "output functor" << util::endl;
};


int ModeChangeFunc::operator()() const {
	this->modeman_->change_mode(&next_);	
	return 1;
};

} /* End of namespace stf::core::functor */
} /* End of namespace stf::core */
} /* End of namespace stf */

