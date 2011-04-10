/**
 * @file   NJRTC.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_clock_NJRTC_h
#define stf_core_devicedriver_clock_NJRTC_h
#include "../../../core/devicedriver/CDHComponent.h"
#include "../../../core/devicedriver/clock/ITimeClock.h"
#include "../../../core/devicedriver/clock/IAbsoluteTimeClock.h"
#include "../../../RootObject.h"
#include "../../../util/loki/Typelist.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace clock {

template<class Env>
class NJRTC : public CDHMultiComponent<Env, TYPELIST_2( datatype::Time, datatype::DateTime )>, virtual public ITimeClock, virtual public IAbsoluteTimeClock
{
public:
	NJRTC( int year, int month, int date);
	~NJRTC(void){}
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

template<class Env>
NJRTC<Env>::NJRTC( int year, int month, int date)
	: CDHMultiComponent<Env, TYPELIST_2( datatype::Time, datatype::DateTime )>( "NJRTC")//, datetime_(year, month, date)
{
	const_cast<datatype::DateTime*>(&get<1, datatype::DateTime>())->init(year, month, date, 0, 0, 0);
	this->clock_ = this;//staticƒ|ƒCƒ“ƒ^‚ÉŠ„‚è“–‚Ä
}

template<class Env>
const datatype::Time NJRTC<Env>::get_time() const {
	return this->get<0, datatype::Time>();
}

template<class Env>
const datatype::DateTime NJRTC<Env>::get_datetime() const {
	return this->get<1, datatype::DateTime>();
}

template<class Env>
void NJRTC<Env>::set_absolute_time(datatype::DateTime t){
	this->outputport<1, datatype::DateTime>().value_ = t;
}

template<class Env>
void NJRTC<Env>::set_absolute_time(int year, int month, int day, int hour, int minute, int second){
	this->outputport<1, datatype::DateTime>().value_.init(year, month, day, hour, minute, second);
}

template<class Env>
void NJRTC<Env>::set_time(datatype::Time t){
	this->outputport<0, datatype::Time>().value_ = t;
}

template<class Env>
void NJRTC<Env>::set_time(int sec, int millisec){
	this->outputport<0, datatype::Time>().value_.clear();
	this->outputport<0, datatype::Time>().value_.add_milliseconds(millisec);
	this->outputport<0, datatype::Time>().value_.add_seconds(sec);
}

template<class Env>
void NJRTC<Env>::do_update()
{
	const_cast<datatype::Time*>(&get<0, datatype::Time>())->add_milliseconds(this->CLOCK);
	//this->time_.add_milliseconds(this->CLOCK);
}

} /* End of namespace stf::core::devicedriver::clock */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_clock_NJRTC_h
