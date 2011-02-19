#ifndef stf_datatype_TypeConverter_h
#define stf_datatype_TypeConverter_h

#include "DCM.h"
#include "EulerAngle.h"
#include "Quaternion.h"
#include "StaticVector.h"
#include "OrbitInfo.h"

namespace stf {
namespace datatype {

///単位や姿勢表現の相互変換を行うユーティリティ．
///datatypeモジュール間の相互結合を防ぐためにこのクラスにstaticメソッドとして変換式をまとめている.ArgoUMLにinlineを多重定義するバグがあるので今のところすべて関数呼び出し
class TypeConverter {
public:
    static Quaternion toQuaternion(const DCM &dcm);
    static Quaternion toQuaternion(const EulerAngle &euler_angle);
    static DCM toDCM(const Quaternion &q);
    static DCM toDCM(const EulerAngle &euler_angle);
    static EulerAngle toEulerAngle(const DCM &dcm);
    static EulerAngle toEulerAngle(const Quaternion &q);
    static DCM toDCM(double roll_deg, double pitch_deg, double yaw_deg);
	static StaticVector<2> toPolar(const StaticVector<3> &vec);
	static StaticVector<3> toRectangular(const StaticVector<2> &vec);
	static OrbitInfo toOrbitInfo(const PositionInfo &pos);
	static PositionInfo toPositionInfo(const OrbitInfo &orb);
	//static Geo toGeo(const PositionInfo &pos);
	//static Geo toGeo(const OrbitInfo &orb);
	
};

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_TypeConverter_h
