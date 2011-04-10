/**
 * @file   GPSBase.h
 * @brief  GPSセンサの基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_gps_GPSBase_h
#define stf_core_devicedriver_gps_GPSBase_h

#include "../../../util/stfassert.h"
#include "../../../datatype/OrbitInfo.h"
#include "../AOCSSensor.h"
#include "../clock/IAbsoluteTimeClock.h"
#include "../../../datatype/DateTime.h"
#include "../../environment/Envfwd.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace gps {

//! GPSセンサの基底クラス．
/*! 
	@tparam Env コンポーネントの環境クラス．
*/
template <class Env>
class GPSBase : public AOCSSensor<Env, datatype::PositionInfo, datatype::PositionInfo>, virtual public clock::IAbsoluteTimeClock{
public:
	GPSBase(): AOCSSensor<Env, datatype::PositionInfo, datatype::PositionInfo>("GPS"){}
	~GPSBase(){}
	virtual const datatype::DateTime get_datetime() const {return t_;}
	virtual void set_absolute_time(datatype::DateTime t) {t_ = t;}
	virtual void set_absolute_time(int year, int month, int day, int hour, int minute, int second){
		t_.init(year, month, day, hour, minute, second);
	}
	virtual datatype::PositionInfo filter(const datatype::PositionInfo& value); 
protected:
	DO_UPDATE_SIMULATOR(){
		this->value_ = filter(this->environment_->getTrueSatellitePosition());

		//if(this->datapool_ != 0){
		//	datapool_->set<GPSBase<environment::Simulator<App> >>(datapool_hold_index_, this->value_);
		//}
	}

	datatype::DateTime t_;
};


template <class Env>
datatype::PositionInfo GPSBase<Env>::filter(const datatype::PositionInfo& value){
	return value;
}

} /* End of namespace stf::core::devicedriver::gyro */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_gps_GPSBase_h
