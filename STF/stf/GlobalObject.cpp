#ifndef GlobalObject_cpp
#define GlobalObject_cpp

#include "GlobalObject.h"

namespace stf {

/*
template<class Env>
datatype::SatelliteModel& Global<Env>::getSatelliteModel(){
	return Global<Env>::g_SatelliteModel;
}

template<class Env>
const datatype::Time Global<Env>::getGlobalTime(){
	return Global<Env>::g_Clock.getTime();
}

template<class Env>
const datatype::DateTime Global<Env>::getAbsoluteTime(){
	return Global<Env>::g_Clock.getAbsoluteTime();
}

template const datatype::Time Global<environment::Simulator>::getGlobalTime();
//template const datatype::Time Global<environment::NullEnv>::getGlobalTime();
template const datatype::DateTime Global<environment::Simulator>::getAbsoluteTime();
//template const datatype::DateTime Global<environment::NullEnv>::getAbsoluteTime();
template datatype::SatelliteModel& Global<environment::Simulator>::getSatelliteModel();*/

//template Global<environment::Simulator>& Global<environment::Simulator>::getInstance();
//template Global<environment::NullEnv>& Global<environment::NullEnv>::getInstance();




/*
// コンストラクタ
template<class Env>
Global<Env>::Global(){
	util::cout << "Global Constructor Called:" << util::endl;
	////////////////////////
	// オブジェクトの生成
	////////////////////////

    ///////////////////////////////////////////////
	//Environment
	this->g_Logger = new core::devicedriver::tmhandler::DebugLogger("telemetry.csv",false);

	///////////////////////////////////////////////
	//Manager
	this->modeman = new manager::ModeManager(ID_MODEMANAGER);
	this->conman = new manager::ControlManager(ID_CONTROLMANAGER);
	this->uniman = new manager::UnitManager(ID_UNITMANAGER);
	this->telman= new manager::TelemetryManager(ID_TELEMETRYMANAGER);
	this->cusman = new manager::CustomManager(ID_CUSTOMMANAGER);
	this->sysman = new manager::SystemManager(ID_SYSTEMMANAGER);
	this->commman = new manager::CommandManager(ID_COMMANDMANAGER);

	///////////////////////////////////////////////
	//Component
	typedef devicedriver::CompositeOutput<devicedriver::mtq::MTQ<Env>,3> ThreeAxisMTQ;
	typedef devicedriver::CompositeOutput<devicedriver::rw::RW<Env>,4> SkewRW;
	typedef devicedriver::CompositeInput<devicedriver::gyro::Gyro<Env>,3> ThreeAxisGyro;
	typedef devicedriver::CompositeInput<devicedriver::stt::STT<Env>,2> TwoAxisSTT;
	typedef devicedriver::CompositeInput<devicedriver::sunsensor::SunSensor<Env>,6> SixAxisSS;
	typedef devicedriver::gyro::Gyro<Env> GYRO;
	typedef devicedriver::stt::STT<Env> STT;
	typedef devicedriver::mtq::MTQ<Env> MTQ;
	typedef devicedriver::sunsensor::SunSensor<Env> SS;
	typedef devicedriver::rw::RW<Env> RW;
	typedef devicedriver::magnetometer::TAM<Env> TAM;
	typedef devicedriver::earthsensor::EarthSensor<Env> ES;
	typedef devicedriver::gps::DummyGPS<Env> GPS;

	this->mtq1 = new MTQ(ID_MTQ_X,datatype::TypeConverter::toDCM(0,-90,0));
	this->mtq2 = new MTQ(ID_MTQ_Y,datatype::TypeConverter::toDCM(0,0,90));
	this->mtq3 = new MTQ(ID_MTQ_Z,datatype::TypeConverter::toDCM(0,0,0));
	this->mtq = new ThreeAxisMTQ(ID_MTQ,datatype::TypeConverter::toDCM(0,0,0));
	mtq->appendChild(mtq1);
	mtq->appendChild(mtq2);
	mtq->appendChild(mtq3);

	this->stt1 = new STT(ID_STT_X,datatype::TypeConverter::toDCM(0,0,0));
	this->stt2 = new STT(ID_STT_Y,datatype::TypeConverter::toDCM(90,0,0));
	this->stt =  new TwoAxisSTT(ID_STT,datatype::TypeConverter::toDCM(0,0,0));
	stt->appendChild(stt1);
	stt->appendChild(stt2);
	
	this->gyro1 = new GYRO(ID_GYRO_X,datatype::TypeConverter::toDCM(0,-90,0));
	this->gyro2 = new GYRO(ID_GYRO_Y,datatype::TypeConverter::toDCM(0,0,90));
	this->gyro3 = new GYRO(ID_GYRO_Z,datatype::TypeConverter::toDCM(0,0,0));
	this->gyro =  new ThreeAxisGyro(ID_GYRO,datatype::TypeConverter::toDCM(0,0,0));
	gyro->appendChild(gyro1);
	gyro->appendChild(gyro2);
	gyro->appendChild(gyro3);

	this->ss1 = new SS(ID_SS_PX,datatype::TypeConverter::toDCM(0,-90,0));
	this->ss2 = new SS(ID_SS_PY,datatype::TypeConverter::toDCM(0,0,90));
	this->ss3 = new SS(ID_SS_PZ,datatype::TypeConverter::toDCM(0,0,0));
	this->ss4 = new SS(ID_SS_MX,datatype::TypeConverter::toDCM(180,-90,0));
	this->ss5 = new SS(ID_SS_MY,datatype::TypeConverter::toDCM(180,0,90));
	this->ss6 = new SS(ID_SS_MZ,datatype::TypeConverter::toDCM(180,0,0));
	this->ss = new SixAxisSS(ID_SS,datatype::TypeConverter::toDCM(0,0,0));
	ss->appendChild(ss1);
	ss->appendChild(ss2);
	ss->appendChild(ss3);
	ss->appendChild(ss4);
	ss->appendChild(ss5);
	ss->appendChild(ss6);

	this->rw1 = new RW(ID_RW_1,datatype::TypeConverter::toDCM(0,0,0));
	this->rw2 = new RW(ID_RW_2,datatype::TypeConverter::toDCM(0,70,0).inverse());
	this->rw3 = new RW(ID_RW_3,datatype::TypeConverter::toDCM(120,70,0).inverse());
	this->rw4 = new RW(ID_RW_4,datatype::TypeConverter::toDCM(240,70,0).inverse());
	this->rw = new SkewRW(ID_RW,datatype::TypeConverter::toDCM(0,0,0));

	rw->appendChild(rw1);
	rw->appendChild(rw2);
	rw->appendChild(rw3);
	rw->appendChild(rw4);

	this->tam = new TAM(ID_TAM,datatype::TypeConverter::toDCM(0,0,0));
	this->earth = new ES(ID_EARTH,datatype::TypeConverter::toDCM(0,0,0));
	this->gpsdummy = new GPS(ID_GPS);
	this->comm = new devicedriver::cmhandler::DummyCommandReceiver(ID_RECEIVER,this->commman);

	///////////////////////////////////////////////
	//DB Connection
	g_EventDatapool.create<core::event::SubjectBase<core::event::ModeChangeEvent>>(ID_ModeChangeEvent,10,"ModeChangeEvent");

	mtq1->connect(&g_DataPool,10,"MTQ1");
	mtq2->connect(&g_DataPool,10,"MTQ2");
	mtq3->connect(&g_DataPool,10,"MTQ3");
	mtq->connect(&g_DataPool,10,"MTQ");

	stt1->connect(&g_DataPool,10,"STT1");
	stt2->connect(&g_DataPool,10,"STT2");
	stt->connect(&g_DataPool,10,"STT");

	gyro1->connect(&g_DataPool,20,"GYRO1");
	gyro2->connect(&g_DataPool,20,"GYRO2");
	gyro3->connect(&g_DataPool,20,"GYRO3");
	gyro->connect(&g_DataPool,20,"GYRO");

	tam->connect(&g_DataPool,20,"TAM");
	rw->connect(&g_DataPool,20,"RW");

	///////////////////////////////////////////////
	//Strategy

	//simple pid controller
	// stt->pid->mtq
	core::strategy::control::EKFParamaters param;
	param.timestep = STEPTIME;
	param.tau = GYROECRV;
	for(int i = 0;i < 6; i++) param.P0[i][i] = 20;
    param.v = 0.1;
	param.w_b = 0.3;
	param.w_q = 0.1;

	datatype::Quaternion q_target;
	this->pid =new core::strategy::control::ControlBlock
	(
		ID_PID,
		new core::strategy::control::QuaternionPID
		(
			ID_PID,0.05, 0.0, 0.5, 0.1,q_target,
			stt1,
			rw
		),
		rw
	);

	//simple pid controller - 2
	datatype::Quaternion q_target2;
	q_target2[0] = 0.4;
	q_target2[1] = 0.3;
	q_target2.normalize();

	this->pid2 = new core::strategy::control::ControlBlock
	(
		ID_EKF,
		new core::strategy::control::QuaternionPID
		(
			ID_PID, 0.05, 0.0, 0.5, 0.1, q_target, 
			new core::strategy::control::EKF
			(
				ID_EKF, param, stt, gyro, 0, 0
			), 
			rw
		),
		rw
	);
	
	//simple rate dumper
	this->ratedumping = 
		new core::strategy::control::ControlBlock(
			ID_DUMPING,
			new core::strategy::control::RateDumping(ID_DUMPING, 0.1, 0.0, 0.04, 0.1,gyro,rw),
			rw
		);

	//PRISM Controller
	
	Combining_2<datatype::StaticVector<3>>* PRISM_COMBINER = new Combining_2<datatype::StaticVector<3>>(0);
	CrossProduct* PRISM_CROSSPRODUCT = new CrossProduct(0);
	GGCompensation* PRISM_GGCOMP = new GGCompensation(0);
	PID* PRISM_PID = new PID(0,0.1,0.01,0.5,STEPTIME,*(new datatype::Quaternion));
	EKF* PRISM_EKF = new EKF(0);
	SunMagTRIAD* PRISM_TRIAD = new SunMagTRIAD(0);
	
	ControlBlock* PRISM_CONTROLLER =
		new ControlBlock(0,PRISM_CROSSPRODUCT,mtq);

	// PID(地球指向) 
    // output: Torque
	// input:  EKF -> Quaternion
	//         EKF -> Omega
	PRISM_PID->connectSource<0>(PRISM_EKF);
	PRISM_PID->connectSource<1>(PRISM_EKF);

	// EKF 
    // output: Quatenrion,Omega
	// input: TRIAD -> Quaternion
	//        Gyro  -> Omega
	PRISM_EKF->connectSource<0>(PRISM_TRIAD);
	PRISM_EKF->connectSource<1>(gyro);

	// TRIAD 
    // output: Quatenrion
	// input:  Sunsensor    -> Sunvector
	//         MagnetoMeter -> MagneticField
	//         TLEUplink    -> OrbitInfo
	//         (RTC)        -> DateTime
	PRISM_TRIAD->connectSource<0>(ss);
	PRISM_TRIAD->connectSource<1>(tam);
	PRISM_TRIAD->connectSource<2>(gpsdummy);
//	PRISM_TRIAD->connectSource<3>(&g_Clock);

	// Gravity Gradient Compensation
	// output: Torque
	// input:  EKF          -> Quaternion
	//         TLEUplink    -> OrbitInfo
	//         (InnerModel) -> I
	PRISM_GGCOMP->connectSource<0>(PRISM_EKF);
	PRISM_GGCOMP->connectSource<1>(gpsdummy);

	// Torque Combiner
	// output: Torque
	// input:  PID         -> Torque
	PRISM_COMBINER->connectSource<0>(PRISM_PID);
	PRISM_COMBINER->connectSource<1>(PRISM_GGCOMP);

	// Cross Product
	// output: Magnetic Moment
	// input:  MagnetoMeter     -> Magnetic Field
	//         Torrque Combiner -> Torque
	PRISM_CROSSPRODUCT->connectSource<0>(PRISM_COMBINER);
	PRISM_CROSSPRODUCT->connectSource<1>(tam);

	//this->nocontrol = new core::strategy::control::NoControl(ID_NOCONTROL);
	this->outputall = new core::strategy::telemetry::OutputAll(ID_OUTPUTALLTM,g_Logger,&g_DataPool,&g_EventDatapool);

	gpsdummy->doUpdate();
	tam->doUpdate();
	ss->doUpdate();
	
	PRISM_CONTROLLER->computeTorque(*(new datatype::Time(1,0)));
	//Mode
	this->safemode = new mode::SafeMode(ID_SAFEMODE);
	this->missionmode = new mode::MissionMode(ID_MISSIONMODE);
	this->unloadingmode = new mode::UnloadingMode(ID_UNLOADINGMODE);

	//this->func = new functor::Functor<core::functor::Getter_Over<datatype::Time,devicedriver::clock::ITimeClock>,core::functor::change_modeFunc>
	//(
	//new core::functor::Getter_Over<datatype::Time,devicedriver::clock::ITimeClock>(&g_Clock,&devicedriver::clock::ITimeClock::getTime,new datatype::Time(10,0)),
	//new core::functor::change_modeFunc(*(this->missionmode))
	//);
	//ModeHotSpotとなるコンポーネントの初期化が全て終わってから各モードのinitを呼ぶ
	//this->safemode->init();
	//this->missionmode->init();
	//this->unloadingmode->init();
}*/

/*
template <class Env>
Global<Env>::~Global(){
	util::cout << "Global Destructor Called:" << util::endl;
}*/

} /* End of namespace stf */
#endif // GlobalObject_cpp