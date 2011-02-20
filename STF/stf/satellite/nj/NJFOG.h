/**
 * @file   NJFOG.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_NJFOG_NJFOG_h
#define stf_core_devicedriver_NJFOG_NJFOG_h

#include "../../core/devicedriver/gyro/GyroBase.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace gyro {

template<class T>
class NJFOG : public GyroBase<T> {
public:
	NJFOG(){}
	//Sigma =0.0001, tau(ECRV)=1000sec
	NJFOG(int instance_id, const datatype::DCM &angle) : GyroBase(instance_id, angle,0.0001,GYROECRV){}
	~NJFOG(){}
	virtual void do_update(){}
private:
};



} /* End of namespace stf::core::devicedriver::gyro */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_NJFOG_NJFOG_h
