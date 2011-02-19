#include<iostream>
#include<fstream>
#include "scube/environment/Simulator.h"
#include "scube/satellite/PRISMFactory.h"

using namespace scube;

int main(void){
	typedef environment::Simulator env;

	std::cout << "AOCS Framework Test Program:\n\n";

	//Clock clk;

	scube::factory::SatelliteFactory<env>* en = new scube::factory::PRISMFactory<env>();
	scube::Global<env>* gl = en->create();

	//シミュレータの生成
	scube::environment::Simulator& s = scube::environment::Simulator::getInstance();
	//シミュレーション用の軌道情報
	datatype::OrbitInfo orbit(7100000, 0.01, 0, 0.5 * util::math::PI, 0, 0);
	//シミュレータ初期化
	s.init(gl, STEPTIME, 100, orbit, new std::ofstream("output.csv"));

	//シミュレータ外乱設定
	//datatype::Vector v(3);
	//v[0] = 0.3;
	//v[1] = -0.2;
	//s.attachNoiseSource(new environment::torquesource::ImpulseNoise(3,v,0,3000,&s));
    //s.attachNoiseSource(new environment::torquesource::WhiteNoise(0.01,0));

	///////////////////////////////////////////////
	// 実行
	for(int i = 0; i < 2000; i++)
		s.runOneCycle();

	return 1;
}
