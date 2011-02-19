/**
 * @file   AOCSComponent.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */

#ifndef stf_core_devicedriver_AOCSComponent_h
#define stf_core_devicedriver_AOCSComponent_h

#include "IDataUpdatable.h"
#include "IDatapoolProducer.h"
#include "ISwitchable.h"
#include "../../datatype/DCM.h"
#include "../../datatype/Vector.h"
#include "../../datatype/Magnetic.h"
#include "../../datatype/Scalar.h"
#include "../../datatype/String.h"
#include "../../datatype/Time.h"
#include "../../datatype/OrbitInfo.h"
#include "../../RootObject.h"
#include "../../datatype/TypeConverter.h"
#include "../datapool/Datapool.h"
#include "IOPort.h"
#include "../../GlobalObject.h"

namespace stf {
namespace core {
namespace datapool {
template<class T> class Datapool;
}
namespace devicedriver {


///センサ，アクチュエータの基本クラス．
template<class T,class U = T,class Env = ENV>
class AOCSComponent : public RootObject, virtual public IDataUpdatable, virtual public ISwitchable, public OutputPorts< TYPELIST_1(T) > {
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
	virtual void setValue(const U& value) { 
		value_ = value; 
		copyToBodyFrame_(Loki::Type2Type<Target>(),Loki::Type2Type<Hold>());
		this->last_update_ = this->clock_->getTime();
	}
	virtual void setValueInBodyFrame(const T& value){ 
		value_b_ = value; 	
		copyToLocalFrame_(Loki::Type2Type<Target>(),Loki::Type2Type<Hold>());
		this->last_update_ = this->clock_->getTime(); 	
	}
	virtual const U& getValue() const{ return value_; }
	virtual const T& getValueInBodyFrame(){ return value_b_;}//getValue(Loki::Type2Type<Target>(),Loki::Type2Type<Hold>());}
	virtual void do_compute(const datatype::Time& t){}
	virtual ~AOCSComponent(){}
protected:
	bool is_on_;
	U value_;
	//U value_max_;//正常範囲内での最大値．
	//T value_b_;
	Env* environment_;
    ///アライメント補正を考慮するかどうか．高精度の場合のみtrue
    //bool use_alignment_;
	//コンポーネント座標系から機体座標系へのDCM．
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
	AOCSComponent(const AOCSComponent<T,U,Env>& rhs);
};

template<class T,class U,class Env>
AOCSComponent<T,U,Env>::AOCSComponent(int instance_id, const datatype::String& name) : RootObject(instance_id,name)
{
	this->environment_ = &Env::getInstance();
}

template<class T,class U,class Env>
AOCSComponent<T,U,Env>::AOCSComponent(int instance_id, const datatype::String& name, const datatype::DCM& dcm) : set_angle_(dcm), RootObject(instance_id,name)
{
	this->environment_ = &Env::getInstance();
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
