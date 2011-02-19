#include <assert.h>

#include "EulerAngle.h"
#include "../util/math.h"

namespace stf { 
namespace datatype {

EulerAngle::EulerAngle(const StaticVector<3> &rhs)
{
	for(int i = 0; i < 3; i++)
		(*this)[i] = rhs[i];
}

void EulerAngle::normalize(){
	for(int i = 0; i < this->dimension(); i++){
		while(this->value_[i] > util::math::PI)
			this->value_[i] -= 2 * util::math::PI;
			
		while(this->value_[i] < -util::math::PI)
			this->value_[i] += 2 * util::math::PI;
	}
}

} /* End of namespace stf::datatype */
} /* End of namespace stf */
