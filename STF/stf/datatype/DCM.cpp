#include <assert.h>

#include "DCM.h"
#include "Matrix.h"

namespace stf { 
namespace datatype {

DCM::DCM()
: Matrix(3,3)
{
	this->value_[0][0] = 1.0;
	this->value_[1][1] = 1.0;
	this->value_[2][2] = 1.0;
}

DCM::DCM(const Matrix &rhs)
: Matrix(3,3)
{
	assert(rhs.cols_ == 3 && rhs.rows_ == 3);
	for(int i = 0; i < rows_; i++)
		for(int j = 0; j < cols_; j++)
			value_[i][j] = rhs[i][j];
}

DCM::~DCM()
{
}

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
