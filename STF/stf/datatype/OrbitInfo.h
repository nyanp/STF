/**
 * @file   OrbitInfo.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_datatype_OrbitInfo_h
#define stf_datatype_OrbitInfo_h
#include "assert.h"
#include "IAocsData.h"
#include "StaticVector.h"
#include "../util/math.h"
namespace stf { 
namespace datatype {

//軌道6要素を保持するクラス．サイズ肥大化を避けるため，主要な計算はOrbitImplのstaticなメソッドに投げることで行う
struct OrbitInfo : public IAocsData {
public:
	OrbitInfo() {}
	OrbitInfo(double a, double e, double M, double i, double Omega, double omega)
		: a(a), e(e), M(M), i(i), Omega(Omega), omega(omega)
	{
		n = sqrt( util::math::MU / (a * a * a) ); 
	}
	~OrbitInfo(){}
	virtual void normalize(){}
	virtual void reset(){};
	virtual const double* toStream() const { return 0; };
	virtual int getStreamLength() const { return 7; };
	double a;//長半径(m)
	double e;//離心率
	double M;//平均近点離角
	double i;//軌道傾斜角(rad)
	double Omega;//昇交点赤経(rad)
	double omega;//近地点引数
	double n;
private:

};

struct Geo : public IAocsData {
	virtual void normalize(){}
	virtual void reset(){};
	virtual const int* serialize() const { return 0;}
	double latitude;//緯度(rad)
	double longitude;//経度(rad)
	double altitude;//高度(m)
};

struct PositionInfo : public IAocsData {
public:
	PositionInfo() {}
	~PositionInfo() {}
	virtual void normalize(){}
	virtual void reset(){};
	virtual const double* toStream() const { return 0; };
	virtual int getStreamLength() const { return 7; };
	StaticVector<3> position;//地心慣性座標系における衛星の位置．
	StaticVector<3> velocity;//
private:

};

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_OrbitInfo_h
