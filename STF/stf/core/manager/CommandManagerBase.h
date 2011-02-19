/**
 * @file   CommandManagerBase.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef core_manager_CommandManagerBase_h
#define core_manager_CommandManagerBase_h
#include <assert.h>
#include "ManagerBase.h"
#include "../../datatype/List.h"
#include "../event/ModeChangeEvent.h"
#include "../event/SubjectBase.h"

namespace stf {
namespace core {
namespace command {
class Command;
}
namespace strategy {
namespace control {
class IControlStrategy;
}
}
namespace mode {
class ModeBase;
} /* End of namespace core::mode */
} /* End of namespace core */

namespace core {
namespace manager {

class CommandManagerBase : public ManagerBase, virtual public event::Observer<event::ModeChangeEvent>{
public:
	//typedef core::strategy::control::IControlStrategy HotSpot;
	//typedef stf::util::Type2Type<HotSpot> SpotType;

	CommandManagerBase(int instance_id) : ManagerBase(instance_id, "CommandManager"), list_index_(0), crit_list_index_(0)
	{
		for(int i = 0; i < NUM_OF_LIST; i++)
			this->commandList_[i] = 0;
	}
	virtual ~CommandManagerBase(){};
    virtual void run();
	virtual bool runnable() const { return true; }
	virtual void notify(const mode::ModeBase* value);
	void addCommand( command::Command* cmd ){
		list_index_++;
		list_index_ %= NUM_OF_LIST;
		commandList_[list_index_] = cmd;
	}
private:
	void executeCommand_(const datatype::Time& t);
	void removeCommand_(int i);
	static const int NUM_OF_LIST = 10;
	command::Command* commandList_[NUM_OF_LIST];
	int list_index_;
	int crit_list_index_;
};


} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // core_manager_CommandManagerBase_h
