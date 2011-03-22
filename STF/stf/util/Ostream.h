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
#include"../datatype/StaticVector.h"
#include"../datatype/StaticMatrix.h"
#include"../Config.h"

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

namespace util {

//! 標準出力のラッパ．
/*! 
	@tparam T 出力を転送するストリームクラス．
*/
template<class T>
class Ostream {
public:
	typedef typename T::OutputStream Os;
	Ostream(Os& stream): stream_(stream){};
	template < typename U>
	Ostream<T>& operator <<(U val){ stream_ << val; return *this; }
	inline Ostream<T>& operator <<(Ostream<T>&(*f)(Ostream<T>&));//マニピュレータ用
private:
	Os& stream_;
};

template<class T>
inline Ostream<T>& Ostream<T>::operator <<(Ostream<T>&(*f)(Ostream<T>&)){
	return (*f)(*this);
}

template<class T>
Ostream<T>& endl(Ostream<T>& os){
	os << "\n";//TBD
	return os;
}

template<class T>
class Ofstream {
public:
	typedef typename T::OutputFileStream Ofs;
	Ofstream(Ofs& stream): stream_(stream){};
	template < typename U>
	Ofstream<T>& operator <<(U val){ stream_ << val; return *this; }
	inline Ofstream<T>& operator <<(Ofstream<T>&(*f)(Ofstream<T>&));//マニピュレータ用
private:
	Ofs& stream_;
};

template<class T>
inline Ofstream<T>& Ofstream<T>::operator <<(Ofstream<T>&(*f)(Ofstream<T>&)){
	return (*f)(*this);
}

template<class T>
Ofstream<T>& endl(Ofstream<T>& os){
	os << "\n";//TBD
	return os;
}

class NoOutput {
public:
	NoOutput& operator <<(int val){return *this;};
	NoOutput& operator <<(double val){return *this;};
	NoOutput& operator <<(const char* val){return *this;};
private:
};

//extern Ostream<NoOutput> cout;
extern Ostream<ENV> cout;
extern Ofstream<ENV> clog;

} /* End of namespace stf::util */
} /* End of namespace stf */

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



#endif // util_Ostream_h
