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
#include "../../../util/Macros.h"
#include "../../../util/loki/TypeManip.h"
#include "../AOCSActuator.h"
#include "../../../datatype/Scalar.h"
#include "../../../datatype/Magnetic.h"
#include "../../environment/Envfwd.h"

namespace stf {
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
private:

	DO_UPDATE_SIMULATOR(){
		//線形性誤差の付加→TBD
		//this->linearity_ * 0.01
		//DBへ記録
		if(this->datapool_ != 0){
			datapool_->set<MTQBase<environment::Simulator<App> >>(this->datapool_hold_index_, this->output_);
		}
	}

	INIT(){
		this->environment_->attachMagneticSource(this);
	}

    double linearity_;
};

template<class Env>
MTQBase<Env>::MTQBase(const datatype::DCM &dcm, double max_torque, double min_torque, double linearity) 
	: AOCSActuator<Env, datatype::MagneticMoment, datatype::Scalar>( "MTQ", dcm), linearity_(linearity)
{
	//this->max_output_ = max_torque;	
	//this->min_output_ = min_torque;
	init();
}

} /* End of namespace stf::core::devicedriver::mtq */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_mtq_MTQBase_h
