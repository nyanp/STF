#ifndef stf_core_strategy_control_Combining_h
#define stf_core_strategy_control_Combining_h
#include <assert.h>
#include "../../devicedriver/IOPort.h"
#include "../StrategyBase.h"
#include "../../../util/Ostream.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {

//任意の物理量を単純加算で合成する制御ブロック群．なんかキモい．

template<class T>
class Combining_2 : public devicedriver::InputPorts< TYPELIST_2(T, T) >, 
		public devicedriver::OutputPorts < TYPELIST_1(T) > ,
		public StrategyBase
{
public:
	Combining_2(int instance_id) : StrategyBase(instance_id, "Combining"){}
	Combining_2(int instance_id,
		devicedriver::OutputPort<T>* source_1, 
		devicedriver::OutputPort<T>* source_2,
		devicedriver::InputPort<T>* torque_out) : StrategyBase(instance_id, "Combining_2") {
			this->connectSource<0>(source_1);
			this->connectSource<1>(source_2);
			torque_out->connectSource_(this);
	}
	~Combining_2(){}
	virtual void do_compute(const datatype::Time& t){
		if(t > this->last_update_){//既に別のブロック経由で更新済みなら再計算しない
			util::cout << "compute: combining-2" << util::endl;
			this->value_b_.reset();
			this->value_b_ += this->source<0,T>().getValueInBodyFrame(t);
			this->value_b_ += this->source<1,T>().getValueInBodyFrame(t);
			this->last_update_ = t;
		}
	}
private:

};

template<class T>
class Combining_3 : public devicedriver::InputPorts< TYPELIST_3(T, T, T) >, 
		public devicedriver::OutputPorts < TYPELIST_1(T) > ,
		public StrategyBase
{
public:
	Combining_3(int instance_id) : StrategyBase(instance_id, "Combining"){}
	Combining_3(int instance_id,
		devicedriver::OutputPort<T>* source_1, 
		devicedriver::OutputPort<T>* source_2,
		devicedriver::OutputPort<T>* source_3,
		devicedriver::InputPort<T>* torque_out) : StrategyBase(instance_id, "Combining_3") {
			this->connectSource<0>(source_1);
			this->connectSource<1>(source_2);
			this->connectSource<2>(source_3);
			torque_out->connectSource_(this);
	}
	~Combining_3(){}
	virtual void do_compute(const datatype::Time& t){
		if(t > this->last_update_){//既に別のブロック経由で更新済みなら再計算しない
			this->value_b_.reset();
			this->value_b_ += this->source<0,T>().getValueInBodyFrame(t);
			this->value_b_ += this->source<1,T>().getValueInBodyFrame(t);
			this->value_b_ += this->source<2,T>().getValueInBodyFrame(t);
			this->last_update_ = t;
		}
	}
private:

};

template<class T>
class Combining_4 : public devicedriver::InputPorts< TYPELIST_4(T, T, T, T) >, 
		public devicedriver::OutputPorts < TYPELIST_1(T) > ,
		public StrategyBase
{
public:
	Combining_4(int instance_id) : StrategyBase(instance_id, "Combining"){}
	Combining_4(int instance_id,
		devicedriver::OutputPort<T>* source_1, 
		devicedriver::OutputPort<T>* source_2,
		devicedriver::OutputPort<T>* source_3,
		devicedriver::OutputPort<T>* source_4,
		devicedriver::InputPort<T>* torque_out) : StrategyBase(instance_id, "Combining_4") {
			this->connectSource<0>(source_1);
			this->connectSource<1>(source_2);
			this->connectSource<2>(source_3);
			this->connectSource<3>(source_4);
			torque_out->connectSource_(this);
	}
	~Combining_4(){}
	virtual void do_compute(const datatype::Time& t){
		if(t > this->last_update_){//既に別のブロック経由で更新済みなら再計算しない
			this->value_b_.reset();
			this->value_b_ += this->source<0,T>().getValueInBodyFrame(t);
			this->value_b_ += this->source<1,T>().getValueInBodyFrame(t);
			this->value_b_ += this->source<2,T>().getValueInBodyFrame(t);
			this->value_b_ += this->source<3,T>().getValueInBodyFrame(t);
			this->last_update_ = t;
		}
	}
private:
};

template<class T>
class Combining_5 : public devicedriver::InputPorts< TYPELIST_5(T, T, T, T, T) >, 
		public devicedriver::OutputPorts < TYPELIST_1(T) > ,
		public StrategyBase
{
public:
	Combining_5(int instance_id) : StrategyBase(instance_id, "Combining"){}
	Combining_5(int instance_id,
		devicedriver::OutputPort<T>* source_1, 
		devicedriver::OutputPort<T>* source_2,
		devicedriver::OutputPort<T>* source_3,
		devicedriver::OutputPort<T>* source_4,
		devicedriver::OutputPort<T>* source_5,
		devicedriver::InputPort<T>* torque_out) : StrategyBase(instance_id, "Combining_5") {
			this->connectSource<0>(source_1);
			this->connectSource<1>(source_2);
			this->connectSource<2>(source_3);
			this->connectSource<3>(source_4);
			this->connectSource<4>(source_5);
			torque_out->connectSource_(this);
	}
	~Combining_5(){}
	virtual void do_compute(const datatype::Time& t){
		if(t > this->last_update_){//既に別のブロック経由で更新済みなら再計算しない
			this->value_b_.reset();
			this->value_b_ += this->source<0,T>().getValueInBodyFrame(t);
			this->value_b_ += this->source<1,T>().getValueInBodyFrame(t);
			this->value_b_ += this->source<2,T>().getValueInBodyFrame(t);
			this->value_b_ += this->source<3,T>().getValueInBodyFrame(t);
			this->value_b_ += this->source<4,T>().getValueInBodyFrame(t);
			this->last_update_ = t;
		}
	}
private:
};

template<class T>
class Combining_6 : public devicedriver::InputPorts< TYPELIST_6(T, T, T, T, T, T) >, 
		public devicedriver::OutputPorts < TYPELIST_1(T) > ,
		public StrategyBase
{
public:
	Combining_6(int instance_id) : StrategyBase(instance_id, "Combining"){}
	Combining_6(int instance_id,
		devicedriver::OutputPort<T>* source_1, 
		devicedriver::OutputPort<T>* source_2,
		devicedriver::OutputPort<T>* source_3,
		devicedriver::OutputPort<T>* source_4,
		devicedriver::OutputPort<T>* source_5,
		devicedriver::OutputPort<T>* source_6,
		devicedriver::InputPort<T>* torque_out) : StrategyBase(instance_id, "Combining_6") {
			this->connectSource<0>(source_1);
			this->connectSource<1>(source_2);
			this->connectSource<2>(source_3);
			this->connectSource<3>(source_4);
			this->connectSource<4>(source_5);
			this->connectSource<5>(source_6);
			torque_out->connectSource_(this);
	}
	~Combining_6(){}
	virtual void do_compute(const datatype::Time& t){
		if(t > this->last_update_){//既に別のブロック経由で更新済みなら再計算しない
			this->value_b_.reset();
			this->value_b_ += this->source<0,T>().getValueInBodyFrame(t);
			this->value_b_ += this->source<1,T>().getValueInBodyFrame(t);
			this->value_b_ += this->source<2,T>().getValueInBodyFrame(t);
			this->value_b_ += this->source<3,T>().getValueInBodyFrame(t);
			this->value_b_ += this->source<4,T>().getValueInBodyFrame(t);
			this->value_b_ += this->source<5,T>().getValueInBodyFrame(t);
			this->last_update_ = t;
		}
	}
private:
};



} /* End of namespace stf::core::mode::strategy::control */
} /* End of namespace stf::core::mode::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_mode_storategy_control_Combining_h
