/**
 * @file   Command.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_command_Command_h
#define stf_core_command_Command_h

#include "../../RootObject.h"
#include "../../util/Ostream.h"
#include "../../datatype/Time.h"
#include "../../datatype/String.h"
#include "../devicedriver/cmhandler/ICommandReceiver.h"

namespace stf {
namespace core {
namespace devicedriver {

}
namespace command {

class Command : public RootObject {
public:
	Command(const datatype::Time& t, const datatype::String& name) : RootObject(0, name), rcv_(0),time_(t) {}
	virtual ~Command(){}
	const datatype::Time& getTime() const { return time_; }
	void  connectReceiver(devicedriver::cmhandler::ICommandReceiver* rcv) { rcv_ = rcv; }
	virtual void execute() = 0;
	virtual Command* clone(const datatype::Time& t) = 0;
	virtual void init(int* params, int paramsize) = 0;
	virtual bool canExecute(const datatype::Time& t) { if(t >= time_ ) return true; return false; }//デフォルトの実装．時刻以外で判断してもよい
private:
    Command(const Command &rhs);
    Command &operator=(const Command &rhs);
protected:
	datatype::Time time_;
	devicedriver::cmhandler::ICommandReceiver* rcv_;
};

} /* End of namespace stf::core::command */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_command_Command_h
