/**
 * @file   DummyClock.h
 * @brief  ダミーの時刻計算を行うコンポーネントドライバ．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_clock_DummyClock_h
#define stf_core_devicedriver_clock_DummyClock_h

#include "ITimeClock.h"
#include "IAbsoluteTimeClock.h"
#include "../CDHComponent.h"
#include "../../../util/loki/Typelist.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace clock {

//! ダミーの時刻計算を行うコンポーネントドライバ．
/*! 
	IDataUpdatable::doUpdateが呼び出されるたびに，CLOCKミリ秒だ内部時刻が進む．
	
	@tparam Env   環境クラス．
	@tparam CLOCK 時計の刻み幅（単位ミリ秒）．
*/
template<class Env, int CLOCK = 100>
class DummyClock : public CDHMultiComponent<Env, TYPELIST_2( datatype::Time, datatype::DateTime )>, virtual public ITimeClock, virtual public IAbsoluteTimeClock
{
public:
	DummyClock(int year, int month, int date): CDHMultiComponent<Env, TYPELIST_2( datatype::Time, datatype::DateTime )>("DummyClock")
	{
		const_cast<datatype::DateTime*>(&get<1, datatype::DateTime>())->init(year, month, date, 0, 0, 0);
		this->clock_ = this;//staticポインタに割り当て
	}

	~DummyClock(void){}

	virtual const datatype::Time get_time() const  {
		return this->get<0, datatype::Time>();
	}

	virtual const datatype::DateTime get_datetime() const {
		return this->get<1, datatype::DateTime>();
	}

	virtual void set_absolute_time(datatype::DateTime t){
		this->outputport<1, datatype::DateTime>().value_ = t;
	}

	virtual void set_absolute_time(int year, int month, int day, int hour, int minute, int second){
		this->outputport<1, datatype::DateTime>().value_.init(year, month, day, hour, minute, second);
	}

	virtual void set_time(datatype::Time t){
		this->outputport<0, datatype::Time>().value_ = t;
	}

	virtual void set_time(int sec, int millisec){
		this->outputport<0, datatype::Time>().value_.clear();
		this->outputport<0, datatype::Time>().value_.add_milliseconds(millisec);
		this->outputport<0, datatype::Time>().value_.add_seconds(sec);
	}

	virtual void do_update(){
		const_cast<datatype::Time*>(&get<0, datatype::Time>())->add_milliseconds(CLOCK);
	}
};

} /* End of namespace stf::core::devicedriver::clock */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_clock_DummyClock_h
