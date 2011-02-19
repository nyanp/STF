/**
 * @file   NJControllers.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_control_NJControlBlock_h
#define stf_core_strategy_control_NJControlBlock_h
#include "../../core/strategy/control/ControlBlock.h"
#include "../../core/devicedriver/IOPort.h"
#include "../../datatype/Quaternion.h"
#include "../../datatype/Time.h"
#include "../../datatype/TypeConverter.h"
#include "../../datatype/Magnetic.h"
#include "../../datatype/StaticVector.h"
#include "../../core/devicedriver/clock/IAbsoluteTimeClock.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {
namespace nj {
// Nano-JASMINE固有の制御ブロックを記述する

// Quaternion Avevraging Block
// 2軸のQuaternionを1個のQuaternionに変換


//3つのトルクを単純加算で合成する制御ブロック．
class QuaternionAveraging : public devicedriver::InputPorts< TYPELIST_2(datatype::Quaternion, datatype::Quaternion) >, 
		public devicedriver::OutputPorts < TYPELIST_1(datatype::Quaternion) > ,
		public StrategyBase
{
public:
	QuaternionAveraging(int instance_id): StrategyBase(instance_id, "Quaternion Averaging"){}
	QuaternionAveraging(int instance_id,
		devicedriver::OutputPort<datatype::Quaternion>* stt_1, 
		devicedriver::OutputPort<datatype::Quaternion>* stt_2,
		devicedriver::InputPort<datatype::Quaternion>* q_out = 0) : StrategyBase(instance_id, "Quaternion Averaging")
	{
			this->connectSource<0>(stt_1);
			this->connectSource<1>(stt_2);
			if(q_out != 0) q_out->connectSource_(this);
	}
	~QuaternionAveraging(){}
	virtual void do_compute(const datatype::Time& t);
protected:

};

//StarEKF 星像から角速度を推定するEKF.
class StarImageEKF : public devicedriver::InputPorts< TYPELIST_2(datatype::StaticVector<3>,datatype::StaticVector<3>) >,
		public devicedriver::OutputPorts < TYPELIST_1(datatype::StaticVector<3>) > ,
		public StrategyBase
{
public:
	StarImageEKF(int instance_id) : StrategyBase(instance_id, "StarImageEKF") {}
	virtual void do_compute(const datatype::Time& t);
private:
};


//中期姿勢安定度要求に応じて目標Quaternionを伝搬する制御ブロック．
class MidRangeSpinController : public devicedriver::InputPorts< TYPELIST_1(datatype::Quaternion) >,
		public devicedriver::OutputPorts < TYPELIST_1(datatype::Quaternion) > ,
		public StrategyBase
{
public:
	MidRangeSpinController(int instance_id) : StrategyBase(instance_id, "MidSpinController") {}
	MidRangeSpinController(int instance_id, devicedriver::OutputPort<datatype::Quaternion>* q_source) : StrategyBase(instance_id, "MidSpinController"){
		this->connectSource<0>(q_source);
	}
	virtual void do_compute(const datatype::Time& t);
private:
};

//長期姿勢安定度要求に応じて目標スピン軸を伝搬する制御ブロック．
class LongRangeSpinController : 
		public devicedriver::OutputPorts < TYPELIST_1(datatype::Quaternion) > ,
		public StrategyBase
{
public:
	LongRangeSpinController(int instance_id) : StrategyBase(instance_id, "MidSpinController") {}
	virtual void do_compute(const datatype::Time& t);
private:
};

//FOG推定モードにおける目標Quaternionを制御するブロック．
//衛星6面のうち1面を太陽方向を指向させる
class QuaternionForRMMEstimation : public devicedriver::InputPorts< TYPELIST_1(datatype::PositionInfo) >,
		public devicedriver::OutputPorts < TYPELIST_1(datatype::Quaternion) > ,
		public StrategyBase
{
public:
	QuaternionForRMMEstimation(int instance_id, devicedriver::clock::IAbsoluteTimeClock* clock, datatype::Time timespan)
		: StrategyBase(instance_id, "QuaternionForFOGEstimation"), index_(0), clock_(clock), timespan_(timespan){}
	virtual void do_compute(const datatype::Time& t);
private:
	devicedriver::clock::IAbsoluteTimeClock* clock_;
	datatype::Time before_;
	datatype::Time timespan_;
	int index_;//現在の太陽指向面
};

class MCConstantOutput : 
	public devicedriver::OutputPorts < TYPELIST_1(datatype::MagneticMoment) > , public StrategyBase
{
public:
	MCConstantOutput(int instance_id, devicedriver::clock::IAbsoluteTimeClock* clock, datatype::Time timespan)
		: StrategyBase(instance_id, "MCConstantOutput"), index_(0), axis_(0), clock_(clock), timespan_(timespan){}
	virtual void do_compute(const datatype::Time& t);
private:
	devicedriver::clock::IAbsoluteTimeClock* clock_;
	datatype::Time before_;
	datatype::Time timespan_;
	int index_;
	int axis_;
};

class RWConstantOutput : 
	public devicedriver::OutputPorts < TYPELIST_4(datatype::StaticVector<3>,datatype::StaticVector<3>,datatype::StaticVector<3>,datatype::StaticVector<3>) > , public StrategyBase
{
public:
	RWConstantOutput(int instance_id, devicedriver::clock::IAbsoluteTimeClock* clock, datatype::Time timespan)
		: StrategyBase(instance_id, "RWConstantOutput"), index_(0), axis_(0), clock_(clock), timespan_(timespan){}
	virtual void do_compute(const datatype::Time& t);
private:
	devicedriver::clock::IAbsoluteTimeClock* clock_;
	datatype::Time before_;
	datatype::Time timespan_;
	int index_;
	int axis_;
};
} /* End of namespace stf::core::mode::strategy::control::nj */
} /* End of namespace stf::core::mode::strategy::control */
} /* End of namespace stf::core::mode::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_mode_storategy_control_NJControlBlock_h
