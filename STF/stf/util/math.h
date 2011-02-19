/**
 * @file   math.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_util_math_h
#define stf_util_math_h
//#include "math/Exp.h"
#include "math/Rand.h"
//#include "math/RungeKutta.h"

//数学系関数のラッパ．
//環境依存をなるべく回避するため，math/cmathを直接読み込まずにこれを使う
namespace stf {
namespace util {
namespace math { 
	static const double PI = 3.14159265358979323846;
	static const double DEG2RAD = 0.0174532925199432957;
	static const double RAD2DEG = 57.295779513082320876;
	static const double RAD2ARCSEC = 206264.806247096355;
	static const double ARCSEC2RAD = 0.000004848136811095359935;
	static const double MU = 3.9860044E14;//地心重力定数
	static const double ALIGN = 1E-10;
	double sqrt(double s);
	double abs(double s);
	double Sin(double s);
	double Cos(double s);
	double Align(double s,double align = ALIGN);
}
}
}
#endif