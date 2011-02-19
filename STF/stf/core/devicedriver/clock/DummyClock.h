/**
 * @file   DummyClock.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_clock_DummyClock_h
#define stf_core_devicedriver_clock_DummyClock_h
#include "ITimeClock.h"
#include "IAbsoluteTimeClock.h"
#include "../CDHComponent.h"
#include "../IDataUpdatable.h"
#include "../../../RootObject.h"
#include "../../../util/TypeList.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace clock {

class DummyClock : public CDHMultiComponent< TYPELIST_2( datatype::Time, datatype::DateTime ) >, virtual public ITimeClock, virtual public IAbsoluteTimeClock
{
public:
	DummyClock(int instance_id, int year, int month, int date);
	~DummyClock(void);
	virtual const datatype::Time getTime() const; 
	virtual const datatype::DateTime getAbsoluteTime() const;
	virtual void set_absolute_time(datatype::DateTime t);
	virtual void set_absolute_time(int year, int month, int day, int hour, int minute, int second);
	virtual void set_time(datatype::Time t);
	virtual void set_time(int sec, int millisec);
	virtual void doUpdate();
private:
	DummyClock(const DummyClock& rhs);
	DummyClock& operator =(const DummyClock& rhs);
	static const int CLOCK = 100;
};

} /* End of namespace stf::core::devicedriver::clock */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_clock_DummyClock_h
