/**
 * @file   EulerAngle.cpp
 * @brief  z-y-xオイラー角(rad)．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include <assert.h>

#include "EulerAngle.h"
#include "../util/math.h"

namespace stf { 
namespace datatype {

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
