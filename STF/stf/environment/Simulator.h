/**
 * @file   Simulator.h
 * @brief  ソフトウェアシミュレータ環境クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_environment_Simulator_h
#define stf_environment_Simulator_h

#include <fstream>
#include <iostream>
#include <vector>

#include "../datatype/StaticVector.h"
#include "../datatype/StaticMatrix.h"
#include "../datatype/Vector.h"
#include "../datatype/Matrix.h"
#include "../datatype/Quaternion.h"
#include "../datatype/Time.h"
#include "../datatype/DateTime.h"
#include "../datatype/OrbitInfo.h"
#include "../datatype/Magnetic.h"
#include "../datatype/Scalar.h"
#include "../datatype/List.h"

#include "IODriverBase.h"
#include "../util/Ostream.h"

namespace interface {
class IAngularVelocityMeasurable;
class IQuaternionMesurable;
class ITimeMeasure;
} /* End of namespace interface */

namespace stf {
template<class T> class Global;
namespace core {
namespace devicedriver {
template<class T, class U, class Env> class AOCSSensor;
template<class T, class U, class Env> class AOCSActuator;
namespace clock {
class ITimeClock;
}
}
}
namespace environment {
namespace torquesource {
class NoiseBase;
}

class SimulatorImpl;

//! ソフトウェアシミュレータ環境クラス．
/*! 
	IOドライバレベルのエミュレーションは行わず，センサやアクチュエータとのデータ交換は
	各センサ，アクチュエータ型のSimulatorに特殊化したdo_update関数によって行われる．

	@code
	//シミュレータの生成
	stf::environment::Simulator& s = stf::environment::Simulator::get_instance();

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
class Simulator {
public:
	//Environmental Class
	//! シミュレータ環境用のGPIOドライバ．使用しないので空クラスとして定義
	template<int i>class GPIO : public GPIOBase<i> {};
	typedef SPIBase SPI;
	typedef UARTBase UART;

	// Type Traits
	typedef util::Ostream OutputStream;
	typedef util::Ofstream OutputFileStream;
	typedef std::ifstream InputFileStream;

	typedef core::devicedriver::AOCSSensor<datatype::StaticVector<3>, datatype::StaticVector<3>, Simulator> MultiGyro;
	typedef core::devicedriver::AOCSSensor<datatype::StaticVector<3>, datatype::Scalar, Simulator> Gyro;
	typedef core::devicedriver::AOCSSensor<datatype::Quaternion, datatype::Quaternion, Simulator> STT;
	typedef core::devicedriver::AOCSSensor<datatype::StaticVector<2>, datatype::StaticVector<2>, Simulator> Vectorsensor;
	typedef core::devicedriver::AOCSSensor<datatype::MagneticField, datatype::MagneticField, Simulator> Magnetometer;
	typedef core::devicedriver::clock::ITimeClock Clock;
	typedef core::devicedriver::AOCSActuator<datatype::StaticVector<3>, datatype::Scalar, Simulator> TorqueSource;
	typedef core::devicedriver::AOCSActuator<datatype::MagneticMoment, datatype::Scalar, Simulator> MagneticSource;

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

	const datatype::Time& getTrueTime() const;
	const datatype::Quaternion& getTrueQuaternion() const;
	const datatype::StaticVector<3>& getTrueAngular() const;
	const datatype::PositionInfo getTrueSatellitePosition() const;

    void start();
    void runOneCycle();
	void attachTorqueSource(TorqueSource* source);
	void attachMagneticSource(MagneticSource* source);
	void attachNoiseSource(torquesource::NoiseBase* source);
private:
    Simulator();
	static Simulator* singleton_;//Singleton Object
	SimulatorImpl* simulatorimpl_;
};

} /* End of namespace stf::environment */
} /* End of namespace stf */

#endif // aocs_environment_Simulator_h
