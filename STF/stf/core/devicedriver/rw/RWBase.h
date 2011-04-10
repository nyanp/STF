/**
 * @file   RWBase.h
 * @brief  リアクションホイールの基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_rw_RWBase_h
#define stf_core_devicedriver_rw_RWBase_h

#include "../../../util/stfassert.h"
#include "../../../util/Macros.h"
#include "../../../datatype/StaticVector.h"
#include "../../../datatype/Scalar.h"
#include "../AOCSActuator.h"

namespace stf {
namespace environment {
template<class App> class Simulator;
}
namespace core {
namespace devicedriver {
namespace rw {

//! リアクションホイールの基底クラス．
/*! 
	@tparam Env コンポーネントの環境クラス．
*/
template<class Env>
class RWBase : public AOCSActuator<Env, datatype::StaticVector<3>, datatype::Scalar>{
public:
	RWBase(const datatype::DCM &dcm, double max_torque, double min_torque, double max_angular_momentum);
	virtual ~RWBase(){}
	virtual double angular_momentum() { return this->angular_momentum_;}
	virtual bool is_saturated() const{ if(this->angular_momentum_ >= this->max_angular_momentum_) return true; return false; }//ホイールが飽和していたらtrue

private:

	DO_UPDATE_SIMULATOR(){
		//角運動量（回転数）の更新
		this->angular_momentum_ += this->output_.value() * App::steptime;

		if(this->datapool_ != 0)
			datapool_->set<RWBase<environment::Simulator<App> >>(datapool_hold_index_, this->output_);
	}

	INIT(){
		this->environment_->attachTorqueSource(this);
	}

    double max_angular_momentum_;
	double angular_momentum_;//内部およびアンローディング制御ブロックで使用する角運動量．
};

template<class Env>
RWBase<Env>::RWBase(const datatype::DCM &dcm, double max_torque, double min_torque, double max_angular_momentum) :
AOCSActuator<Env, datatype::StaticVector<3>, datatype::Scalar>("RW", dcm), max_angular_momentum_(max_angular_momentum)
{
	//this->max_output_ = max_torque;	
	//this->min_output_ = min_torque;
	init();
}

} /* End of namespace stf::core::devicedriver::rw */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_mtq_RWBase_h
