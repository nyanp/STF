/**
 * @file   StrategyBase.h
 * @brief  ストラテジの共通基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_StrategyBase_h
#define stf_core_strategy_StrategyBase_h

#include "../../RootObject.h"
#include "../datapool/Datapool.h"
#include "../devicedriver/clock/ITimeClock.h"
#include "../../interface/IEnabable.h"
#include "../../util/loki/TypeManip.h"

namespace stf {
namespace core {
namespace strategy {

//! ストラテジの共通基底クラス．
/*! */
class StrategyBase : public RootObject, virtual public interface::IEnabable{
public:
	StrategyBase(int instance_id, const datatype::String& strategy_name) : RootObject(instance_id,strategy_name) {}
	virtual ~StrategyBase(){}
	//! ストラテジの有効化．
	virtual void enable(){ is_enabled_ = true; }
	//! ストラテジの無効化．
	virtual void disable(){ is_enabled_ = false; }
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
