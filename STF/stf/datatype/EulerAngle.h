/**
 * @file   EulerAngle.h
 * @brief  z-y-xオイラー角(rad)．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_datatype_EulerAngle_h
#define stf_datatype_EulerAngle_h

#include "StaticVector.h"

namespace stf { 
namespace datatype {

//! 3-2-1(z-y-x)Euler Angleを表現する．単位rad
/*! */
class EulerAngle : public StaticVector<3> {
public:
	EulerAngle() {}
    EulerAngle(const StaticVector<3> &rhs);
	~EulerAngle(){}
	//! 行列式を１に調整する
	virtual void normalize();
};

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_EulerAngle_h
