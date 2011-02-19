/**
 * @file   ModeChangeCommand.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_command_change_modeCommand_h
#define stf_core_command_change_modeCommand_h

#include "Command.h"

namespace stf {
namespace core {
namespace mode {
class ModeBase;
}
namespace manager {
class ModeManagerBase;
}
namespace command {

class change_modeCommand : public Command {
public:
	change_modeCommand(const datatype::Time& t, core::mode::ModeBase *mode, core::manager::ModeManagerBase *modeman)
		: Command(t,"change_modeCommand"), mode_(mode), modeman_(modeman) {}
	~change_modeCommand(){}
	virtual void execute();
	virtual Command* clone(const datatype::Time& t);
	virtual void init(int* params, int paramsize){}//‚È‚É‚à‚µ‚È‚¢
private:
    change_modeCommand(const change_modeCommand &rhs);
    change_modeCommand &operator=(const change_modeCommand &rhs);
private:
    core::mode::ModeBase *mode_;
	core::manager::ModeManagerBase *modeman_;
};

} /* End of namespace stf::core::command */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_command_change_modeCommand_h
