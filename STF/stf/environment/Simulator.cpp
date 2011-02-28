/**
 * @file   Simulator.cpp
 * @brief  ソフトウェアシミュレータ環境クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "Simulator.h"
#include "../datatype/EulerAngle.h"
#include "../datatype/TypeConverter.h"
#include "../util/math/Rand.h"
#include "../util/math/RungeKutta.h"
#include "../datatype/OrbitCalc.h"

namespace stf {
namespace environment {

Simulator* Simulator::singleton_ = new Simulator();

void Simulator::init(Global<Simulator>* global, double stepTimeInSecond, double maxTimeInSecond, const datatype::OrbitInfo& orbit,  std::ofstream *ostream)
{
	util::math::WhiteNoise_init(0);
    this->global_ = global;
    this->timestep_.add_milliseconds(stepTimeInSecond * 1000);
    this->max_time_.add_milliseconds(maxTimeInSecond * 1000);
	this->orbit_.set_orbitElement(orbit);
    if(ostream != 0)
        this->ofstream_ = ostream;
}

Simulator& Simulator::get_instance(){
	return *singleton_;
}

Simulator::~Simulator()
{
	this->ofstream_->close();
}

datatype::MagneticField Simulator::getMagneticField(const Magnetometer& component) const
{
	return component.get_transfomer().inverse() * this->orbit_.getMagneticField();
}

datatype::StaticVector<3> Simulator::getAngularVelocity(const MultiGyro& component) const 
{
	datatype::StaticVector<3> v  = component.get_transfomer().inverse() * this->true_angular_velocity_;
	return v;
}

datatype::Scalar Simulator::getAngularVelocity(const Gyro& component) const 
{
	return datatype::Scalar((component.get_transfomer().inverse() * this->true_angular_velocity_)[2]);
}

datatype::Quaternion Simulator::getQuaternion(const STT& component) const 
{
	datatype::Quaternion q = datatype::TypeConverter::toQuaternion(component.get_transfomer()).conjugate();
	return  q * this->true_quaternion_;
}

datatype::StaticVector<2> Simulator::getSunDirection(const Vectorsensor& component) const 
{
	return datatype::TypeConverter::toPolar(component.get_transfomer().inverse() * datatype::OrbitCalc::getSunDirectionInBodyFrame(this->orbit_.get_time(), this->true_quaternion_));
}

datatype::StaticVector<2> Simulator::getEarthDirection(const Vectorsensor& component) const 
{
	return datatype::TypeConverter::toPolar(component.get_transfomer().inverse() * datatype::OrbitCalc::getEarthDirectionInBodyFrame(this->orbit_.getSatellitePosition(), this->true_quaternion_));
}

const datatype::PositionInfo Simulator::getTrueSatellitePosition() const
{
	return this->orbit_.getSatellitePosition();
}

datatype::Time Simulator::get_time(const Clock& component) const 
{
    return this->true_time_;
}

void Simulator::start()
{
    std::cout << "Simulator Start" << std::endl;
    while(this->true_time_ < this->max_time_){
        this->runOneCycle();
    }
}

void Simulator::runOneCycle()
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

	datatype::List<core::manager::ManagerBase>::iterator it_m = global_->getFunctionManager()->begin(), end_m = global_->getFunctionManager()->end();
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

void Simulator::attachTorqueSource(TorqueSource* source)
{
    this->torque_sources_.push_back(source);
}

void Simulator::attachNoiseSource(torquesource::NoiseBase* source)
{
	this->noise_sources_.push_back(source);
}

void Simulator::attachMagneticSource(MagneticSource* source)
{
	this->mag_sources_.push_back(source);
}

Simulator::Simulator()
: orbit_()
{
	util::math::WhiteNoise_init(0);
}

} /* End of namespace core::environment */
} /* End of namespace core */
