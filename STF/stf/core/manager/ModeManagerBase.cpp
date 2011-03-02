/**
 * @file   ModeManagerBase.cpp
 * @brief  モードの管理を行う機能マネージャ基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "ModeManagerBase.h"
#include "../mode/ModeBase.h"
#include "../../util/Trace.h"


namespace stf {
namespace core {
namespace manager {

// Oberver
void ModeManagerBase::change_mode(const core::mode::ModeBase *mode)
{
	util::Trace trace(util::Trace::kManager, "modeChange ModeManager");
	trace.debug(mode->name());
	current_mode_ = mode;
	this->notify_observers(*mode);
}

void ModeManagerBase::notify(const mode::ModeBase* value){
	this->component_ = value->get_list(SpotType());
}

void ModeManagerBase::run()
{
	util::Trace trace(util::Trace::kManager, "run ModeManager");
}

const datatype::String& ModeManagerBase::get_current_modename() const {
	return this->current_mode_->name();
}

} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */
