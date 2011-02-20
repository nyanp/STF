/**
 * @file   ModeChangeCommand.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "ModeChangeCommand.h"
#include "../manager/ModeManagerBase.h"
#include "../../util/Ostream.h"

namespace stf {
namespace core {
namespace command {

void modeChangeCommand::execute(){
	util::cout << "mode change command!" << util::endl;
	this->modeman_->change_mode(this->mode_);
}

Command* modeChangeCommand::clone(const datatype::Time& t){
	modeChangeCommand* newcmd = new modeChangeCommand(t,mode_,modeman_);
	return newcmd;
}
} /* End of namespace stf::core::command */
} /* End of namespace stf::core */
} /* End of namespace stf */