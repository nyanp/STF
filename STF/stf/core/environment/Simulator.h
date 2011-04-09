/**
 * @file   Simulator.h
 * @brief  ソフトウェアシミュレータ環境クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_environment_Simulator_h
#define stf_core_environment_Simulator_h

#include "IODriverBase.h"
#include "../../util/Ostream.h"

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

} /* End of namespace stf::core::environment */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_environment_Simulator_h
