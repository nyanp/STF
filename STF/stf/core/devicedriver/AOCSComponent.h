/**
 * @file   AOCSComponent.h
 * @brief  センサおよびアクチュエータの基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */

#ifndef stf_core_devicedriver_AOCSComponent_h
#define stf_core_devicedriver_AOCSComponent_h

#include "IDataUpdatable.h"
#include "ISwitchable.h"
#include "IOPort.h"
#include "../../RootObject.h"
#include "../../datatype/DCM.h"
#include "../../datatype/Magnetic.h"
#include "../../datatype/Scalar.h"
#include "../../datatype/String.h"
#include "../../datatype/Time.h"
#include "../../datatype/OrbitInfo.h"
#include "../../datatype/Quaternion.h"
#include "../../datatype/TypeConverter.h"
#include "../../datatype/StaticVector.h"
#include "../datapool/Datapool.h"
#include "../../util/Macros.h"

namespace stf {
namespace core {
namespace datapool {
template<class T> class Datapool;
}
namespace devicedriver {

//! センサおよびアクチュエータの基底クラス．
/*! 
	@tparam T   測定している物理量を表す型．Targetにtypedefされる
	@tparam U   可観測次元の量を表す型．全軸感度を持ったコンポーネントの場合はT=U．Holdにtypedefされる
	@tparam Env コンポーネントの環境クラス．
*/
template<class T, class U, class Env>
class AOCSComponent : public RootObject, virtual public IDataUpdatable, virtual public ISwitchable {
public:
	typedef Env Environment;//!< 環境クラス．
	typedef T Target;//!< 測定している物理量を表す型．
	typedef U Hold;//!< 可観測次元の量を表す型．全軸感度を持ったコンポーネントの場合はT=U

	AOCSComponent(int instance_id, const datatype::String& name, const datatype::DCM& dcm);
	AOCSComponent(int instance_id, const datatype::String& name);
	void connect(core::datapool::AocsDataPool* pool, int rows, const datatype::String name){ 
		this->datapool_hold_index_ = pool->create(this, rows, name);
		datapool_ = pool; 
	}
	const datatype::DCM& get_transfomer() const{ return set_angle_; }

	virtual void on(){ is_on_ = true;}
	virtual void off(){ is_on_ = false;}
	virtual bool is_on() const{ return is_on_; }
	virtual void do_compute(const datatype::Time& t){}
	virtual ~AOCSComponent(){}
protected:
	bool is_on_;
	Env* environment_;
	//virtual void component_on() = 0;
	//virtual void compoent_off() = 0;
	//! コンポーネント座標系から機体座標系へのDCM．
	/*! 計算負荷の都合から，通常の取り付け行列の逆行列となっている．value_b_ = set_angle_ * value_ */
    datatype::DCM set_angle_;
private:
    AOCSComponent();
	DISALLOW_COPY_AND_ASSIGN_3(AOCSComponent, T, U, Env);
};

template<class T, class U, class Env>
AOCSComponent<T, U, Env>::AOCSComponent(int instance_id, const datatype::String& name)
	: RootObject(instance_id, name)
{
	this->environment_ = &Env::get_instance();
}

template<class T, class U, class Env>
AOCSComponent<T, U, Env>::AOCSComponent(int instance_id, const datatype::String& name, const datatype::DCM& dcm)
	: set_angle_(dcm), RootObject(instance_id, name)
{
	this->environment_ = &Env::get_instance();
}


} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_AOCSComponent_h
