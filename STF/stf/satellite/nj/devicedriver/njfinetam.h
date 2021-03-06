/**
 * @file   NJFineTAM.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_magnetometer_NJFineTAM_h
#define stf_core_devicedriver_magnetometer_NJFineTAM_h

#include "../../../core/devicedriver/magnetometer/TAMBase.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace magnetometer {
template <class T>
class NJFineTAM : public TAMBase<T>{
public:  
	// 3-Sigmaで1度精度
	NJFineTAM( const datatype::DCM &angle) : TAMBase( angle){}
	~NJFineTAM(){}
	virtual void do_update(){}
private:
	NJFineTAM(){}
};

} /* End of namespace stf::core::devicedriver::magnetometer */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_magnetometer_NJFineTAM_h
