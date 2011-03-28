/**
 * @file   Simulator.cpp
 * @brief  ソフトウェアシミュレータ環境クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "Simulator.h"

#include <fstream>
#include <iostream>
#include <vector>

#include "../../datatype/EulerAngle.h"
#include "../../datatype/TypeConverter.h"
#include "../../util/math/Rand.h"
#include "../../util/math/RungeKutta.h"
#include "../../datatype/OrbitCalc.h"
#include "../devicedriver/AOCSActuator.h"
#include "../devicedriver/AOCSSensor.h"
#include "../manager/ManagerBase.h"
#include "../devicedriver/gyro/GyroBase.h"
#include "../devicedriver/earthsensor/EarthSensorBase.h"
#include "../devicedriver/gps/GPSBase.h"
#include "../devicedriver/magnetometer/TAMBase.h"
#include "../devicedriver/mtq/MTQBase.h"
#include "../devicedriver/rw/RWBase.h"
#include "../devicedriver/stt/STTBase.h"
#include "../devicedriver/sunsensor/SunSensorBase.h"
#include "Orbit.h"
#include "torquesource/NoiseBase.h"
#include "../../GlobalObject.h"

namespace stf {
namespace core {
namespace environment {


class SimulatorImpl {
public:
	typedef core::devicedriver::AOCSSensor<datatype::StaticVector<3>, datatype::StaticVector<3>, Simulator> MultiGyro;
	typedef core::devicedriver::AOCSSensor<datatype::StaticVector<3>, datatype::Scalar, Simulator> Gyro;
	typedef core::devicedriver::AOCSSensor<datatype::Quaternion, datatype::Quaternion, Simulator> STT;
	typedef core::devicedriver::AOCSSensor<datatype::StaticVector<2>, datatype::StaticVector<2>, Simulator> Vectorsensor;
	typedef core::devicedriver::AOCSSensor<datatype::MagneticField, datatype::MagneticField, Simulator> Magnetometer;
	typedef core::devicedriver::clock::ITimeClock Clock;
	typedef core::devicedriver::AOCSActuator<datatype::StaticVector<3>, datatype::Scalar, Simulator> TorqueSource;
	typedef core::devicedriver::AOCSActuator<datatype::MagneticMoment, datatype::Scalar, Simulator> MagneticSource;

    SimulatorImpl();
    ~SimulatorImpl();

	void step_() { this->true_time_ += this->timestep_; this->orbit_.addTime(this->timestep_); }
	void init(Global<Simulator>* global, double stepTimeInSecond, double maxTimeInSecond, const datatype::OrbitInfo& orbit, std::ofstream *ostream);

    datatype::StaticVector<3> getAngularVelocity(const MultiGyro& component) const ;
    datatype::Scalar getAngularVelocity(const Gyro& component) const ;
    datatype::Quaternion getQuaternion(const STT& component) const ;
	datatype::StaticVector<2> getSunDirection(const Vectorsensor& component) const ;
	datatype::StaticVector<2> getEarthDirection(const Vectorsensor& component) const ;
	datatype::MagneticField getMagneticField(const Magnetometer& component) const;
	datatype::Time get_time(const Clock& component) const ;

	const datatype::Time& getTrueTime() const { return this->true_time_; }
	const datatype::Quaternion& getTrueQuaternion() const { return this->true_quaternion_; }
	const datatype::StaticVector<3>& getTrueAngular() const { return this->true_angular_velocity_; }
	const datatype::PositionInfo getTrueSatellitePosition() const;

    void start();
    void runOneCycle();
	void attachTorqueSource(TorqueSource* source);
	void attachMagneticSource(MagneticSource* source);
	void attachNoiseSource(torquesource::NoiseBase* source);

private:
	Orbit orbit_;
	datatype::StaticVector<3> true_angular_velocity_;
    datatype::Quaternion true_quaternion_;
	datatype::StaticVector<3> true_torque_;
    datatype::Time true_time_;
    datatype::Time timestep_;
	datatype::StaticVector<3> noise_torque_;
	std::vector< TorqueSource* > torque_sources_;
	std::vector< torquesource::NoiseBase* > noise_sources_;
	std::vector< MagneticSource* > mag_sources_;

    datatype::StaticMatrix<4, 4> Omega_;
    Global<Simulator> *global_;
    datatype::Time max_time_;
    std::ofstream *ofstream_;

};

void SimulatorImpl::init(Global<Simulator>* global, double stepTimeInSecond, double maxTimeInSecond, const datatype::OrbitInfo& orbit,  std::ofstream *ostream)
{
	util::math::WhiteNoise_init(0);
    this->global_ = global;
    this->timestep_.add_milliseconds(stepTimeInSecond * 1000);
    this->max_time_.add_milliseconds(maxTimeInSecond * 1000);
	this->orbit_.set_orbitElement(orbit);
    if(ostream != 0)
        this->ofstream_ = ostream;
}

SimulatorImpl::~SimulatorImpl()
{
	this->ofstream_->close();
}

datatype::MagneticField SimulatorImpl::getMagneticField(const Magnetometer& component) const
{
	return component.get_transfomer().inverse() * this->orbit_.getMagneticField();
}

datatype::StaticVector<3> SimulatorImpl::getAngularVelocity(const MultiGyro& component) const 
{
	datatype::StaticVector<3> v  = component.get_transfomer().inverse() * this->true_angular_velocity_;
	return v;
}

datatype::Scalar SimulatorImpl::getAngularVelocity(const Gyro& component) const 
{
	return datatype::Scalar((component.get_transfomer().inverse() * this->true_angular_velocity_)[2]);
}

datatype::Quaternion SimulatorImpl::getQuaternion(const STT& component) const 
{
	datatype::Quaternion q = datatype::TypeConverter::toQuaternion(component.get_transfomer()).conjugate();
	return  q * this->true_quaternion_;
}

datatype::StaticVector<2> SimulatorImpl::getSunDirection(const Vectorsensor& component) const 
{
	return datatype::TypeConverter::toPolar(component.get_transfomer().inverse() * datatype::OrbitCalc::getSunDirectionInBodyFrame(this->orbit_.get_time(), this->true_quaternion_));
}

datatype::StaticVector<2> SimulatorImpl::getEarthDirection(const Vectorsensor& component) const 
{
	return datatype::TypeConverter::toPolar(component.get_transfomer().inverse() * datatype::OrbitCalc::getEarthDirectionInBodyFrame(this->orbit_.getSatellitePosition(), this->true_quaternion_));
}

const datatype::PositionInfo SimulatorImpl::getTrueSatellitePosition() const
{
	return this->orbit_.getSatellitePosition();
}

datatype::Time SimulatorImpl::get_time(const Clock& component) const 
{
    return this->true_time_;
}

void SimulatorImpl::start()
{
    std::cout << "Simulator Start" << std::endl;
    while(this->true_time_ < this->max_time_){
        this->runOneCycle();
    }
}

void SimulatorImpl::runOneCycle()
{
	if(this->ofstream_ != 0){
		//Logging
		(*this->ofstream_) 
			<< this->true_time_.total_seconds() << ", "
			<< this->true_quaternion_[0] << ", "
			<< this->true_quaternion_[1] << ", "
			<< this->true_quaternion_[2] << ", "
			<< this->true_quaternion_[3] << ", "
			<< this->true_angular_velocity_[0] << ", "
			<< this->true_angular_velocity_[1] << ", "
			<< this->true_angular_velocity_[2] << ", "
			<< this->true_torque_[0] << ", "
			<< this->true_torque_[1] << ", "
			<< this->true_torque_[2] << ", "
			<< this->noise_torque_[0] << ", "
			<< this->noise_torque_[1] << ", "
			<< this->noise_torque_[2] << "\n";
            /*<< this->global_->fog1->bias_rate_ << ", "
            << this->global_->fog2->bias_rate_ << ", "
            << this->global_->fog3->bias_rate_ << ", "
            << this->global_->ekf->q_[0] << ", "
            << this->global_->ekf->q_[1] << ", "
            << this->global_->ekf->q_[2] << ", "
            << this->global_->ekf->q_[3] << ", "
            << this->global_->ekf->bref_[0] << ", "
            << this->global_->ekf->bref_[1] << ", "
            << this->global_->ekf->bref_[2] << "\n";*/
	}

	datatype::List<core::manager::ManagerBase>::iterator it_m = global_->get_function_manager()->begin(), end_m = global_->get_function_manager()->end();
	while( it_m !=  end_m ){
		(*it_m).run();
		++it_m;
	}

    this->true_torque_.reset();//トルクを一旦リセットし，外部ソースから計算しなおす
    std::vector<TorqueSource*>::iterator it_t = this->torque_sources_.begin(), end_t = this->torque_sources_.end();
    while( it_t != end_t ){
		for(int i = 0; i < 3; i++){
			this->true_torque_[i] += (*it_t)->get_torque().value() * (*it_t)->get_transfomer()[i][2];
		}
        ++it_t;
    }

	this->noise_torque_.reset();
	std::vector< torquesource::NoiseBase* >::iterator it_n = this->noise_sources_.begin(), end_n = this->noise_sources_.end();
    while( it_n != end_n ){
		this->noise_torque_ += (*it_n)->get_torque_bodyframe();
        ++it_n;
    }

    //次ステップの計算
    double acc[3];//角加速度
	acc[0] = this->true_torque_[0] + this->noise_torque_[0];
    acc[1] = this->true_torque_[1] + this->noise_torque_[1];
    acc[2] = this->true_torque_[2] + this->noise_torque_[2];//TBD:衛星の質量特性で割る必要

    double omega[3];//角速度ωn+1＝ωn＋at
	omega[0] = this->true_angular_velocity_[0] + acc[0] * this->timestep_.total_seconds();
    omega[1] = this->true_angular_velocity_[1] + acc[1] * this->timestep_.total_seconds();
    omega[2] = this->true_angular_velocity_[2] + acc[2] * this->timestep_.total_seconds();

    Omega_[0][1] = -omega[0];
    Omega_[0][2] = -omega[1];
    Omega_[0][3] = -omega[2];
    Omega_[1][2] =  omega[2];
    Omega_[1][3] = -omega[1];
    Omega_[2][3] =  omega[0];
    for(int i = 0; i < 4; i++)
      for(int j = 0; j < 4; j++)
        if(i > j) Omega_[i][j] = -Omega_[j][i];

    this->true_quaternion_ += util::math::RungeKutta::slope(true_quaternion_, 0.5 * Omega_, timestep_.total_seconds());
    for(int i = 0; i < 3; i++) this->true_angular_velocity_[i] = omega[i];
	this->step_();
}

void SimulatorImpl::attachTorqueSource(TorqueSource* source)
{
    this->torque_sources_.push_back(source);
}

void SimulatorImpl::attachNoiseSource(torquesource::NoiseBase* source)
{
	this->noise_sources_.push_back(source);
}

void SimulatorImpl::attachMagneticSource(MagneticSource* source)
{
	this->mag_sources_.push_back(source);
}

SimulatorImpl::SimulatorImpl()
: orbit_()
{
	util::math::WhiteNoise_init(0);
}

Simulator* Simulator::singleton_ = new Simulator();

Simulator& Simulator::get_instance(){
	return *Simulator::singleton_;
}

void Simulator::init(Global<Simulator>* global, double stepTimeInSecond, double maxTimeInSecond, const datatype::OrbitInfo& orbit,  std::ofstream *ostream)
{
	this->simulatorimpl_->init(global, stepTimeInSecond, maxTimeInSecond, orbit, ostream);
}

Simulator::~Simulator()
{
	
}

datatype::MagneticField Simulator::getMagneticField(const Magnetometer& component) const
{
	return this->simulatorimpl_->getMagneticField(component);
}

datatype::StaticVector<3> Simulator::getAngularVelocity(const MultiGyro& component) const 
{
	return this->simulatorimpl_->getAngularVelocity(component);
}

datatype::Scalar Simulator::getAngularVelocity(const Gyro& component) const 
{
	return this->simulatorimpl_->getAngularVelocity(component);
}

datatype::Quaternion Simulator::getQuaternion(const STT& component) const 
{
	return this->simulatorimpl_->getQuaternion(component);
}

datatype::StaticVector<2> Simulator::getSunDirection(const Vectorsensor& component) const 
{
	return this->simulatorimpl_->getSunDirection(component);
}

datatype::StaticVector<2> Simulator::getEarthDirection(const Vectorsensor& component) const 
{
	return this->simulatorimpl_->getEarthDirection(component);
}

const datatype::PositionInfo Simulator::getTrueSatellitePosition() const
{
	return this->simulatorimpl_->getTrueSatellitePosition();
}

const datatype::Time& Simulator::getTrueTime() const {
	return this->simulatorimpl_->getTrueTime();
}

const datatype::Quaternion& Simulator::getTrueQuaternion() const { 
	return this->simulatorimpl_->getTrueQuaternion();
}

const datatype::StaticVector<3>& Simulator::getTrueAngular() const { 
	return this->simulatorimpl_->getTrueAngular();
}

datatype::Time Simulator::get_time(const Clock& component) const 
{
	return this->simulatorimpl_->get_time(component);
}

void Simulator::start()
{
	this->simulatorimpl_->start();
}

void Simulator::runOneCycle()
{
	this->simulatorimpl_->runOneCycle();
}

void Simulator::attachTorqueSource(TorqueSource* source)
{
	this->simulatorimpl_->attachTorqueSource(source);
}

void Simulator::attachNoiseSource(torquesource::NoiseBase* source)
{
	this->simulatorimpl_->attachNoiseSource(source);
}

void Simulator::attachMagneticSource(MagneticSource* source)
{
	this->simulatorimpl_->attachMagneticSource(source);
}

Simulator::Simulator()
{
	this->simulatorimpl_ = new SimulatorImpl();
}

} /* End of namespace stf::core::environment */
} /* End of namespace stf::core */
} /* End of namespace core */

/////////////////////////////////////
// シミュレータ用の部分特殊化
////////////////////////////////////

namespace stf {
namespace core {
namespace devicedriver {
namespace gyro {

template <>
void GyroBase<environment::Simulator>::do_update(){
	this->value_ = filter(this->environment_->getAngularVelocity(*this));
	if(this->datapool_ != 0){
		datapool_->set<GyroBase<environment::Simulator>>(datapool_hold_index_, this->value_);
	}
}

template <>
datatype::Scalar GyroBase<environment::Simulator>::filter(const datatype::Scalar& value){
    for(int i = 0; i < 3; i++){
		double noise = util::math::WhiteNoise(this->sigma_, 0);
		//slope計算は高速化のためScalarではなくdoubleで行う
		this->bias_rate_ += util::math::RungeKutta::slope(bias_rate_.value(), -1 / tau_, noise, 0.1);
    }
	return value + bias_rate_;
}

} /* End of namespace stf::core::devicedriver::gyro */

namespace earthsensor {
template <>
void EarthSensorBase<environment::Simulator>::do_update(){
	this->value_ = filter(this->environment_->getEarthDirection(*this));
	if(this->datapool_ != 0){
		datapool_->set<EarthSensorBase<environment::Simulator>>(datapool_hold_index_, this->value_);
	}
}

template <>
datatype::StaticVector<2> EarthSensorBase<environment::Simulator>::filter(const datatype::StaticVector<2>& value){
	datatype::StaticVector<3> earthvector_true = datatype::TypeConverter::toRectangular(value);

	datatype::EulerAngle angle;
	angle[0] = util::math::WhiteNoise(this->err_deg_ * util::math::DEG2RAD , 0) / 3;
	angle[1] = util::math::WhiteNoise(this->err_deg_ * util::math::DEG2RAD, 0) / 3;
	angle[2] = util::math::WhiteNoise(this->err_deg_ * util::math::DEG2RAD, 0) / 3;

	datatype::StaticVector<3> earthvector = datatype::TypeConverter::toDCM(angle) * earthvector_true;

	return datatype::TypeConverter::toPolar(earthvector);
}

} /* End of namespace stf::core::devicedriver::stt */

namespace gps {

template <>
void GPSBase<environment::Simulator>::do_update(){
	this->value_ = filter(this->environment_->getTrueSatellitePosition());

	//if(this->datapool_ != 0){
	//	datapool_->set<GPSBase<environment::Simulator>>(datapool_hold_index_, this->value_);
	//}
}
//
template <>
datatype::PositionInfo GPSBase<environment::Simulator>::filter(const datatype::PositionInfo& value){
	return value;
}

} /* End of namespace stf::core::devicedriver::gps */

namespace magnetometer {

//STT本体のQuaternion
//シミュレータ環境ではSTT座標系での真値を取得する
template <>
void TAMBase<environment::Simulator>::do_update(){
	this->value_ = filter(this->environment_->getMagneticField(*this));
	if(this->datapool_ != 0){
		datapool_->set<TAMBase<environment::Simulator>>(datapool_hold_index_, this->value_);
	}
}

template <>
datatype::MagneticField TAMBase<environment::Simulator>::filter(const datatype::MagneticField& value){
	return value;
}

} /* End of namespace stf::core::devicedriver::magnetometer */


namespace mtq {


template <>
void MTQBase<environment::Simulator>::do_update(){
	//線形性誤差の付加→TBD
	//this->linearity_ * 0.01
	//DBへ記録
	if(this->datapool_ != 0){
		datapool_->set<MTQBase<environment::Simulator>>(this->datapool_hold_index_, this->output_);
	}
}

// シミュレータ用の特殊化版コンストラクタ．
// トルクソースとしてシミュレータに自動的に登録
template<>
MTQBase<environment::Simulator>::MTQBase(int instance_id, const datatype::DCM &dcm, double max_torque, double min_torque, double linearity) 
	: AOCSActuator<datatype::MagneticMoment, datatype::Scalar, environment::Simulator>(instance_id, "MTQ", dcm), linearity_(linearity)
{
	//this->max_output_ = max_torque;
	//this->min_output_ = min_torque;	
	this->environment_->attachMagneticSource(this);
}

} /* End of namespace stf::core::devicedriver::mtq */
namespace rw {


template <>
void RWBase<environment::Simulator>::do_update(){
	//角運動量（回転数）の更新
	this->angular_momentum_ += this->output_.value() * STEPTIME;
	//
	if(this->datapool_ != 0){
		datapool_->set<RWBase<environment::Simulator>>(datapool_hold_index_, this->output_);
	}
}

// シミュレータ用の特殊化版コンストラクタ．
// トルクソースとしてシミュレータに自動的に登録
template<>
RWBase<environment::Simulator>::RWBase(int instance_id, const datatype::DCM &dcm, double max_torque, double min_torque, double max_angular_momentum) : 
AOCSActuator<datatype::StaticVector<3>, datatype::Scalar, environment::Simulator>(instance_id, "RW", dcm), max_angular_momentum_(max_angular_momentum)
{
	this->environment_->attachTorqueSource(this);
	//this->max_output_ = max_torque;
	//this->min_output_ = min_torque;
}

} /* End of namespace stf::core::devicedriver::rw */

namespace stt {

//STT本体のQuaternion
//シミュレータ環境ではSTT座標系での真値を取得する
template <>
void STTBase<environment::Simulator>::do_update(){
	count_++;
	if(count_ >= 5){
		this->value_ = filter(this->environment_->getQuaternion(*this));
		if(this->datapool_ != 0){
			datapool_->set<STTBase<environment::Simulator>>(datapool_hold_index_, this->value_);
		}
		count_ = 0;
	}
}

template <>
datatype::Quaternion STTBase<environment::Simulator>::filter(const datatype::Quaternion& value){
	datatype::EulerAngle angle;
	angle[0] = util::math::WhiteNoise(this->err_arcsec_ * util::math::ARCSEC2RAD , 0) / 3;
	angle[1] = util::math::WhiteNoise(this->err_arcsec_ * util::math::ARCSEC2RAD, 0) / 3;
	angle[2] = util::math::WhiteNoise(this->err_arcsec_ * util::math::ARCSEC2RAD, 0) / 3;
	return datatype::TypeConverter::toQuaternion(angle) * value;
}

} /* End of namespace stf::core::devicedriver::stt */
namespace sunsensor {

//STT本体のQuaternion
//シミュレータ環境ではSTT座標系での真値を取得する
template <>
void SunSensorBase<environment::Simulator>::do_update(){
	this->value_ = filter(this->environment_->getSunDirection(*this));
	if(this->datapool_ != 0){
		datapool_->set<SunSensorBase<environment::Simulator>>(datapool_hold_index_, this->value_);
	}
}

template <>
datatype::StaticVector<2> SunSensorBase<environment::Simulator>::filter(const datatype::StaticVector<2>& value){
	datatype::StaticVector<3> sunvector_true = datatype::TypeConverter::toRectangular(value);

	datatype::EulerAngle angle;
	//angle[0] = util::math::WhiteNoise(this->err_deg_ * util::math::DEG2RAD , 0) / 3;
	//angle[1] = util::math::WhiteNoise(this->err_deg_ * util::math::DEG2RAD, 0) / 3;
	//angle[2] = util::math::WhiteNoise(this->err_deg_ * util::math::DEG2RAD, 0) / 3;

	datatype::StaticVector<3> sunvector = datatype::TypeConverter::toDCM(angle) * sunvector_true;

	return datatype::TypeConverter::toPolar(sunvector);
}

} /* End of namespace stf::core::devicedriver::stt */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */