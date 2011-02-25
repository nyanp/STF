/**
 * @file   TelemetryManagerBase.cpp
 * @brief  テレメトリ生成を行う機能マネージャ基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "TelemetryManagerBase.h"
#include "../strategy/telemetry/ITelemetryStrategy.h"
#include "../mode/ModeBase.h"
#include "../../util/Trace.h"

namespace stf {
namespace core {
namespace manager {

void TelemetryManagerBase::notify(const mode::ModeBase* value){
	this->telem_ = value->getlist(SpotType());
}

void TelemetryManagerBase::run()
{
	util::Trace trace(util::Trace::kManager, "run TelemetryManager");
	if(this->telem_ == 0){
		trace.debug("skip");
		return;
	}
	datatype::List<HotSpot>::iterator it = this->telem_->begin();
	while(it != telem_->end()){
		(*it).write_to_telemetry();
		++it;
	}
}


} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */
