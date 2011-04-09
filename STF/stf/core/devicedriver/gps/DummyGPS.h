/**
 * @file   DummyGPS.h
 * @brief  TLEのアップリンクで軌道情報を保持するGPSダミー．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_gps_DummyGPS_h
#define stf_core_devicedriver_gps_DummyGPS_h

#include "GPSBase.h"
#include "../../../datatype/OrbitInfo.h"
#include "../../../datatype/TypeConverter.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace gps {

//! TLEのアップリンクで軌道情報を保持するGPSダミー．
/*! 
	@tparam Env コンポーネントの環境クラス．
*/
template<class Env>
class DummyGPS : public GPSBase<Env> {
public:
	DummyGPS(){}
	void set_orbit(const datatype::OrbitInfo& orbit){
		this->set_value(datatype::TypeConverter::toPositionInfo(orbit));//軌道要素を衛星の6次元状態量に変換
	}
	~DummyGPS(){}
private:
};



} /* End of namespace stf::core::devicedriver::gps */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_gps_GPS_h
