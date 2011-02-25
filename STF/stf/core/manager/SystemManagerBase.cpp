/**
 * @file   SystemManagerBase.cpp
 * @brief  条件判定や異常対応を行う機能マネージャ基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "SystemManagerBase.h"
#include "../mode/ModeBase.h"
#include "../datapool/Datapool.h"
#include "../functor/Functor.h"
#include "../../util/Trace.h"

namespace stf {
namespace core {
namespace manager {

void SystemManagerBase::notify(const mode::ModeBase* value){
	util::cout << "system list change!" << util::endl;
	this->func_ = value->getlist(SpotType());
	//this->func_ = value->getlist(SpotType());
}

void SystemManagerBase::run()
{
	util::Trace trace(util::Trace::kManager, "run SystemManager");

	if(func_ == 0 || func_->size() == 0){
		trace.debug("skip");
		return;
	}

	//ファンクタによってnotifyが起動し，func_自身が書き換えられることがあるのでit.end()とは比較しない
	for(int i = 0;i < func_->size(); i++){
		((*func_)[i])();
	}

}


} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */