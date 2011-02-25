/**
 * @file   AOCSComponent.h
 * @brief  センサおよびアクチュエータの基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 * @todo   copyToBodyFrame_の特殊化を洗練させる
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

//#include "../../GlobalObject.h"
#include "../../Macros.h"

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
template<class T,class U = T,class Env = ENV>
class AOCSComponent : public RootObject, virtual public IDataUpdatable, virtual public ISwitchable, public OutputPorts< TYPELIST_1(U) > {
public:
	typedef T Target;//測定している物理量を表す型．
	typedef U Hold;//可観測次元の量を表す型．全軸感度を持ったコンポーネントの場合はT=U
	AOCSComponent(int instance_id, const datatype::String& name, const datatype::DCM& dcm);
	AOCSComponent(int instance_id, const datatype::String& name);
	void connect(core::datapool::AocsDataPool* pool,int rows, const datatype::String name){ 
		this->datapool_hold_index_ = pool->create(this,rows,name);
		datapool_ = pool; 
	}
	const datatype::DCM& getDCM() const{ return set_angle_; }

	virtual void on(){ is_on_ = true;}
	virtual void off(){ is_on_ = false;}
	virtual bool is_on() const{ return is_on_; }
	virtual void set_value(const U& value) { 
		value_ = value; 
		copyToBodyFrame_(Loki::Type2Type<Target>(),Loki::Type2Type<Hold>());
		this->last_update_ = this->clock_->get_time();
	}
	virtual void set_in_bodyframe(const T& value){ 
		value_b_ = value; 	
		copyToLocalFrame_(Loki::Type2Type<Target>(),Loki::Type2Type<Hold>());
		this->last_update_ = this->clock_->get_time(); 	
	}
	virtual const U& get_value() const{ return value_; }
	virtual const T& get_in_bodyframe(){ return value_b_;}//get_value(Loki::Type2Type<Target>(),Loki::Type2Type<Hold>());}
	virtual void do_compute(const datatype::Time& t){}
	virtual ~AOCSComponent(){}
protected:
	bool is_on_;
	T value_b_;
	Env* environment_;
	//! コンポーネント座標系から機体座標系へのDCM．
	/*! 計算負荷の都合から，通常の取り付け行列の逆行列となっている．value_b_ = set_angle_ * value_ */
    datatype::DCM set_angle_;

private:
	void copyToLocalFrame_(Loki::Type2Type<datatype::StaticVector<3>>,Loki::Type2Type<datatype::Scalar>);
	void copyToLocalFrame_(Loki::Type2Type<datatype::StaticVector<3>>,Loki::Type2Type<datatype::StaticVector<3>>);	
	void copyToLocalFrame_(Loki::Type2Type<datatype::StaticVector<2>>,Loki::Type2Type<datatype::StaticVector<2>>);
	void copyToLocalFrame_(Loki::Type2Type<datatype::Quaternion>,Loki::Type2Type<datatype::Quaternion>);
	void copyToLocalFrame_(Loki::Type2Type<datatype::MagneticField>,Loki::Type2Type<datatype::MagneticField>);
	void copyToLocalFrame_(Loki::Type2Type<datatype::MagneticMoment>,Loki::Type2Type<datatype::MagneticMoment>);
	void copyToLocalFrame_(Loki::Type2Type<datatype::MagneticMoment>,Loki::Type2Type<datatype::Scalar>);
	void copyToLocalFrame_(Loki::Type2Type<datatype::PositionInfo>,Loki::Type2Type<datatype::PositionInfo>){ this->value_ = this->value_b_; }
	void copyToBodyFrame_(Loki::Type2Type<datatype::StaticVector<3>>,Loki::Type2Type<datatype::Scalar>);
	void copyToBodyFrame_(Loki::Type2Type<datatype::StaticVector<3>>,Loki::Type2Type<datatype::StaticVector<3>>);	
	void copyToBodyFrame_(Loki::Type2Type<datatype::StaticVector<2>>,Loki::Type2Type<datatype::StaticVector<2>>);	
	void copyToBodyFrame_(Loki::Type2Type<datatype::Quaternion>,Loki::Type2Type<datatype::Quaternion>);
	void copyToBodyFrame_(Loki::Type2Type<datatype::MagneticField>,Loki::Type2Type<datatype::MagneticField>);
	void copyToBodyFrame_(Loki::Type2Type<datatype::MagneticMoment>,Loki::Type2Type<datatype::MagneticMoment>);
	void copyToBodyFrame_(Loki::Type2Type<datatype::MagneticMoment>,Loki::Type2Type<datatype::Scalar>);
	void copyToBodyFrame_(Loki::Type2Type<datatype::PositionInfo>,Loki::Type2Type<datatype::PositionInfo>){ this->value_b_ = this->value_; }
    AOCSComponent();
	DISALLOW_COPY_AND_ASSIGN_3(AOCSComponent,T,U,Env);
};

template<class T,class U,class Env>
AOCSComponent<T,U,Env>::AOCSComponent(int instance_id, const datatype::String& name) : RootObject(instance_id,name)
{
	this->environment_ = &Env::get_instance();
}

template<class T,class U,class Env>
AOCSComponent<T,U,Env>::AOCSComponent(int instance_id, const datatype::String& name, const datatype::DCM& dcm) : set_angle_(dcm), RootObject(instance_id,name)
{
	this->environment_ = &Env::get_instance();
}

template<class T,class U,class Env>
void AOCSComponent<T,U,Env>::copyToBodyFrame_(Loki::Type2Type<datatype::StaticVector<3>>,Loki::Type2Type<datatype::Scalar>){
	for(int i = 0; i < 3; i++)
		this->value_b_[i] = this->set_angle_[i][2] * this->value_.value();
}

template<class T,class U,class Env>
void AOCSComponent<T,U,Env>::copyToBodyFrame_(Loki::Type2Type<datatype::Quaternion>,Loki::Type2Type<datatype::Quaternion>){
	datatype::Quaternion q = datatype::TypeConverter::toQuaternion(this->set_angle_);
	this->value_b_ = q * this->value_;
}

template<class T,class U,class Env>
void AOCSComponent<T,U,Env>::copyToBodyFrame_(Loki::Type2Type<datatype::StaticVector<3>>,Loki::Type2Type<datatype::StaticVector<3>>){
	this->value_b_ = this->set_angle_ * this->value_;
}

template<class T,class U,class Env>
void AOCSComponent<T,U,Env>::copyToBodyFrame_(Loki::Type2Type<datatype::MagneticField>,Loki::Type2Type<datatype::MagneticField>){
	this->value_b_ = this->set_angle_ * this->value_;
}

template<class T,class U,class Env>
void AOCSComponent<T,U,Env>::copyToBodyFrame_(Loki::Type2Type<datatype::MagneticMoment>,Loki::Type2Type<datatype::MagneticMoment>){
	this->value_b_ = this->set_angle_ * this->value_;
}

template<class T,class U,class Env>
void AOCSComponent<T,U,Env>::copyToBodyFrame_(Loki::Type2Type<datatype::MagneticMoment>,Loki::Type2Type<datatype::Scalar>){
	for(int i = 0; i < 3; i++)
		this->value_b_[i] = this->set_angle_[i][2] * this->value_.value();
}


template<class T,class U,class Env>
void AOCSComponent<T,U,Env>::copyToBodyFrame_(Loki::Type2Type<datatype::StaticVector<2>>,Loki::Type2Type<datatype::StaticVector<2>>){
	//一旦直交座標系に戻してから極座標系に再変換
	this->value_b_ = datatype::TypeConverter::toPolar(this->set_angle_ * datatype::TypeConverter::toRectangular(this->value_));
}

template<class T,class U,class Env>
void AOCSComponent<T,U,Env>::copyToLocalFrame_(Loki::Type2Type<datatype::StaticVector<3>>,Loki::Type2Type<datatype::Scalar>){
	this->value_ = this->value_b_[0] / set_angle_[0][2];
}

template<class T,class U,class Env>
void AOCSComponent<T,U,Env>::copyToLocalFrame_(Loki::Type2Type<datatype::Quaternion>,Loki::Type2Type<datatype::Quaternion>){
	datatype::Quaternion q = datatype::TypeConverter::toQuaternion(this->set_angle_).conjugate();
	this->value_ = q * this->value_b_;
}

template<class T,class U,class Env>
void AOCSComponent<T,U,Env>::copyToLocalFrame_(Loki::Type2Type<datatype::StaticVector<3>>,Loki::Type2Type<datatype::StaticVector<3>>){
	this->value_ = this->set_angle_.inverse() * this->value_b_;
}

template<class T,class U,class Env>
void AOCSComponent<T,U,Env>::copyToLocalFrame_(Loki::Type2Type<datatype::MagneticField>,Loki::Type2Type<datatype::MagneticField>){
	this->value_ = this->set_angle_.inverse() * this->value_b_;
}

template<class T,class U,class Env>
void AOCSComponent<T,U,Env>::copyToLocalFrame_(Loki::Type2Type<datatype::MagneticMoment>,Loki::Type2Type<datatype::MagneticMoment>){
	this->value_ = this->set_angle_.inverse() * this->value_b_;
}

template<class T,class U,class Env>
void AOCSComponent<T,U,Env>::copyToLocalFrame_(Loki::Type2Type<datatype::MagneticMoment>,Loki::Type2Type<datatype::Scalar>){
	this->value_ = this->value_b_[0] / set_angle_[0][2];
}

template<class T,class U,class Env>
void AOCSComponent<T,U,Env>::copyToLocalFrame_(Loki::Type2Type<datatype::StaticVector<2>>,Loki::Type2Type<datatype::StaticVector<2>>){
	//一旦直交座標系に戻してから極座標系に再変換
	this->value_ = datatype::TypeConverter::toPolar(this->set_angle_.inverse() * datatype::TypeConverter::toRectangular(this->value_b_));
}


} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_AOCSComponent_h
