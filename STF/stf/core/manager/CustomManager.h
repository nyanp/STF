/**
 * @file   CustomManager.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_manager_CustomManager_h
#define stf_core_manager_CustomManager_h

#include "CustomManagerBase.h"

namespace stf {
namespace core {
namespace manager {

class CustomManager : public CustomManagerBase
{
public:
	CustomManager(int instance_id) : CustomManagerBase(instance_id){}
	~CustomManager(){}
	virtual void run();
	virtual bool runnable();
protected:
};

} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_manager_CustomManager_h