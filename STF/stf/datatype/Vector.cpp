/**
 * @file   Vector.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "Vector.h"
#include "../util/math.h"
#include "../util/Ostream.h"
namespace stf { 
namespace datatype {

Vector::Vector()
{
	initVector(1,0.0);
}

Vector::Vector(int dim)
{
	initVector(dim,0.0);
}

void Vector::normalize()
{
//単なる物理量のセットなので一般的なnormalizeは実装できない
//ノルムで割るような操作はサブクラスで実装すること
}

double Vector::norm(int n) const
{
	assert((n == 1) || (n == 2));//計算負荷の問題から今は1，2次のノルムしかとらない
	double value = 0.0;
	if(n == 1){
		for(int i = 0; i < this->dimension_; i++)
			value += util::math::abs(value_[i]);
	}else if(n ==2){
		for(int i = 0; i < this->dimension_; i++)
			value += value_[i] * value_[i];
		value = util::math::sqrt(value);
	}
	return value;
}

Vector::Vector(const Vector &rhs)
{

	initVector(rhs.dimension_,0.0);
	for(int i = 0; i < dimension_; i++)
		this->value_[i] = rhs[i];
}

Vector::~Vector()
{
	delete[] this->value_;
}


Vector &Vector::operator=(const Vector &rhs)
{
	assert(rhs.dimension_ == dimension_);
	//delete[] this->value_;
	//initVector(rhs.dimension_,0.0);
	for(int i = 0; i < dimension_; i++)
		this->value_[i] = rhs[i];
	return *this;
}

void Vector::initVector(int dim, double value)
{
    assert(dim > 0);
	this->value_ = new double[dim];
	this->dimension_ = dim;
	assert(this->value_ != 0);//メモリが確保できないときにvalue_==0となって終了
	for(int i = 0; i < dim; i++)
		this->value_[i] = value;
}

bool Vector::operator==(const Vector &rhs) const 
{
    return false;
}

bool Vector::operator!=(const Vector &rhs) const 
{
    return false;
}

Vector &Vector::operator+=(const Vector &rhs)
{
	assert(dimension_ == rhs.dimension_);
	for(int i = 0; i < dimension_; i++)
		value_[i] += rhs[i];
	return *this;
}

Vector &Vector::operator-=(const Vector &rhs)
{
	assert(dimension_ == rhs.dimension_);
	for(int i = 0; i < dimension_ ; i++)
		value_[i] -= rhs[i];
	return *this;
}

Vector &Vector::operator*=(double rhs)
{
	for(int i = 0; i < dimension_ ; i++)
		value_[i] *= rhs;
	return *this;
}

Vector &Vector::operator/=(double rhs)
{
	for(int i = 0; i < dimension_ ; i++)
		value_[i] /= rhs;
	return *this;
}



} /* End of namespace stf::datatype */
} /* End of namespace stf */

