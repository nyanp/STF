/**
 * @file   StaticVector.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_datatype_StaticVector_h
#define stf_datatype_StaticVector_h
#include "assert.h"
#include "IAocsData.h"
#include "Vector.h"
#include "../util/math.h"

namespace stf { 
namespace datatype {

template<int dim>
class StaticVector : public IAocsData {
public:
	StaticVector(){ for ( int i = 0; i < dim; i++ ) value_[i] = 0.0; }
	StaticVector(const StaticVector<dim>& rhs);
	StaticVector(const Vector& rhs);
	~StaticVector(){}
	virtual void normalize();
	virtual void reset(){ for ( int i = 0; i < dim; i++ ) value_[i] = 0.0; }
	virtual const double* to_stream() const { return value_; }
	virtual int stream_length() const { return dim; }
	int dimension( void ) const { return dim; };
	virtual double norm(int n) const;
	inline double max() const;
	inline double min() const;
    inline const double &operator[](int index) const ;
    inline double &operator[](int index) ;
    inline StaticVector<dim> &operator=(const StaticVector<dim> &rhs);
    inline StaticVector<dim> &operator=(const Vector &rhs);
    bool operator==(const StaticVector<dim> &rhs) const ;
    bool operator!=(const StaticVector<dim> &rhs) const ;
    inline StaticVector<dim> &operator+=(const StaticVector<dim> &rhs);
    inline StaticVector<dim> &operator-=(const StaticVector<dim> &rhs);
    inline StaticVector<dim> &operator*=(double rhs);
    inline StaticVector<dim> &operator/=(double rhs);
protected:
	double value_[dim];
private:
	friend inline const Matrix operator * (const Matrix&, const Matrix&);
};

template<int dim>
StaticVector<dim>::StaticVector(const StaticVector<dim> &rhs)
{
	for(int i = 0; i < dim; i++)
		this->value_[i] = rhs[i];
}

template<int dim>
StaticVector<dim>::StaticVector(const Vector &rhs)
{
	assert(rhs.dimension() == dim);
	for(int i = 0; i < dim; i++)
		this->value_[i] = rhs[i];
}

template<int dim>
void StaticVector<dim>::normalize()
{
//単なる物理量のセットなので一般的なnormalizeは実装できない
//ノルムで割るような操作はサブクラスで実装すること
}

template<int dim>
double StaticVector<dim>::norm(int n) const
{
	assert((n == 1) || (n == 2));//計算負荷の問題から今は1，2次のノルムしかとらない
	double value = 0.0;
	if(n == 1){
		for(int i = 0; i < dim; i++)
			value += util::math::abs(value_[i]);
	}else if(n ==2){
		for(int i = 0; i < dim; i++)
			value += value_[i] * value_[i];
		value = util::math::sqrt(value);
	}
	return value;
}

template<int dim>
StaticVector<dim> &StaticVector<dim>::operator=(const StaticVector<dim> &rhs)
{
	for(int i = 0; i < dim; i++)
		this->value_[i] = rhs[i];
	return *this;
}

template<int dim>
StaticVector<dim> &StaticVector<dim>::operator=(const Vector &rhs)
{
	assert(dim == rhs.dimension());
	for(int i = 0; i < dim; i++)
		this->value_[i] = rhs[i];
	return *this;
}

template<int dim>
bool StaticVector<dim>::operator==(const StaticVector<dim> &rhs) const 
{
	for(int i = 0; i < dim; i++)
		if(this->value_[i] != rhs[i]) return false;
    return true;
}

template<int dim>
bool StaticVector<dim>::operator!=(const StaticVector<dim> &rhs) const 
{
    return !(*this == rhs);
}

template<int dim>
StaticVector<dim> &StaticVector<dim>::operator+=(const StaticVector<dim> &rhs)
{
	for(int i = 0; i < dim; i++)
		value_[i] += rhs[i];
	return *this;
}

template<int dim>
StaticVector<dim> &StaticVector<dim>::operator-=(const StaticVector<dim> &rhs)
{
	for(int i = 0; i < dim ; i++)
		value_[i] -= rhs[i];
	return *this;
}

template<int dim>
StaticVector<dim> &StaticVector<dim>::operator*=(double rhs)
{
	for(int i = 0; i < dim ; i++)
		value_[i] *= rhs;
	return *this;
}

template<int dim>
StaticVector<dim> &StaticVector<dim>::operator/=(double rhs)
{
	for(int i = 0; i < dim ; i++)
		value_[i] /= rhs;
	return *this;
}

////////////////////////////////
//  Inline Methods for StaticVector<dim> //
////////////////////////////////

template<int dim>
inline StaticVector<dim> operator + (const StaticVector<dim>& v){
	StaticVector<dim> temp = v;
	return temp;
}

template<int dim>
inline StaticVector<dim> operator - (const StaticVector<dim>& v){
	StaticVector<dim> temp = v;
	for(int i = 0; i < dim; i++)
		temp[i] = -temp[i];
	return temp;
}

template<int dim>
inline const double &StaticVector<dim>::operator[](int index) const 
{
	return this->value_[index];
}

template<int dim>
inline double &StaticVector<dim>::operator[](int index) 
{
	return this->value_[index];
}

template<int dim>
inline double StaticVector<dim>::max() const
{
	double result = 0.0;
	for(int i = 0; i < dim; i++)
		if(value_[i] > result) result = value_[i];
	return result;
}

template<int dim>
inline double StaticVector<dim>::min() const
{
	double result = 0.0;
	for(int i = 0; i < dim; i++)
		if(value_[i] < result) result = value_[i];
	return result;
}

template<int dim>
inline const StaticVector<dim> operator + (const StaticVector<dim>& vec1, const StaticVector<dim>& vec2){
	StaticVector<dim> temp = vec1;
	temp += vec2;
	return temp;
}

template<int dim>
inline const StaticVector<dim> operator - (const StaticVector<dim>& vec1, const StaticVector<dim>& vec2){
	StaticVector<dim> temp = vec1;
	temp -= vec2;
	return temp;
}

// ベクトルの内積
template<int dim>
inline const double operator * (const StaticVector<dim>& vec1, const StaticVector<dim>& vec2){
	double value = 0.0;
	for(int i = 0; i < dim; i++)
		value += vec1[i] * vec2[i];
	return value;
}

// ベクトルを右から定数倍
template<int dim>
inline const StaticVector<dim> operator * (const StaticVector<dim>& vec, double factor){
	StaticVector<dim> temp = vec;
	return temp *= factor;
}

// ベクトルを左から定数倍
template<int dim>
inline const StaticVector<dim> operator * (double factor, const StaticVector<dim>& vec){
	return vec * factor;
}

inline const StaticVector<3> operator %(const StaticVector<3>& vec1,const StaticVector<3>& vec2){
	StaticVector<3> temp;
	temp[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
	temp[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
	temp[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
	return temp;
}

inline double operator %(const StaticVector<2>& vec1,const StaticVector<2>& vec2){
	return vec1[0] * vec2[1] - vec1[1] * vec2[0];
}

// ベクトルを定数で除算
template<int dim>
inline const StaticVector<dim> operator / (const StaticVector<dim>& vec, double factor){
	StaticVector<dim> temp = vec;
	return temp /= factor;
}

///////////////////
// Dummy Operators

template<int dim>
inline bool operator > (const StaticVector<dim>& vec1,const StaticVector<dim>& vec2){
	assert(0); return false;
}

template<int dim>
inline bool operator < (const StaticVector<dim>& vec1,const StaticVector<dim>& vec2){
	assert(0); return false;
}

template<int dim>
inline bool operator >= (const StaticVector<dim>& vec1,const StaticVector<dim>& vec2){
	assert(0); return false;
}

template<int dim>
inline bool operator <= (const StaticVector<dim>& vec1,const StaticVector<dim>& vec2){
	assert(0); return false;
}


} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_StaticVector_h
