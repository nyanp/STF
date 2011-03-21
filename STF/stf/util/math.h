/**
 * @file   math.h
 * @brief  数学系関数のラッパと算術定数の定義．
 *
 * 可搬性を向上させるために，math/cmathを直接読み込まずにこれを使う
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_util_math_h
#define stf_util_math_h

namespace stf {
namespace util {
namespace math { 
	static const double PI = 3.14159265358979323846;//! 円周率
	static const double DEG2RAD = 0.0174532925199432957;//! deg→radの変換係数
	static const double RAD2DEG = 57.295779513082320876;//! rad→degの変換係数
	static const double RAD2ARCSEC = 206264.806247096355;//! rad→秒角の変換係数
	static const double ARCSEC2RAD = 0.000004848136811095359935;//! 秒角→radの変換係数
	static const double MU = 3.9860044E14;//! 地心重力定数
	static const double ALIGN = 1E-10;//! ゼロ判定の閾値
	//! 平方根を求める，cmathのラッパ．
	double sqrt(double s);
	//! 絶対値を求める，cmathのラッパ．
	double abs(double s);
	//! 正弦を求める，cmathのラッパ．
	double Sin(double s);
	//! 余弦を求める，cmathのラッパ．
	double Cos(double s);
	//! sが指定以下であれば0を返す切り下げ判定関数．
	inline double Align(double s, double align = ALIGN){
		return abs(s) < align ? 0 : s;
	}
}
}
}
#endif