/**
 * @file   Ostream.cpp
 * @brief  標準出力のラッパ．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "Ostream.h"
#include"../util/math.h"
#include"../datatype/String.h"
#include"../datatype/Scalar.h"
#include"../datatype/Vector.h"
#include"../datatype/Matrix.h"
#include"../datatype/Scalar.h"
#include"../datatype/Time.h"
#include"../datatype/DateTime.h"
#include"../datatype/OrbitInfo.h"

namespace {
	std::string toString_(const stf::datatype::String& str){
		std::string s(str.to_char());
		return s;
	}
}

namespace stf { 
namespace util {


// datatype::Scalar
std::ostream &operator << (std::ostream& out_file, const stf::datatype::Scalar& scalar){
	out_file << scalar.value();
	return out_file;
}

// datatype::String
std::ostream &operator << (std::ostream& out_file, const stf::datatype::String& str){
	out_file << str.to_char();
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

// std::ostreamクラスの演算子に対するグローバルな演算子オーバーロード
std::ostream &operator << (std::ostream& out_file, const stf::datatype::DateTime& time){
	out_file << time.dates() << "/" << time.hours() << ":" << time.minutes() << ":" << time.seconds();
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

} /* End of namespace stf::util */
} /* End of namespace stf */