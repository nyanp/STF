/**
 * @file   Magnetic.cpp
 * @brief  磁気関係の物理量を表す
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include <assert.h>
#include "../util/math.h"
#include "Magnetic.h"

namespace stf { 
namespace datatype {

MagneticField::MagneticField(double m0, double m1, double m2)
{
    this->value_[0] = m0;
    this->value_[1] = m1;
    this->value_[2] = m2;
}

MagneticField::MagneticField(const StaticVector<3> &rhs)
{
	for(int i = 0; i < 3; i++)
		(*this)[i] = rhs[i];
}

MagneticField::MagneticField(const MagneticField &rhs)
{
	for(int i = 0; i < 3; i++)
		(*this)[i] = rhs[i];
}

MagneticMoment::MagneticMoment(double m0, double m1, double m2)
{
    this->value_[0] = m0;
    this->value_[1] = m1;
    this->value_[2] = m2;
}

MagneticMoment::MagneticMoment(const StaticVector<3> &rhs)
{
	for(int i = 0; i < 3; i++)
		(*this)[i] = rhs[i];
}

MagneticMoment::MagneticMoment(const MagneticMoment &rhs)
{
	for(int i = 0; i < 3; i++)
		(*this)[i] = rhs[i];
}

} /* End of namespace stf::datatype */
} /* End of namespace stf */
