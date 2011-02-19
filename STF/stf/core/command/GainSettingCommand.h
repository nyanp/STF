/**
 * @file   GainSettingCommand.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_command_GainSettingCommand_h
#define stf_core_command_GainSettingCommand_h

#include "Command.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {
class PID;
}
}
namespace command {

class GainSettingCommand : public Command {
public:
	GainSettingCommand(const datatype::Time& t, strategy::control::PID* controller, double kp, double ki, double kd)
		: Command(t,"GainSettingCommand"), controller_(controller), kp_(kp), ki_(ki), kd_(kd) {}
	~GainSettingCommand(){}
	virtual void execute();
private:
    GainSettingCommand(const GainSettingCommand &rhs);
    GainSettingCommand &operator=(const GainSettingCommand &rhs);
private:
    strategy::control::PID* controller_;
	double kp_;
	double ki_;
	double kd_;
};

} /* End of namespace stf::core::command */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_command_GainSettingCommand_h
