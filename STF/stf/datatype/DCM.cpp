/**
 * @file   DCM.cpp
 * @brief  Z-Y-Xの順で回転させる回転行列（DCM）．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include <assert.h>
#include "DCM.h"

namespace stf { 
namespace datatype {

void DCM::normalize()
{
    double det = (*this)[0][0] * (*this)[1][1] * (*this)[2][2]
				+(*this)[0][1] * (*this)[1][2] * (*this)[2][0]
				+(*this)[0][2] * (*this)[1][0] * (*this)[2][1]
				-(*this)[0][2] * (*this)[1][1] * (*this)[2][0]
				-(*this)[0][1] * (*this)[1][0] * (*this)[2][2]
				-(*this)[0][0] * (*this)[1][2] * (*this)[2][1];
	for(int i = 0; i < 3; i++)
	  for(int j = 0; j < 3; j++)
		(*this)[i][j] /= det;
}

} /* End of namespace stf::datatype */
} /* End of namespace stf */
