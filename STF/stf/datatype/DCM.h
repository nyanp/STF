/**
 * @file   DCM.h
 * @brief  Z-Y-Xの順で回転させる回転行列（DCM）．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef datatype_DCM_h
#define datatype_DCM_h

#include "StaticMatrix.h"

namespace stf { 
namespace datatype {

//! Z-Y-Xの順で回転させる回転行列（DCM）．
/*! */
class DCM : public StaticMatrix<3,3> {
public:
    DCM();
    DCM(const StaticMatrix<3,3> &rhs);
	~DCM(){}
	//! 値を-pi～piに調整する
	virtual void normalize();
};

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // datatype_DCM_h
