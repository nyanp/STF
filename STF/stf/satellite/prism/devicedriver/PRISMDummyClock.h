/**
 * @file   PRISMDummyClock.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_clock_PRISMDummyClock_h
#define stf_core_devicedriver_clock_PRISMDummyClock_h
#include "../../../core/devicedriver/Includes.h"
#include "../../../RootObject.h"
#include "../../../util/loki/Typelist.h"
#include "../../../Config.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace clock {

class PRISMDummyClock 
	: public CDHMultiComponent<TYPELIST_2( datatype::Time, datatype::DateTime ), ENV>, virtual public ITimeClock, virtual public IAbsoluteTimeClock
{
public:
	PRISMDummyClock( int year, int month, int date);
	~PRISMDummyClock(void);
	virtual const datatype::Time get_time() const; 
	virtual const datatype::DateTime get_datetime() const;
	virtual void set_absolute_time(datatype::DateTime t);
	virtual void set_absolute_time(int year, int month, int day, int hour, int minute, int second);
	virtual void set_time(datatype::Time t);
	virtual void set_time(int sec, int millisec);
	virtual void do_update();
private:
	PRISMDummyClock(const PRISMDummyClock& rhs);
	PRISMDummyClock& operator =(const PRISMDummyClock& rhs);
	static const int CLOCK = 100;
};

} /* End of namespace stf::core::devicedriver::clock */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_clock_PRISMDummyClock_h
