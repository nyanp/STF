/**
 * @file   Ostream.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef util_Ostream_h
#define util_Ostream_h
#include<iostream>
#include<fstream>
#include"../datatype/String.h"
#include"../datatype/Vector.h"
#include"../datatype/Matrix.h"
#include"../datatype/Scalar.h"
#include"../datatype/Time.h"
#include"../datatype/OrbitInfo.h"
#include"../datatype/StaticVector.h"
#include"../datatype/StaticMatrix.h"

namespace stf { 
namespace util {

template<class T>
class Ostream {
public:
	Ostream(T& stream): stream_(stream){};
	template < typename U>
	Ostream<T>& operator <<(U val){ stream_ << val; return *this; }
	inline Ostream<T>& operator <<(Ostream<T>&(*f)(Ostream<T>&));//マニピュレータ用
private:
	T& stream_;
	Ostream();
	Ostream(const Ostream& rhs);//暗黙のコピーを禁止
	Ostream &operator =(const Ostream& rhs);
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

class NoOutput {
public:
	NoOutput& operator <<(int val){return *this;};
	NoOutput& operator <<(double val){return *this;};
	NoOutput& operator <<(const char* val){return *this;};
private:
};

//extern Ostream<NoOutput> cout;
extern Ostream<std::ostream> cout;
extern Ostream<std::fstream> clog;

} /* End of namespace stf::util */
} /* End of namespace stf */

std::ostream &operator << (std::ostream& out_file, const stf::datatype::Vector& vec);
std::ostream &operator << (std::ostream& out_file, const stf::datatype::Matrix& mat);
std::ostream &operator << (std::ostream& out_file, const stf::datatype::Scalar& scalar);
std::ostream &operator << (std::ostream& out_file, const stf::datatype::String& str);
std::ostream &operator << (std::ostream& out_file, const stf::datatype::Time& time);
std::ostream &operator << (std::ostream& out_file, const stf::datatype::OrbitInfo& orbit);
std::ostream &operator << (std::ostream& out_file, const stf::datatype::PositionInfo& pos);

template<int i, int j>
std::ostream &operator << (std::ostream& out_file, const stf::datatype::StaticMatrix<i,j>& mat){
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
