/**
 * @file   UnitManagerBase.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_manager_UnitManagerBase_h
#define stf_core_manager_UnitManagerBase_h

#include "ManagerBase.h"
#include "../../datatype/List.h"
#include "../event/ModeChangeEvent.h"
#include "../event/SubjectBase.h"
#include "ModeManagerBase.h"

namespace stf {
namespace core {
namespace devicedriver {
class IDataUpdatable;
}
namespace manager {

class UnitManagerBase : public ManagerBase, virtual public event::Observer<event::ModeChangeEvent>
{
public:
	typedef core::devicedriver::IDataUpdatable HotSpot;
	typedef stf::util::Type2Type<core::devicedriver::IDataUpdatable> SpotType;

	UnitManagerBase(int instance_id) : ManagerBase(instance_id, "UnitManager"), unit_list_(0) {}
	virtual ~UnitManagerBase(){}

    void run();
	bool runnable() const { return true; }
	virtual void notify(const mode::ModeBase* value);
protected:
    const datatype::List<HotSpot>* unit_list_;
};

} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_manager_UnitManagerBase_h