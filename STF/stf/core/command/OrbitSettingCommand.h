/**
 * @file   OrbitSettingCommand.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_command_OrbitSettingCommand_h
#define stf_core_command_OrbitSettingCommand_h

#include "Command.h"

namespace stf {
namespace datatype {
struct OrbitInfo;
}
namespace core {
namespace devicedriver {
namespace gps {
template<class T> class DummyGPS;
}
}
namespace command {

class OrbitSettingCommand : public Command {
public:
	OrbitSettingCommand(const datatype::Time& t, core::devicedriver::gps::DummyGPS<ENV>* gps, datatype::OrbitInfo* orbit)
		: Command(t,"OrbitSettingCommand"), gps_(gps), orbit_(orbit) {}
	~OrbitSettingCommand(){}
	virtual void execute();
private:
    OrbitSettingCommand(const OrbitSettingCommand &rhs);
    OrbitSettingCommand &operator=(const OrbitSettingCommand &rhs);
private:
	core::devicedriver::gps::DummyGPS<ENV>* gps_;
	datatype::OrbitInfo* orbit_;
};

} /* End of namespace stf::core::command */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_command_OrbitSettingCommand_h
