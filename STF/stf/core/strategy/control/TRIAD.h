#ifndef stf_core_strategy_control_TRIAD_h
#define stf_core_strategy_control_TRIAD_h

#include "../StrategyBase.h"
#include "../../../datatype/StaticVector.h"
#include "../../../datatype/Quaternion.h"
#include "../../../datatype/OrbitInfo.h"
#include "../../../datatype/DateTime.h"
#include "../../../datatype/Magnetic.h"
#include "../../devicedriver/IOPort.h"
#include "../../devicedriver/clock/IAbsoluteTimeClock.h"

namespace stf {
namespace datatype {
class Time;
}
namespace core {
namespace strategy {
namespace control {


//Body座標と慣性座標のベクトルを2個ずつ入力し，quaternionを出力する汎用のTRIADブロック．
class TRIAD
	: virtual public StrategyBase, 
	public devicedriver::InputPorts< TYPELIST_4( datatype::StaticVector<2>, datatype::StaticVector<2>, datatype::StaticVector<2>, datatype::StaticVector<2> ) >,
	public devicedriver::OutputPorts< TYPELIST_1( datatype::Quaternion ) >
{
public:
	TRIAD(int instance_id) : StrategyBase(instance_id, "TRIAD"){}
	TRIAD(int instance_id, 
		devicedriver::OutputPort<datatype::StaticVector<2>>* body_vector1,
		devicedriver::OutputPort<datatype::StaticVector<2>>* inertial_vector1,
		devicedriver::OutputPort<datatype::StaticVector<2>>* body_vector2,
		devicedriver::OutputPort<datatype::StaticVector<2>>* inertial_vector2,
		devicedriver::InputPort<datatype::Quaternion>* q_out = 0
		);
	~TRIAD(){}
	virtual void do_compute(const datatype::Time& t);
protected:
};

//軌道情報と地球，太陽方向ベクトルからquaternionを出力するTRIADブロック．
class SunEarthTRIAD
	: virtual public StrategyBase, 
	public devicedriver::InputPorts< TYPELIST_4( datatype::StaticVector<2>, datatype::StaticVector<2>, datatype::PositionInfo, datatype::DateTime ) >,
	public devicedriver::OutputPorts< TYPELIST_1( datatype::Quaternion ) >
{
public:
	SunEarthTRIAD(int instance_id) : StrategyBase(instance_id, "SunEarthTRIAD"){}
	SunEarthTRIAD(int instance_id, 
		devicedriver::OutputPort<datatype::StaticVector<2>>* sunvector_source,
		devicedriver::OutputPort<datatype::StaticVector<2>>* earthvector_source,
		devicedriver::OutputPort<datatype::PositionInfo>* position_source,
		devicedriver::OutputPort<datatype::DateTime>* time_source,
		devicedriver::InputPort<datatype::Quaternion>* q_out = 0
		);
	~SunEarthTRIAD(){}
	virtual void do_compute(const datatype::Time& t);
protected:
};

//軌道情報と磁場，太陽方向ベクトルからquaternionを出力するTRIADブロック．
class SunMagTRIAD
	: virtual public StrategyBase, 
	public devicedriver::InputPorts< TYPELIST_4( datatype::StaticVector<2>, datatype::MagneticField, datatype::PositionInfo, datatype::DateTime ) >,
	public devicedriver::OutputPorts< TYPELIST_1( datatype::Quaternion ) >
{
public:
	SunMagTRIAD(int instance_id) : StrategyBase(instance_id, "SunMagTRIAD"){}
	SunMagTRIAD(int instance_id, 
		devicedriver::OutputPort<datatype::StaticVector<2>>* sunvector_source,
		devicedriver::OutputPort<datatype::MagneticField>* mag_source,
		devicedriver::OutputPort<datatype::PositionInfo>* position_source,
		devicedriver::OutputPort<datatype::DateTime>* time_source,
		devicedriver::InputPort<datatype::Quaternion>* q_out = 0
		);
	~SunMagTRIAD(){}
	virtual void do_compute(const datatype::Time& t);
protected:
};

//軌道情報と磁場，太陽方向ベクトルからquaternionを出力するTRIADブロック．
class SunMagTRIAD2
	: virtual public StrategyBase, 
	public devicedriver::InputPorts< TYPELIST_3( datatype::StaticVector<2>, datatype::MagneticField, datatype::PositionInfo ) >,
	public devicedriver::OutputPorts< TYPELIST_1( datatype::Quaternion ) >
{
public:
	SunMagTRIAD2(int instance_id) : StrategyBase(instance_id, "SunMagTRIAD"){}
	SunMagTRIAD2(int instance_id, 
		devicedriver::clock::IAbsoluteTimeClock* clock,
		devicedriver::OutputPort<datatype::StaticVector<2>>* sunvector_source = 0,
		devicedriver::OutputPort<datatype::MagneticField>* mag_source = 0,
		devicedriver::OutputPort<datatype::PositionInfo>* position_source = 0,
		devicedriver::InputPort<datatype::Quaternion>* q_out = 0
		);
	~SunMagTRIAD2(){}
	virtual void do_compute(const datatype::Time& t);
protected:
	devicedriver::clock::IAbsoluteTimeClock* clock_;
};

} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_strategy_control_input_TRIAD_h
