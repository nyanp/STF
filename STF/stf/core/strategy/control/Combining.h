/**
 * @file   Combining.h
 * @brief  任意の物理量を単純加算で合成する制御ブロック群．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 * @todo   TypeListで纏められるか検討
 */
#ifndef stf_core_strategy_control_Combining_h
#define stf_core_strategy_control_Combining_h
#include "../../../util/stfassert.h"
#include "../../devicedriver/IOPort.h"
#include "../StrategyBase.h"
#include "../../../util/Trace.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {

//! 2つの物理量を加算して1つに纏める制御ブロック．
/*! 
	@tparam T 合成する物理量．reset()および operator += が実装されている必要がある
*/
template<class T>
class Combining_2 : public devicedriver::InputPorts< TYPELIST_2(T, T) >, 
		public devicedriver::OutputPorts < TYPELIST_1(T) > ,
		public StrategyBase
{
public:
	Combining_2(int instance_id) : StrategyBase(instance_id, "Combining_2"){}

	Combining_2(int instance_id,
		devicedriver::OutputPort<T>* source_1, 
		devicedriver::OutputPort<T>* source_2,
		devicedriver::InputPort<T>* torque_out) : StrategyBase(instance_id, "Combining_2") 
	{
		this->connect_source<0>(source_1);
		this->connect_source<1>(source_2);
		torque_out->connect_source_(this);
	}

	~Combining_2(){}

	//! 制御アルゴリズム本体．
	/*!
		入力ポートから値を伝搬し，単純加算で出力を生成する．
		既に更新済みであれば何もしない．
	*/
	virtual void do_compute(const datatype::Time& t){
		if(t > this->last_update_){//既に別のブロック経由で更新済みなら再計算しない
			util::Trace trace(util::Trace::kControlBlock, name_);

			this->value_.reset();
			if(this->input_isconnected<0>()) this->value_ += this->source<0, T>().get_value(t);
			if(this->input_isconnected<1>()) this->value_ += this->source<1, T>().get_value(t);

			trace.debug(value_);

			this->last_update_ = t;
		}
	}
};


//! 3つの物理量を加算して1つに纏める制御ブロック．
/*! 
	@tparam T 合成する物理量．reset()および operator += が実装されている必要がある
*/
template<class T>
class Combining_3 : public devicedriver::InputPorts< TYPELIST_3(T, T, T) >, 
		public devicedriver::OutputPorts < TYPELIST_1(T) > ,
		public StrategyBase
{
public:
	Combining_3(int instance_id) : StrategyBase(instance_id, "Combining_3"){}

	Combining_3(int instance_id,
		devicedriver::OutputPort<T>* source_1, 
		devicedriver::OutputPort<T>* source_2,
		devicedriver::OutputPort<T>* source_3,
		devicedriver::InputPort<T>* torque_out) : StrategyBase(instance_id, "Combining_3") 
	{
		this->connect_source<0>(source_1);
		this->connect_source<1>(source_2);
		this->connect_source<2>(source_3);
		torque_out->connect_source_(this);
	}

	~Combining_3(){}

	//! 制御アルゴリズム本体．
	/*!
		入力ポートから値を伝搬し，単純加算で出力を生成する．
		既に更新済みであれば何もしない．
	*/
	virtual void do_compute(const datatype::Time& t){
		if(t > this->last_update_){//既に別のブロック経由で更新済みなら再計算しない
			util::Trace trace(util::Trace::kControlBlock, name_);

			this->value_.reset();
			if(this->input_isconnected<0>()) this->value_ += this->source<0, T>().get_value(t);
			if(this->input_isconnected<1>()) this->value_ += this->source<1, T>().get_value(t);
			if(this->input_isconnected<2>()) this->value_ += this->source<2, T>().get_value(t);

			trace.debug(value_);

			this->last_update_ = t;
		}
	}
};


//! 4つの物理量を加算して1つに纏める制御ブロック．
/*! 
	@tparam T 合成する物理量．reset()および operator += が実装されている必要がある
*/
template<class T>
class Combining_4 : public devicedriver::InputPorts< TYPELIST_4(T, T, T, T) >, 
		public devicedriver::OutputPorts < TYPELIST_1(T) > ,
		public StrategyBase
{
public:
	Combining_4(int instance_id) : StrategyBase(instance_id, "Combining_4"){}

	Combining_4(int instance_id,
		devicedriver::OutputPort<T>* source_1, 
		devicedriver::OutputPort<T>* source_2,
		devicedriver::OutputPort<T>* source_3,
		devicedriver::OutputPort<T>* source_4,
		devicedriver::InputPort<T>* torque_out) : StrategyBase(instance_id, "Combining_4") 
	{
		this->connect_source<0>(source_1);
		this->connect_source<1>(source_2);
		this->connect_source<2>(source_3);
		this->connect_source<3>(source_4);
		torque_out->connect_source_(this);
	}

	~Combining_4(){}

	//! 制御アルゴリズム本体．
	/*!
		入力ポートから値を伝搬し，単純加算で出力を生成する．
		既に更新済みであれば何もしない．
	*/
	virtual void do_compute(const datatype::Time& t){
		if(t > this->last_update_){//既に別のブロック経由で更新済みなら再計算しない
			util::Trace trace(util::Trace::kControlBlock, name_);

			this->value_.reset();
			if(this->input_isconnected<0>()) this->value_ += this->source<0, T>().get_value(t);
			if(this->input_isconnected<1>()) this->value_ += this->source<1, T>().get_value(t);
			if(this->input_isconnected<2>()) this->value_ += this->source<2, T>().get_value(t);
			if(this->input_isconnected<3>()) this->value_ += this->source<3, T>().get_value(t);

			trace.debug(value_);

			this->last_update_ = t;
		}
	}
};


//! 5つの物理量を加算して1つに纏める制御ブロック．
/*! 
	@tparam T 合成する物理量．reset()および operator += が実装されている必要がある
*/
template<class T>
class Combining_5 : public devicedriver::InputPorts< TYPELIST_5(T, T, T, T, T) >, 
		public devicedriver::OutputPorts < TYPELIST_1(T) > ,
		public StrategyBase
{
public:
	Combining_5(int instance_id) : StrategyBase(instance_id, "Combining_5"){}

	Combining_5(int instance_id,
		devicedriver::OutputPort<T>* source_1, 
		devicedriver::OutputPort<T>* source_2,
		devicedriver::OutputPort<T>* source_3,
		devicedriver::OutputPort<T>* source_4,
		devicedriver::OutputPort<T>* source_5,
		devicedriver::InputPort<T>* torque_out) : StrategyBase(instance_id, "Combining_5") 
	{
		this->connect_source<0>(source_1);
		this->connect_source<1>(source_2);
		this->connect_source<2>(source_3);
		this->connect_source<3>(source_4);
		this->connect_source<4>(source_5);
		torque_out->connect_source_(this);
	}

	~Combining_5(){}

	//! 制御アルゴリズム本体．
	/*!
		入力ポートから値を伝搬し，単純加算で出力を生成する．
		既に更新済みであれば何もしない．
	*/
	virtual void do_compute(const datatype::Time& t){
		if(t > this->last_update_){//既に別のブロック経由で更新済みなら再計算しない
			util::Trace trace(util::Trace::kControlBlock, name_);

			this->value_.reset();
			if(this->input_isconnected<0>()) this->value_ += this->source<0, T>().get_value(t);
			if(this->input_isconnected<1>()) this->value_ += this->source<1, T>().get_value(t);
			if(this->input_isconnected<2>()) this->value_ += this->source<2, T>().get_value(t);
			if(this->input_isconnected<3>()) this->value_ += this->source<3, T>().get_value(t);
			if(this->input_isconnected<4>()) this->value_ += this->source<4, T>().get_value(t);

			trace.debug(value_);

			this->last_update_ = t;
		}
	}
};


//! 6つの物理量を加算して1つに纏める制御ブロック．
/*! 
	@tparam T 合成する物理量．reset()および operator += が実装されている必要がある
*/
template<class T>
class Combining_6 : public devicedriver::InputPorts< TYPELIST_6(T, T, T, T, T, T) >, 
		public devicedriver::OutputPorts < TYPELIST_1(T) > ,
		public StrategyBase
{
public:
	Combining_6(int instance_id) : StrategyBase(instance_id, "Combining_6"){}

	Combining_6(int instance_id,
		devicedriver::OutputPort<T>* source_1, 
		devicedriver::OutputPort<T>* source_2,
		devicedriver::OutputPort<T>* source_3,
		devicedriver::OutputPort<T>* source_4,
		devicedriver::OutputPort<T>* source_5,
		devicedriver::OutputPort<T>* source_6,
		devicedriver::InputPort<T>* torque_out) : StrategyBase(instance_id, "Combining_6") 
	{
		this->connect_source<0>(source_1);
		this->connect_source<1>(source_2);
		this->connect_source<2>(source_3);
		this->connect_source<3>(source_4);
		this->connect_source<4>(source_5);
		this->connect_source<5>(source_6);
		torque_out->connect_source_(this);
	}

	~Combining_6(){}

	//! 制御アルゴリズム本体．
	/*!
		入力ポートから値を伝搬し，単純加算で出力を生成する．
		既に更新済みであれば何もしない．
	*/
	virtual void do_compute(const datatype::Time& t){
		if(t > this->last_update_){//既に別のブロック経由で更新済みなら再計算しない
			util::Trace trace(util::Trace::kControlBlock, name_);

			this->value_.reset();
			if(this->input_isconnected<0>()) this->value_ += this->source<0, T>().get_value(t);
			if(this->input_isconnected<1>()) this->value_ += this->source<1, T>().get_value(t);
			if(this->input_isconnected<2>()) this->value_ += this->source<2, T>().get_value(t);
			if(this->input_isconnected<3>()) this->value_ += this->source<3, T>().get_value(t);
			if(this->input_isconnected<4>()) this->value_ += this->source<4, T>().get_value(t);
			if(this->input_isconnected<5>()) this->value_ += this->source<5, T>().get_value(t);

			trace.debug(value_);

			this->last_update_ = t;
		}
	}
};

} /* End of namespace stf::core::mode::strategy::control */
} /* End of namespace stf::core::mode::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_mode_storategy_control_Combining_h
