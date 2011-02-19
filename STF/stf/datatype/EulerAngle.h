/**
 * @file   EulerAngle.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_datatype_EulerAngle_h
#define stf_datatype_EulerAngle_h

#include "StaticVector.h"


namespace stf { 
namespace datatype {
///z-y-x座標系におけるオイラー角(rad)．ジンバルロックに注意して使用すること．
class EulerAngle : public StaticVector<3> {
public:
	EulerAngle() {}//: Vector(3) {}
    EulerAngle(const StaticVector<3> &rhs);
	~EulerAngle(){}
	// virtual method for IAocsData
	virtual void normalize();// -180 - 180に調整
};

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_EulerAngle_h
