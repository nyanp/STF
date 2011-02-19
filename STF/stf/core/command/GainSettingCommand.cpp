/**
 * @file   GainSettingCommand.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "GainSettingCommand.h"
#include "../strategy/control/PID.h"
#include "../../util/Ostream.h"

namespace stf {
namespace core {
namespace command {

void GainSettingCommand::execute(){
	util::cout << "gain setting command!" << util::endl;
	this->controller_->setPIDGain(kp_,ki_,kd_);
}

} /* End of namespace stf::core::command */
} /* End of namespace stf::core */
} /* End of namespace stf */