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
class DCM : public StaticMatrix<3, 3> {
public:
    DCM(){
		this->value_[0][0] = 1.0;
		this->value_[1][1] = 1.0;
		this->value_[2][2] = 1.0;
	}

	DCM(const DCM& rhs){
		for(int i = 0; i < 3; i++)
		  for(int j = 0; j < 3; j++)
			value_[i][j] = rhs[i][j];
	}

    DCM(const StaticMatrix<3, 3> &rhs){
		for(int i = 0; i < 3; i++)
		  for(int j = 0; j < 3; j++)
			value_[i][j] = rhs[i][j];
	}

	DCM(double m00, double m01, double m02, double m10, double m11, double m12, double m20, double m21, double m22){
		(*this)[0][0] = m00; (*this)[0][1] = m01; (*this)[0][2] = m02;
		(*this)[0][0] = m10; (*this)[0][1] = m11; (*this)[0][2] = m12;
		(*this)[0][0] = m20; (*this)[0][1] = m21; (*this)[0][2] = m22;
	}

	~DCM(){}
	//! 値を-pi～piに調整する
	virtual void normalize();
};

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // datatype_DCM_h
