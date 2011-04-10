/**
 * @file   TAMBase.h
 * @brief  3軸磁気センサの基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_magnetometer_TAMBase_h
#define stf_core_devicedriver_magnetometer_TAMBase_h

#include "../../../util/stfassert.h"
#include "../../../datatype/Magnetic.h"
#include "../../../util/loki/TypeManip.h"
#include "../../environment/Envfwd.h"

#include "../AOCSSensor.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace magnetometer {


//! 3軸磁気センサの基底クラス．
/*! 
	@tparam Env コンポーネントの環境クラス．
*/
template <class Env>
class TAMBase : public AOCSSensor<Env, datatype::MagneticField, datatype::MagneticField>{
public:
	TAMBase(const datatype::DCM &angle);
	virtual ~TAMBase(){}
	virtual void do_update(){
		do_update(Loki::Type2Type<Env>());
	}
	virtual datatype::MagneticField filter(const datatype::MagneticField& value); 
private:
	template<class T> void do_update(Loki::Type2Type<T>);
	template<class App> void do_update(Loki::Type2Type<environment::Simulator<App> >){
		this->value_ = filter(this->environment_->getMagneticField(*this));
		if(this->datapool_ != 0){
			datapool_->set<TAMBase<environment::Simulator<App> >>(datapool_hold_index_, this->value_);
		}
	}

    TAMBase();
	double err_deg_;
	int sigma_;
};

template <class Env>
TAMBase<Env>::TAMBase(const datatype::DCM& dcm)
	: AOCSSensor<Env, datatype::MagneticField, datatype::MagneticField>( "TAM", dcm){}

template <class Env>
datatype::MagneticField TAMBase<Env>::filter(const datatype::MagneticField& value){
	return value;
}

} /* End of namespace stf::core::devicedriver::magnetometer */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_sunsensor_TAMBase_h
