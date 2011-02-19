#include "SwitchCommand.h"
#include "../../util/Ostream.h"
#include "../devicedriver/ISwitchable.h"

namespace stf {
namespace core {
namespace command {

void SwitchCommand::execute(){
	util::cout << "mode change command!" << util::endl;
	if(on_){
		this->sw_->on();
	}else{
		this->sw_->off();
	}
}

} /* End of namespace stf::core::command */
} /* End of namespace stf::core */
} /* End of namespace stf */