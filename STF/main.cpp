#include<iostream>
#include<fstream>
#include<vector>
#include "stf/util/Ostream.h"

//#include "stf/core/strategy/control/Includes.h"
#include "stf/GlobalObject.h"
#include "stf/InstanceID.h"

#include "stf/environment/NullEnv.h"
#include "stf/environment/Simulator.h"
#include "stf/environment/torquesource/ImpulseNoise.h"
#include "stf/environment/torquesource/WhiteNoise.h"

#include "stf/core/mode/ModeBase.h"

#include "stf/core/event/SubjectBase.h"
#include "stf/core/event/Event.h"
#include "stf/core/manager/Includes.h"
#include "stf/core/functor/Functor.h"
#include "stf/core/command/ModeChangeCommand.h"

#include "stf/util/math.h"
#include "stf/util/Trace.h"
#include "stf/core/datapool/Datapool.h"
#include "stf/core/devicedriver/Includes.h"
#include "stf/datatype/IAocsData.h"
#include "stf/datatype/TypeConverter.h"
#include "stf/datatype/Quaternion.h"
#include "stf/datatype/EulerAngle.h"
#include "stf/datatype/DCM.h"
#include "stf/datatype/TypeConverter.h"
#include "stf/datatype/StaticVector.h"
#include "stf/datatype/StaticMatrix.h"
#include "stf/core/datapool/Datapool.h"
#include "stf/core/devicedriver/CDHComponent.h"
#include "stf/util/loki/HierarchyGenerators.h"
#include "stf/core/devicedriver/IOPort.h"
#include "stf/satellite/PRISMFactory.h"
#include "stf/satellite/NJFactory.h"
#include "stf/satellite/SimpleSatelliteFactory.h"
#include "stf/util/math/Exp.h"

#include "stf/environment/sh/iodefine.h"
#include "stf/interface/Iterator.h"
#include "stf/satellite/PRISM/PRISMIterator.h"


using namespace stf;
using namespace stf::core;
using namespace stf::core::devicedriver;
using stf::util::cout;
using datatype::TypeConverter;


class SPIBase {
public:
	void send(char* s){}
};

struct HW {
struct STTPX {
	struct SPI{
		static const int BAUDRATE = 9600;
		enum IO{
			MOSI = 1,
			MISO = 2
		};
	};
	enum GPIO{
		BASEADDR = 1

	};
};
struct RW {
	enum SPI{
		MOSI = 3,
		MISO = 4
	};
	enum GPIO{
		ENABLE = 4
	};
};
};

class H8 {
public:
	class SPI : public SPIBase{
	public:
		SPI(int baseaddr, int baudrate, int mode){}
	};
	class GPIO{
	public:
		GPIO(int baseaddr){}
	};

};


int main(void){
	datatype::Scalar target;
	strategy::control::SingleAxisPID pid(0, 1, 0, 0, 0, target);
	devicedriver::rw::RW<ENV> rw(0, datatype::TypeConverter::toDCM(0,0,0) );
	strategy::control::ControlBlock cb(0, &pid, &rw);

	util::Trace::enable(util::Trace::kManager);
	util::Trace::enable(util::Trace::kControlBlock);
	util::Trace::enable(util::Trace::kCommand);
	util::Trace::enable(util::Trace::kEvent);
	util::Trace::enable(util::Trace::kDataPool);

	util::Trace tr(util::Trace::kManager, "man");

	typedef devicedriver::CompositeOutput<devicedriver::mtq::MTQ<ENV>, 3> ThreeAxisMTQ;
	typedef devicedriver::CompositeOutput<devicedriver::rw::RW<ENV>, 4> SkewRW;
	typedef devicedriver::CompositeInput<devicedriver::gyro::Gyro<ENV>, 3> ThreeAxisGyro;
	typedef devicedriver::CompositeInput<devicedriver::stt::STT<ENV>, 2> TwoAxisSTT;
	typedef devicedriver::CompositeInput<devicedriver::sunsensor::SunSensor<ENV>, 6> SixAxisSS;
	typedef devicedriver::gyro::Gyro<ENV> GYRO;
	typedef devicedriver::stt::STT<ENV> STT;
	typedef devicedriver::mtq::MTQ<ENV> MTQ;
	typedef devicedriver::sunsensor::SunSensor<ENV> SS;
	typedef devicedriver::rw::RW<ENV> RW;

	std::cout << "AOCS Framework Test Program:\n\n";
	std::cout << Conversion<int, double>::exists << std::endl;
	std::cout << Conversion<char*, double>::exists << std::endl;

	//stf::factory::SatelliteFactory<ENV>* en = new ();
	stf::factory::PRISMFactory<ENV>& factory = stf::factory::PRISMFactory<ENV>::getInstance();
	stf::Global<ENV>* gl = factory.create();

	//stf::factory::SatelliteFactory<ENV>* en2 = new stf::factory::NJFactory<ENV>();
	stf::Global<ENV>* gl2 = stf::factory::NJFactory<ENV>::getInstance().create();

	//stf::factory::SatelliteFactory<ENV>* en3 = new stf::factory::SimpleSatelliteFactory<ENV>();
	stf::Global<ENV>* gl3 = stf::factory::SimpleSatelliteFactory<ENV>::getInstance().create();

	stf::Global<ENV>* gl4 = stf::factory::SimpleSatelliteFactory<ENV>::getInstance().create();
	//グローバルオブジェクトの生成
	//stf::Global<env>& g = stf::Global<env>::get_instance();

	//シミュレータの生成
	stf::environment::Simulator& s = stf::environment::Simulator::get_instance();
	//シミュレーション用の軌道情報
	datatype::OrbitInfo orbit(7100000, 0.01, 0, 0.5 * util::math::PI, 0, 0);
	//シミュレータ初期化
	s.init(gl3, STEPTIME, 100, orbit, new std::ofstream("output.csv"));
	
	//シミュレータ外乱設定
	datatype::StaticVector<3> v;
	v[0] = 0.3;
	v[1] = -0.2;
	s.attachNoiseSource(new environment::torquesource::ImpulseNoise(3, v, 0, 3000,&s));
    s.attachNoiseSource(new environment::torquesource::WhiteNoise(0.01, 0));

	//実行タスクの追加

	//そのほかの設定
	//g.comm->add_command(new core::command::modeChangeCommand(g.get_global_time(), g.missionmode, g.modeman));
	//g.modeman->change_mode(g.safemode);

	///////////////////////////////////////////////
	// 実行
	for(int i = 0; i < 800; i++)
		s.runOneCycle();

	return 1;
}
