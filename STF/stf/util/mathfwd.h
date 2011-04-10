/**
 * @file   mathfwd.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.04.10
 */
#ifndef stf_util_mathfwd_h
#define stf_util_mathfwd_h

namespace stf {
namespace datatype {
class Matrix;
}
namespace util {

namespace math {
	//! 平方根を求める，cmathのラッパ．
	double sqrt(double s);
	//! 絶対値を求める，cmathのラッパ．
	double abs(double s);
	//! 正弦を求める，cmathのラッパ．
	double Sin(double s);
	//! 余弦を求める，cmathのラッパ．
	double Cos(double s);
	
	//! 行列の指数をn次のマクローリン展開まで計算して返す関数．
	datatype::Matrix exp(const datatype::Matrix& m, int n);
	
	//! 行列の指数を4次のマクローリン展開まで計算して返す関数．
	datatype::Matrix exp(const datatype::Matrix& m);
}


}
}


#endif