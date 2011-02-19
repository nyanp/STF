/**
 * @file   SequenceCommand.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_command_SequenceCommand_h
#define stf_core_command_SequenceCommand_h
#include <assert.h>
#include "Command.h"
#include "../../datatype/Time.h"

namespace stf {
namespace core {
namespace command {

template<int Num>
class SequenceCommand : public Command {
public:
	SequenceCommand(const datatype::Time& t)
		: Command(t,"SequenceCommand"), index_(-1){
			for(int i = 0; i < Num; i++) commands_[i] = 0;
	}
	~SequenceCommand(){
		if(index_ != -1){
			for(int i = 0; i <= index_; i++)
				delete commands_[i];
		}
	}
	virtual bool canExecute(const datatype::Time& t){
		if(index_ == -1) return false; //コマンドが1つもない
		if(this->time_ > t) return false; //まだ開始時刻ではない
		for(int i = 0; i < index_; i++){
			if(!commands_[i]->canExecute(t)) return false; //すべてのコマンドが実行可能になるまで実行しない
		}
		return true;
	}
	void addCommand(Command* command){
		index_++;
		assert(index_ < Num);
		commands_[index_] = command;
	}
	virtual void execute(){
		for(int i = 0; i < index_; i++){
			commands_[i]->execute();//順番に実行
		}
	}
private:
    SequenceCommand(const SequenceCommand &rhs);
    SequenceCommand &operator=(const SequenceCommand &rhs);
	Command* commands_[Num];
	int index_;
};

} /* End of namespace stf::core::command */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_command_SequenceCommand_h
