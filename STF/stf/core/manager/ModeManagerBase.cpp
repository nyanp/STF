/**
 * @file   ModeManagerBase.cpp
 * @brief  モードの管理を行う機能マネージャ基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "ModeManagerBase.h"
#include "../mode/ModeBase.h"
#include "../../util/Ostream.h"

namespace stf {
namespace core {
namespace manager {

// Oberver
void ModeManagerBase::change_mode(const core::mode::ModeBase *mode)
{
	util::cout << "change_mode:" << "->" << mode->name() << util::endl;
	current_mode_ = mode;
	this->notify_observers(*mode);
}

void ModeManagerBase::notify(const mode::ModeBase* value){
	this->component_ = value->getlist(SpotType());
}

void ModeManagerBase::run()
{
 	//util::cout<<"Modeman run:\n";   
	this->check();
}

const datatype::String& ModeManagerBase::get_current_modename() const {
	return this->current_mode_->name();
}

} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */
