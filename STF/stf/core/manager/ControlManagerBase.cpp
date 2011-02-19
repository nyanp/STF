/**
 * @file   ControlManagerBase.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "ControlManagerBase.h"
#include "../mode/ModeBase.h"
#include "../../util/Ostream.h"
#include "../strategy/control/ControlBlock.h"

namespace stf {
namespace core {
namespace manager {

void ControlManagerBase::run(){
 	//util::cout<<"Conman run:\n";   
	if(this->controller_ == 0){
		//util::cout << "skip" << util::endl;
		return;
	}
	datatype::Time t = this->clock_->getTime();
	doControl(t);
}

void ControlManagerBase::notify(const mode::ModeBase* value){
	util::cout <<  "strategychange:" << util::endl;
	this->controller_ = value->getlist(SpotType());
}

void ControlManagerBase::doControl(const datatype::Time& t){
	datatype::List<HotSpot>::iterator it = this->controller_->begin();
	while(it != controller_->end()){
		(*it).computeTorque(t);
		++it;
	}
}


} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */
