/**
 * @file   Simulator.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_environment_Simulator_h
#define stf_environment_Simulator_h

#include <fstream>
#include <iostream>
#include <vector>
#include "../core/devicedriver/AOCSComponent.h"
#include "../datatype/StaticVector.h"
#include "../datatype/StaticMatrix.h"
#include "../datatype/Vector.h"
#include "../datatype/Matrix.h"
#include "../datatype/Quaternion.h"
#include "../datatype/Time.h"
#include "../datatype/DateTime.h"
#include "../datatype/OrbitInfo.h"
#include "../datatype/Magnetic.h"
#include "torquesource/NoiseBase.h"
#include "../core/manager/ManagerBase.h"
#include "../datatype/List.h"
#include "../GlobalObject.h"
#include "Orbit.h"
#include "IODriverBase.h"

namespace interface {
class IAngularVelocityMeasurable;
class IQuaternionMesurable;
class ITimeMeasure;
} /* End of namespace interface */

namespace stf {
namespace environment {

class Simulator {
public:
	//Environmental Class
	template<int i>class GPIO : public GPIOBase<i> {};
	typedef SPIBase SPI;
	typedef UARTBase UART;

	// Type Traits
	typedef std::ofstream OutputStream;
	typedef std::ifstream InputStream;

	typedef core::devicedriver::AOCSComponent<datatype::StaticVector<3>,datatype::StaticVector<3>,Simulator> MultiGyro;
	typedef core::devicedriver::AOCSComponent<datatype::StaticVector<3>,datatype::Scalar,Simulator> Gyro;
	typedef core::devicedriver::AOCSComponent<datatype::Quaternion,datatype::Quaternion,Simulator> STT;
	typedef core::devicedriver::AOCSComponent<datatype::StaticVector<2>,datatype::StaticVector<2>,Simulator> Vectorsensor;
	typedef core::devicedriver::AOCSComponent<datatype::MagneticField,datatype::MagneticField,Simulator> Magnetometer;
	typedef core::devicedriver::clock::ITimeClock Clock;
	typedef core::devicedriver::AOCSComponent<datatype::StaticVector<3>,datatype::Scalar,Simulator> TorqueSource;
	typedef core::devicedriver::AOCSComponent<datatype::MagneticMoment,datatype::Scalar,Simulator> MagneticSource;

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
    Simulator();
	static Simulator* singleton_;//Singleton Object
	void step_() { this->true_time_ += this->timestep_; this->orbit_.addTime(this->timestep_); }
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

    datatype::StaticMatrix<4,4> Omega_;
    Global<Simulator> *global_;
    datatype::Time max_time_;
    std::ofstream *ofstream_;
	//datatype::List<core::manager::ManagerBase> managers_;
};

} /* End of namespace stf::environment */
} /* End of namespace stf */

#endif // aocs_environment_Simulator_h
