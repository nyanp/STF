/**
 * @file   NJGPS.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_gps_NJGPS_h
#define stf_core_devicedriver_gps_NJGPS_h

#include "../../core/devicedriver/gps/GPSBase.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace gps {

// TLEのアップリンクで軌道情報を保持するGPSダミー．
template<class T>
class NJGPS : public GPSBase<T> {
public:
	NJGPS(){}
	//Sigma =0.02, tau(ECRV)=1000sec
	NJGPS(int instance_id) : GPSBase(instance_id){}
	void setOrbit(const datatype::OrbitInfo& orbit){
		this->setValue(datatype::TypeConverter::toPositionInfo(orbit));//軌道要素を衛星の6次元状態量に変換
	}
	~NJGPS(){}
private:
};



} /* End of namespace stf::core::devicedriver::gps */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_gps_GPS_h
