/**
 * @file   Quaternion.cpp
 * @brief  4元数を表現するクラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "../util/stfassert.h"
#include "../util/math.h"
#include "Quaternion.h"

namespace stf { 
namespace datatype {

void Quaternion::normalize()
{
	double norm = util::math::sqrt(value_[0] * value_[0] + value_[1] * value_[1]
	            + value_[2] * value_[2] + value_[3] * value_[3]);
	for(int i = 0;i < 4; i++)	
		value_[i] /= norm;
}

double Quaternion::norm(int n) const 
{
	assert((n == 1) || (n == 2));//計算負荷の問題から今は1，2次のノルムしかとらない
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
