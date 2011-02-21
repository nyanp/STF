/**
 * @file   GPSBase.h
 * @brief  GPSセンサの基底クラス
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_gps_GPSBase_h
#define stf_core_devicedriver_gps_GPSBase_h

#include "../../../datatype/OrbitInfo.h"
#include "../AOCSSensor.h"
#include "../clock/IAbsoluteTimeClock.h"
#include "../../../datatype/DateTime.h"

namespace stf {
namespace environment {
class Simulator;
}
namespace core {
namespace devicedriver {
namespace gps {

//! GPSセンサの基底クラス．
/*! 
	@tparam T コンポーネントの環境クラス．
*/
template <class T>
class GPSBase : public AOCSSensor<datatype::PositionInfo, datatype::PositionInfo, T>, virtual public clock::IAbsoluteTimeClock{
public:
	GPSBase(int instance_id): AOCSSensor<datatype::PositionInfo, datatype::PositionInfo, T>(instance_id, "GPS"){}
	~GPSBase(){}
	virtual void do_update();
	virtual const datatype::DateTime get_datetime() const {return t_;}
	virtual void set_absolute_time(datatype::DateTime t) {t_ = t;}
	virtual void set_absolute_time(int year, int month, int day, int hour, int minute, int second){
		t_.init(year,month,day,hour,minute,second);
	}
	virtual datatype::PositionInfo filter(const datatype::PositionInfo& value); 
protected:
	datatype::DateTime t_;
};


template <class T>
void GPSBase<T>::do_update(){

}

template <>
void GPSBase<environment::Simulator>::do_update();
template <>
datatype::PositionInfo GPSBase<environment::Simulator>::filter(const datatype::PositionInfo& value); 
} /* End of namespace stf::core::devicedriver::gyro */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_gps_GPSBase_h
