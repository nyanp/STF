/**
 * @file   Ostream.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "Ostream.h"
#include"../datatype/String.h"
#include"../util/math.h"

namespace {
	std::string toString_(const stf::datatype::String& str){
		std::string s(str.toChar());
		return s;
	}
}

//////////////////////////////////////
// Global OverLoad for std::ostream //
//////////////////////////////////////

// datatype::Scalar
std::ostream &operator << (std::ostream& out_file, const stf::datatype::Scalar& scalar){
	out_file << scalar.value();
	return out_file;
}

// datatype::String
std::ostream &operator << (std::ostream& out_file, const stf::datatype::String& str){
	out_file << str.toChar();
	return out_file;
}

// datatype::Vector
std::ostream &operator << (std::ostream& out_file, const stf::datatype::Vector& vec){
	for(int i = 0; i < vec.dimension(); i++){
		out_file.width(6);
		out_file << vec[i] << " ";
	}
	//out_file << "\n";
	return out_file;
}

std::ostream &operator << (std::ostream& out_file, const stf::datatype::Time& time){
	out_file << time.seconds() << ":" << time.milliseconds();
	return out_file;
}

// datatype::Matrix
std::ostream &operator << (std::ostream& out_file, const stf::datatype::Matrix& mat){
	out_file << "\n";
	for(int rows = 0;rows < mat.rows(); rows++){
		for(int cols = 0;cols < mat.cols(); cols++){
			out_file.width(11);
			out_file << mat[rows][cols];
		}
		out_file << "\n";
	}
	return out_file;
}

//Orbit Element
std::ostream &operator << (std::ostream& out_file, const stf::datatype::OrbitInfo& orbit){
	out_file << "orbit element:\n";
	out_file << "a(km):" << orbit.a / 1000 << "\n";
	out_file << "e:" << orbit.e << "\n";
	out_file << "i(deg):" << orbit.i * stf::util::math::RAD2DEG << "\n";
	out_file << "M(deg):" << orbit.M * stf::util::math::RAD2DEG << "\n";
	out_file << "omega(deg):" << orbit.omega * stf::util::math::RAD2DEG << "\n";
	out_file << "Omega(deg):" << orbit.Omega * stf::util::math::RAD2DEG << "\n";
	out_file << "n:" << orbit.n << "\n";
	return out_file;
}

//Satellite Position
std::ostream &operator << (std::ostream& out_file, const stf::datatype::PositionInfo& pos){
	out_file << "orbit element:\n";
	out_file << "velocity(m/s):" << pos.velocity << "\n";
	out_file << "position(m):" << pos.position << "\n";
	return out_file;
}

namespace stf { 
namespace util {
NoOutput none;
std::fstream log("log.txt");
Ostream<std::ostream> cout(std::cout);
Ostream<std::fstream> clog(log);
//Ostream<NoOutput> cout(none);
} /* End of namespace stf::util */
} /* End of namespace stf */