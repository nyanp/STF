#include <assert.h>
#include "../util/math.h"
#include "Quaternion.h"

namespace stf { 
namespace datatype {

Quaternion::Quaternion(double q0,double q1, double q2, double q3) //: Vector(4)
{
    this->value_[0] = q0;
    this->value_[1] = q1;
    this->value_[2] = q2;
    this->value_[3] = q3;
}

Quaternion::Quaternion() //: Vector(4)
{
	this->value_[0] = 1.0;
}

Quaternion::Quaternion(const StaticVector<4> &rhs) //: Vector(4)
{
	//assert(rhs.dimension() == 4);
	for(int i = 0; i < 4; i++)
		(*this)[i] = rhs[i];
}

Quaternion::Quaternion(const Quaternion &rhs)// : Vector(4)
{
	for(int i = 0; i < 4; i++)
		(*this)[i] = rhs[i];
}

Quaternion Quaternion::conjugate() const 
{
	Quaternion q;
	q[0] = (*this)[0];  q[1] = -(*this)[1];
	q[2] = -(*this)[2]; q[3] = -(*this)[3];
	return q;
}

void Quaternion::normalize()
{
	double norm = util::math::sqrt(value_[0] * value_[0] + value_[1] * value_[1]
	            + value_[2] * value_[2] + value_[3] * value_[3]);
	for(int i = 0;i < 4; i++)	
		value_[i] /= norm;
}

double Quaternion::norm(int n) const 
{
	assert((n == 1) || (n == 2));//ŒvŽZ•‰‰×‚Ì–â‘è‚©‚ç¡‚Í1C2ŽŸ‚Ìƒmƒ‹ƒ€‚µ‚©‚Æ‚ç‚È‚¢
	double value = 0.0;
	if(n == 1){
		for(int i = 0; i < 4; i++)
			value += util::math::abs(value_[i]);
	}else if(n ==2){
		for(int i = 0; i < 4; i++)
			value += value_[i] * value_[i];
		value = util::math::sqrt(value);
	}
	return value;
}


} /* End of namespace stf::datatype */
} /* End of namespace stf */
