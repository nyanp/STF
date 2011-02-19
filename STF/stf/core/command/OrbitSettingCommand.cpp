/**
 * @file   OrbitSettingCommand.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "OrbitSettingCommand.h"
#include "../../util/Ostream.h"
#include "../devicedriver/gps/DummyGPS.h"

namespace stf {
namespace core {
namespace command {

void OrbitSettingCommand::execute(){
	util::cout << "mode change command!" << util::endl;
	this->gps_->setOrbit(*this->orbit_);

}

} /* End of namespace stf::core::command */
} /* End of namespace stf::core */
} /* End of namespace stf */