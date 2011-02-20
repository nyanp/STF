/**
 * @file   MessageCommand.h
 * @brief  予め決められたメッセージを出力するコマンド．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_command_UnaryFunctorCommand_h
#define stf_core_command_UnaryFunctorCommand_h

#include "Command.h"
#include "../functor/Functor.h"
#include "../../datatype/String.h"

namespace stf {
namespace core {
namespace command {

//! 予め決められたメッセージを出力するコマンド．
/*! コンストラクタで指定したメッセージをそのまま返答する．生存確認や，
	@tparam Num 実行するコマンドの数．
*/
class MessageCommand : public Command {
public:
	 MessageCommand(const datatype::Time& t, const datatype::String& msg)
		: msg_(msg), Command(t,"UnaryFunctorCommand") {}
	~ MessageCommand(){}
	virtual void init(int* params, int paramsize){}
	virtual Command* clone(const datatype::Time& t){
		return new MessageCommand(t,msg_);
	}
	virtual void execute(){
		this->rcv_->send_packet(msg_);
	}
private:
	datatype::String msg_;
};


} /* End of namespace stf::core::command */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_command_UnaryFunctorCommand_h
