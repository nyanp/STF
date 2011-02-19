/**
 * @file   StrategyBase.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_StrategyBase_h
#define stf_core_strategy_StrategyBase_h

#include "../../RootObject.h"
#include "../datapool/Datapool.h"
#include "../devicedriver/clock/ITimeClock.h"
#include "../IEnabable.h"

namespace stf {
namespace core {
namespace strategy {

class StrategyBase : public RootObject, virtual public IEnabable{
public:
	StrategyBase(int instance_id, const datatype::String& strategy_name) : RootObject(instance_id,strategy_name) {}
	virtual ~StrategyBase(){}
	template<typename T> void connect(util::Type2Type<T>, int rows, const datatype::String name){ 
		this->datapool_hold_index_ = Global<ENV>::getDataPool().create(util::Type2Type<T>(),rows,name);
		datapool_ = &Global<ENV>::getDataPool(); 
	}
	// virtual method for IEnabable(TBD:not implemented in prototype)
	virtual void enable(){}
	virtual void disable(){}
	virtual bool is_enable () const{ return this->is_enabled_; }
protected:
	bool is_enabled_;
private:
	DISALLOW_COPY_AND_ASSIGN(StrategyBase);
};

} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_strategy_StrategyBase_h
