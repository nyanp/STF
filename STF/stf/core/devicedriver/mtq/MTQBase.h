/**
 * @file   MTQBase.h
 * @brief  磁気トルカの基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_mtq_MTQBase_h
#define stf_core_devicedriver_mtq_MTQBase_h

#include "../../../util/stfassert.h"
#include "../AOCSActuator.h"
#include "../../../datatype/Scalar.h"
#include "../../../datatype/Magnetic.h"

namespace stf {
namespace environment {
class Simulator;
}
namespace core {
namespace devicedriver {
namespace mtq {

//! 磁気トルカの基底クラス．
/*! 
	@tparam Env コンポーネントの環境クラス．
*/
template<class Env>
class MTQBase : public AOCSActuator<Env, datatype::MagneticMoment, datatype::Scalar> {
public:
	MTQBase(const datatype::DCM &dcm, double max_torque, double min_torque, double linearity);
	virtual ~MTQBase(){}
	virtual void do_update();
private:
    double linearity_;
};

template<class Env>
MTQBase<Env>::MTQBase(const datatype::DCM &dcm, double max_torque, double min_torque, double linearity) 
	: AOCSActuator<datatype::MagneticMoment, datatype::Scalar, T>( "MTQ", dcm), linearity_(linearity)
{
	this->max_output_ = max_torque;	
	this->min_output_ = min_torque;
}

template<class Env>
void MTQBase<Env>::do_update(){
	stf_static_assert(0 && "Not-Implemented-Exception");
}

template <>
void MTQBase<environment::Simulator>::do_update();

template<>
MTQBase<environment::Simulator>::MTQBase( const datatype::DCM &dcm, double max_torque, double min_torque, double linearity);

} /* End of namespace stf::core::devicedriver::mtq */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_mtq_MTQBase_h
