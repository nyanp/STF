/**
 * @file   ControlManagerBase.cpp
 * @brief  制御ブロックの実行を行う機能マネージャ基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "ControlManagerBase.h"
#include "../mode/ModeBase.h"
#include "../../util/Ostream.h"
#include "../strategy/control/ControlBlock.h"
#include "../../util/Trace.h"

namespace stf {
namespace core {
namespace manager {

void ControlManagerBase::run(){
	util::Trace trace(util::Trace::kManager,"run ControlManager"); 
	if(this->controller_ == 0){
		trace.debug("skip");
		return;
	}
	datatype::Time t = this->clock_->get_time();
	doControl(t);
}

void ControlManagerBase::notify(const mode::ModeBase* value){
	this->controller_ = value->get_list(SpotType());
}

void ControlManagerBase::doControl(const datatype::Time& t){
	datatype::List<HotSpot>::iterator it = this->controller_->begin();
	while(it != controller_->end()){
		(*it).compute_torque(t);
		++it;
	}
}


} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */
