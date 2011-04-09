/**
 * @file   PRISMTelemetryStrategy.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_telemetry_PRISMTelemetryStrategy_h
#define stf_core_strategy_telemetry_PRISMTelemetryStrategy_h
#include "../../../core/strategy/telemetry/SelectingOutput.h"

namespace stf {
namespace interface {
template<int SCALE, int DEPTH> class PRISMTelemetryIterator;
}
namespace core {
namespace devicedriver {
namespace clock {
class PRISMDummyClock;
}
}
namespace strategy {
namespace telemetry {

// PRISMのテレメトリ（AOCS/CDH/詳細/粗履歴）を担当するStrategy.
// 基本的にはSelectingOutputの実装を引き継いでいるが，外部イテレータへ実装を公開する点，
// 時刻によって開始と終了を制御する点が異なる．
template<int SCALE>
class PRISMTelemetryStrategy : public SelectingOutput<short, SCALE> {
public:
	PRISMTelemetryStrategy
	(
		int instance_id,
		devicedriver::tmhandler::ITelemetryStoragable* storage,
		const core::datapool::AocsDataPool* pool,
		const core::datapool::EventDataPool* eventpool,
		const devicedriver::clock::PRISMDummyClock* clock
	) 
		: SelectingOutput<short, SCALE>(instance_id, storage, pool, eventpool), clock_(clock){}

	void setstate(bool enable) { is_enabled_ = enable; }

	virtual void write_to_telemetry(){
		if(is_enabled_)
			if( this->start_obc_ >= this->clock_->get_time() || this->start_rtc_ >= this->clock_->get_datetime() ){
				SelectingOutput<short, SCALE>::write_to_telemetry();
			}
	}

	void set_time(int second){
		this->start_obc_.clear();
		this->start_obc_.add_seconds(second);
	}

	void setRTCTime(int year, int month, int date, int hour, int minute, int second){
		this->start_rtc_.init(year, month, date, hour, minute, second);
	}
private:
	// どちらか一方が超え，かつテレメ有効フラグが立っていたら取得開始．データがいっぱいになり，かつ上書き禁止モードのとき取得停止．
	datatype::DateTime start_rtc_;
	datatype::Time start_obc_;
	const devicedriver::clock::PRISMDummyClock* clock_;
	bool is_enabled_;
	template<int SCALE, int DEPTH> friend class PRISMTelemetryIterator;
};

} /* End of namespace stf::core::strategy::telemetry */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_strategy_telemetry_OutputAll_h