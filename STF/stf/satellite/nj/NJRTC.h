/**
 * @file   NJRTC.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_clock_NJRTC_h
#define stf_core_devicedriver_clock_NJRTC_h
#include "../../core/devicedriver/CDHComponent.h"
#include "../../core/devicedriver/clock/ITimeClock.h"
#include "../../core/devicedriver/clock/IAbsoluteTimeClock.h"
#include "../../RootObject.h"
#include "../../util/loki/Typelist.h"
#include "../../Config.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace clock {

class NJRTC : public CDHMultiComponent<TYPELIST_2( datatype::Time, datatype::DateTime ), ENV>, virtual public ITimeClock, virtual public IAbsoluteTimeClock
{
public:
	NJRTC(int instance_id, int year, int month, int date);
	~NJRTC(void);
	virtual const datatype::Time get_time() const; 
	virtual const datatype::DateTime get_datetime() const;
	virtual void set_absolute_time(datatype::DateTime t);
	virtual void set_absolute_time(int year, int month, int day, int hour, int minute, int second);
	virtual void set_time(datatype::Time t);
	virtual void set_time(int sec, int millisec);
	virtual void do_update();
private:
	NJRTC(const NJRTC& rhs);
	NJRTC& operator =(const NJRTC& rhs);
	static const int CLOCK = 100;
};

} /* End of namespace stf::core::devicedriver::clock */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_clock_NJRTC_h
