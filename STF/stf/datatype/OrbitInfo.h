/**
 * @file   OrbitInfo.h
 * @brief  軌道情報関係の量を表す
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_datatype_OrbitInfo_h
#define stf_datatype_OrbitInfo_h
#include "StaticVector.h"
#include "../util/math.h"

namespace stf { 
namespace datatype {

//! 軌道6要素を保持するクラス．サイズ肥大化を避けるため，主要な計算はOrbitImplのstaticなメソッドに投げることで行う
/*!  */
struct OrbitInfo {
	OrbitInfo() : a(0), e(0), M(0), i(0), Omega(0), omega(0), n(0) {}
	OrbitInfo(double a, double e, double M, double i, double Omega, double omega)
		: a(a), e(e), M(M), i(i), Omega(Omega), omega(omega)
	{
		n = sqrt( util::math::MU / (a * a * a) ); 
	}
	double a;//長半径(m)
	double e;//離心率
	double M;//平均近点離角
	double i;//軌道傾斜角(rad)
	double Omega;//昇交点赤経(rad)
	double omega;//近地点引数
	double n;
};

//! 衛星座標を緯度経度高度の形式で保持するクラス．
/*!  */
struct Geo  {
	Geo() : latitude(0), longitude(0), altitude(0) {}
	double latitude;//緯度(rad)
	double longitude;//経度(rad)
	double altitude;//高度(m)
};

//! 衛星座標を地心慣性座標系における位置と速度の6次元ベクトルで保持するクラス．
/*!  */
struct PositionInfo  {
	PositionInfo() {}
	StaticVector<3> position;
	StaticVector<3> velocity;
};

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_OrbitInfo_h
