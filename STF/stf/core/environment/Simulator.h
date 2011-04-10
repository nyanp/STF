/**
 * @file   Simulator.h
 * @brief  ソフトウェアシミュレータ環境クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_environment_Simulator_h
#define stf_core_environment_Simulator_h

#include <fstream>
#include <iostream>
#include <vector>
#include "IODriverBase.h"
#include "../../util/Ostream.h"
#include "Orbit.h"
#include "../../datatype/EulerAngle.h"
#include "../../datatype/TypeConverter.h"
#include "../../datatype/Magnetic.h"
#include "../../datatype/Scalar.h"
#include "../../datatype/Time.h"
#include "../../datatype/DateTime.h"

namespace interface {
class IAngularVelocityMeasurable;
class IQuaternionMesurable;
class ITimeMeasure;
} /* End of namespace interface */

namespace stf {
template<class T> class Global;

namespace datatype {
template<int> class StaticVector;
template<int,int> class StaticMatrix;
class Quaternion;
class Time;
class DateTime;
class Scalar;
class MagneticField;
struct OrbitInfo;
struct PositionInfo;
class MagneticMoment;
template<class> class List;
}
namespace core {
namespace devicedriver {
template<class Env, class T, class U> class AOCSSensor;
template<class Env, class T, class U> class AOCSActuator;
namespace clock {
class ITimeClock;
}
}

namespace environment {
namespace torquesource {
class NoiseBase;
}

class SimulatorBase {
public:
	virtual const datatype::Time& getTrueTime() const = 0;
	virtual const datatype::Quaternion& getTrueQuaternion() const = 0;
	virtual const datatype::StaticVector<3>& getTrueAngular() const = 0;
	virtual const datatype::PositionInfo getTrueSatellitePosition() const = 0;
};

//! ソフトウェアシミュレータ環境クラス．
/*! 
	IOドライバレベルのエミュレーションは行わず，センサやアクチュエータとのデータ交換は
	各センサ，アクチュエータ型のSimulatorに特殊化したdo_update関数によって行われる．

	@code
	//シミュレータの生成
	stf::environment::Simulator& s = stf::environment::Simulator<App>::get_instance();

	//グローバルオブジェクトの生成
	stf::factory::SatelliteFactory<ENV>* en = new stf::factory::PRISMFactory<ENV>();
	stf::Global<ENV>* gl = en->create();

	//シミュレーション用の軌道情報
	datatype::OrbitInfo orbit(7100000, 0.01, 0, 0.5 * util::math::PI, 0, 0);

	//シミュレータ初期化
	s.init(gl, 100, 100, orbit, new std::ofstream("output.csv"));

	//2000ステップ実行
	for(int i = 0; i < 2000; i++)
		s.runOneCycle();
	@endcode
 */
template<class App>
class Simulator : public SimulatorBase{
public:
	typedef App Application;

	//Environmental Class
	//! シミュレータ環境用のGPIOドライバ．使用しないので空クラスとして定義
	template<int i>class GPIO : public GPIOBase<i> {};
	typedef SPIBase SPI;
	typedef UARTBase UART;

	// Type Traits
	typedef util::Ostream OutputStream;
	typedef util::Ofstream OutputFileStream;
	typedef std::ifstream InputFileStream;

	typedef core::devicedriver::AOCSSensor<Simulator, datatype::StaticVector<3>, datatype::StaticVector<3>> MultiGyro;
	typedef core::devicedriver::AOCSSensor<Simulator, datatype::StaticVector<3>, datatype::Scalar> Gyro;
	typedef core::devicedriver::AOCSSensor<Simulator, datatype::Quaternion, datatype::Quaternion> STT;
	typedef core::devicedriver::AOCSSensor<Simulator, datatype::StaticVector<2>, datatype::StaticVector<2>> Vectorsensor;
	typedef core::devicedriver::AOCSSensor<Simulator, datatype::MagneticField, datatype::MagneticField> Magnetometer;
	typedef core::devicedriver::clock::ITimeClock Clock;
	typedef core::devicedriver::AOCSActuator<Simulator, datatype::StaticVector<3>, datatype::Scalar> TorqueSource;
	typedef core::devicedriver::AOCSActuator<Simulator, datatype::MagneticMoment, datatype::Scalar> MagneticSource;

	static Simulator& get_instance();
	void init(Global<Simulator>* global, double stepTimeInSecond, double maxTimeInSecond, const datatype::OrbitInfo& orbit, std::ofstream *ostream);
    virtual ~Simulator();
    datatype::StaticVector<3> getAngularVelocity(const MultiGyro& component) const ;
    datatype::Scalar getAngularVelocity(const Gyro& component) const ;
    datatype::Quaternion getQuaternion(const STT& component) const ;
	datatype::StaticVector<2> getSunDirection(const Vectorsensor& component) const ;
	datatype::StaticVector<2> getEarthDirection(const Vectorsensor& component) const ;
	datatype::MagneticField getMagneticField(const Magnetometer& component) const;
	datatype::Time get_time(const Clock& component) const ;

	virtual const datatype::Time& getTrueTime() const { return this->true_time_; }
	virtual const datatype::Quaternion& getTrueQuaternion() const { return this->true_quaternion_; }
	virtual const datatype::StaticVector<3>& getTrueAngular() const { return this->true_angular_velocity_; }
	virtual const datatype::PositionInfo getTrueSatellitePosition() const;

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
    Global<Simulator<App> > *global_;
    datatype::Time max_time_;
    std::ofstream *ofstream_;

	void step_() { this->true_time_ += this->timestep_; this->orbit_.addTime(this->timestep_); }

    Simulator();
	static Simulator<App>* singleton_;//Singleton Object
};

template<class App>
void Simulator<App>::init(Global<Simulator<App> >* global, double stepTimeInSecond, double maxTimeInSecond, const datatype::OrbitInfo& orbit,  std::ofstream *ostream)
{
	util::math::WhiteNoise_init(0);
    this->global_ = global;
    this->timestep_.add_milliseconds(stepTimeInSecond * 1000);
    this->max_time_.add_milliseconds(maxTimeInSecond * 1000);
	this->orbit_.set_orbitElement(orbit);
    if(ostream != 0)
        this->ofstream_ = ostream;
}

template<class App>
Simulator<App>::~Simulator()
{
	this->ofstream_->close();
}

template<class App>
datatype::MagneticField Simulator<App>::getMagneticField(const Magnetometer& component) const
{
	return component.get_transfomer().inverse() * this->orbit_.getMagneticField();
}

template<class App>
datatype::StaticVector<3> Simulator<App>::getAngularVelocity(const MultiGyro& component) const 
{
	datatype::StaticVector<3> v  = component.get_transfomer().inverse() * this->true_angular_velocity_;
	return v;
}

template<class App>
datatype::Scalar Simulator<App>::getAngularVelocity(const Gyro& component) const 
{
	return datatype::Scalar((component.get_transfomer().inverse() * this->true_angular_velocity_)[2]);
}

template<class App>
datatype::Quaternion Simulator<App>::getQuaternion(const STT& component) const 
{
	datatype::Quaternion q = datatype::TypeConverter::toQuaternion(component.get_transfomer()).conjugate();
	return  q * this->true_quaternion_;
}

template<class App>
datatype::StaticVector<2> Simulator<App>::getSunDirection(const Vectorsensor& component) const 
{
	return datatype::TypeConverter::toPolar(component.get_transfomer().inverse() * datatype::OrbitCalc::getSunDirectionInBodyFrame(this->orbit_.get_time(), this->true_quaternion_));
}

template<class App>
datatype::StaticVector<2> Simulator<App>::getEarthDirection(const Vectorsensor& component) const 
{
	return datatype::TypeConverter::toPolar(component.get_transfomer().inverse() * datatype::OrbitCalc::getEarthDirectionInBodyFrame(this->orbit_.getSatellitePosition(), this->true_quaternion_));
}

template<class App>
const datatype::PositionInfo Simulator<App>::getTrueSatellitePosition() const
{
	return this->orbit_.getSatellitePosition();
}

template<class App>
datatype::Time Simulator<App>::get_time(const Clock& component) const 
{
    return this->true_time_;
}

template<class App>
void Simulator<App>::start()
{
    std::cout << "Simulator Start" << std::endl;
    while(this->true_time_ < this->max_time_){
        this->runOneCycle();
    }
}

template<class App>
void Simulator<App>::runOneCycle()
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

template<class App>
void Simulator<App>::attachTorqueSource(TorqueSource* source)
{
    this->torque_sources_.push_back(source);
}

template<class App>
void Simulator<App>::attachNoiseSource(torquesource::NoiseBase* source)
{
	this->noise_sources_.push_back(source);
}

template<class App>
void Simulator<App>::attachMagneticSource(MagneticSource* source)
{
	this->mag_sources_.push_back(source);
}

template<class App>
Simulator<App>::Simulator()
: orbit_()
{
	util::math::WhiteNoise_init(0);
}

template<class App>
Simulator<App>& Simulator<App>::get_instance(){
	return *Simulator<App>::singleton_;
}

template<class App>
Simulator<App>* Simulator<App>::singleton_ = new Simulator<App>();

} /* End of namespace stf::core::environment */
} /* End of namespace stf::core */
} /* End of namespace stf */


/////////////////////////////////////
// シミュレータ用の部分特殊化
////////////////////////////////////

namespace stf {
namespace core {
namespace devicedriver {
namespace gyro {


} /* End of namespace stf::core::devicedriver::gyro */

namespace earthsensor {


} /* End of namespace stf::core::devicedriver::stt */

namespace gps {



} /* End of namespace stf::core::devicedriver::gps */

namespace magnetometer {


} /* End of namespace stf::core::devicedriver::magnetometer */


namespace mtq {


} /* End of namespace stf::core::devicedriver::mtq */
namespace rw {


} /* End of namespace stf::core::devicedriver::rw */

namespace stt {


} /* End of namespace stf::core::devicedriver::stt */
namespace sunsensor {


} /* End of namespace stf::core::devicedriver::stt */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */


#endif // stf_core_environment_Simulator_h
