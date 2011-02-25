/**
 * @file   UnitManagerBase.cpp
 * @brief  機器の定期データ取得・更新を行う機能マネージャ基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "UnitManagerBase.h"
#include "../devicedriver/IDataUpdatable.h"
#include "../mode/ModeBase.h"
#include "../../util/Trace.h"

namespace stf {
namespace core {
namespace manager {


void UnitManagerBase::notify(const mode::ModeBase* newmode)
{
	this->unit_list_ = newmode->getlist(SpotType());
}

void UnitManagerBase::run()
{
	util::Trace trace(util::Trace::kManager, "run UnitManager");
	if(unit_list_ == 0){
		trace.debug("skip");
		return;
	}
	datatype::List<HotSpot>::iterator it = unit_list_->begin();
	while(it != unit_list_->end()){
		(*it).do_update();
		++it;
	}      
}


} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */