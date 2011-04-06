/**
 * @file   CommandManagerBase.cpp
 * @brief  コマンドの処理を行う機能マネージャ基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "CommandManagerBase.h"
#include "../../datatype/Time.h"
#include "../command/Command.h"
#include "../devicedriver/clock/ITimeClock.h"
#include "../../util/Trace.h"

namespace stf {
namespace core {
namespace manager {

void CommandManagerBase::run(){
	execute_command_(this->clock_->get_time());
}

void CommandManagerBase::execute_command_(const datatype::Time& t){
	util::Trace trace(util::Trace::kManager, "run CommandManager");
	//実装はリングバッファだが，実装しやすいのでコマンドの確認順序は配列の後ろから
	//実行順序に制約のあるコマンドはトランザクションとして実装するので問題は無いはず
	for(int i = NUM_OF_LIST - 1 ; i >= 0 ; i--){
		if(this->commandList_[i] == 0) continue;
		if(this->commandList_[i]->can_execute(t)){
			trace.debug(commandList_[i]->name().to_char());
			this->commandList_[i]->execute();
			remove_command_(i);
		}
	}
}

void CommandManagerBase::remove_command_(int index){
	delete this->commandList_[index];
	for(int i = index; i < NUM_OF_LIST - 1 ; i++){
		this->commandList_[i] = this->commandList_[i + 1];
	}
	this->commandList_[NUM_OF_LIST] = 0;
}

void CommandManagerBase::notify(const mode::Mode* value){
	//util::Trace trace(util::Trace::kManager, "strategychange CommandManager");
}

} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */
