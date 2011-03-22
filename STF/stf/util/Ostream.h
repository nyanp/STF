/**
 * @file   Ostream.h
 * @brief  標準出力のラッパ．
 *
 * coutの定義を変えることで，出力を一括で切ることができる．
 * @code
 * //Ostream<NoOutput> cout; //uncomment this line to disable console output
 * Ostream<std::ostream> cout; //comment this line to disable console output
 * @endcode
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef util_Ostream_h
#define util_Ostream_h
#include<iostream>
#include<fstream>
#include"../datatype/String.h"
#include"../datatype/StaticVector.h"
#include"../datatype/StaticMatrix.h"

namespace stf { 
namespace datatype {
class String;
class Vector;
class Matrix;
class Scalar;
class Time;
class DateTime;
struct OrbitInfo;
struct PositionInfo;
}
}


namespace stf { 
namespace util {

//! 標準出力のラッパ．
/*! 
	@tparam T 出力を転送するストリームクラス．
*/
class Ostream {
public:
	Ostream(){};
	template < typename U>
	Ostream& operator <<(U val){ std::cout << val; return *this; }
	Ostream& operator <<(Ostream&(*f)(Ostream&)){
		return (*f)(*this);
	}
private:

};

class Ofstream {
public:
	Ofstream(const datatype::String& str): stream_(str.to_char()){};
	template < typename U>
	Ofstream& operator <<(U val){ stream_ << val; return *this; }
	inline Ofstream& operator <<(Ofstream&(*f)(Ofstream&)){
		return (*f)(*this);
	}
private:
	std::ofstream stream_;
};

std::ostream &operator << (std::ostream& out_file, const stf::datatype::Vector& vec);
std::ostream &operator << (std::ostream& out_file, const stf::datatype::Matrix& mat);
std::ostream &operator << (std::ostream& out_file, const stf::datatype::Scalar& scalar);
std::ostream &operator << (std::ostream& out_file, const stf::datatype::String& str);
std::ostream &operator << (std::ostream& out_file, const stf::datatype::Time& time);
std::ostream &operator << (std::ostream& out_file, const stf::datatype::DateTime& time);
std::ostream &operator << (std::ostream& out_file, const stf::datatype::OrbitInfo& orbit);
std::ostream &operator << (std::ostream& out_file, const stf::datatype::PositionInfo& pos);

template<int i, int j>
std::ostream &operator << (std::ostream& out_file, const stf::datatype::StaticMatrix<i, j>& mat){
	for(int row = 0; row < i; row++){
		for(int col = 0; col < j; col++){
			out_file.width(6);
			out_file << mat[row][col] << " ";
		}
		out_file << "\n";
	}
	return out_file;
}

template<int dim>
std::ostream &operator << (std::ostream& out_file, const stf::datatype::StaticVector<dim>& vec){
	for(int i = 0; i < dim; i++){
		out_file.width(6);
		out_file << vec[i] << " ";
	}
	return out_file;
}
} /* End of namespace stf::util */
} /* End of namespace stf */

#endif // util_Ostream_h
