/**
 * @file   Vector.h
 * @brief  可変要素数のベクトル演算を行うクラス．STFではStaticVectorが推奨される
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_datatype_Vector_h
#define stf_datatype_Vector_h

#include "../util/stfassert.h"
#include "IAocsData.h"

namespace stf { 
namespace util {
template <class T>class Ostream;
}
namespace datatype {
//! 可変要素数のベクトル演算を行う．
/*! メモリの動的確保を行うため，STFではシステム初期化以外のタイミングでの使用が推奨されない．通常はStaticVectorを使うこと */
class Vector : public IAocsData {
public:
    Vector();
    explicit Vector(int dim);
	Vector(const Vector &rhs);
    virtual ~Vector();
    void initVector(int dim, double value);
    int dimension() const { return dimension_; };
	virtual double norm(int n) const;
	inline double max() const;
	inline double min() const;
    inline double &operator[](int index) const ;
    Vector &operator=(const Vector &rhs);
    bool operator==(const Vector &rhs) const ;
    bool operator!=(const Vector &rhs) const ;
    Vector &operator+=(const Vector &rhs);
    Vector &operator-=(const Vector &rhs);
    Vector &operator*=(double rhs);
    Vector &operator/=(double rhs);
	virtual const double* to_stream() const{ return value_; }
	virtual int stream_length() const { return dimension_; }
	virtual void normalize();
	virtual void reset(){ for(int i = 0; i < dimension_; i++) this->value_[i] = 0.0; }
protected:
    double *value_;
	int dimension_;
private:
	friend class Matrix;
	template<class T>friend class stf::util::Ostream;
	friend inline const Matrix operator * (const Matrix&, const Matrix&);
	friend inline const Vector operator +(const Vector&, const Vector&);
	friend inline const Vector operator -(const Vector&, const Vector&);
	friend inline const double operator *(const Vector&, const Vector&);
	friend inline const Vector operator *(double, const Vector&);
	friend inline const Vector operator *(const Vector&, double);
	friend inline const Vector operator %(const Vector&, const Vector&);
	friend inline const Vector operator /(const Vector&, double);
	friend inline const Vector operator * (const Matrix&, const Vector&); 
	friend inline bool operator >= (const Vector& left, const Vector& right);
	friend inline bool operator <= (const Vector& left, const Vector& right);
	friend inline bool operator > (const Vector& left, const Vector& right);
	friend inline bool operator < (const Vector& left, const Vector& right);
	friend inline Vector operator - (const Vector& s);
	friend inline Vector operator + (const Vector& s);
};

////////////////////////////////
//  Inline Methods for Vector //
////////////////////////////////

inline Vector operator + (const Vector& v){
	Vector temp = v;
	return temp;
}

inline Vector operator - (const Vector& v){
	Vector temp = v;
	for(int i = 0; i < v.dimension_; i++)
		temp[i] = -temp[i];
	return temp;
}

inline double &Vector::operator[](int index) const 
{
	return this->value_[index];
}

inline double Vector::max() const
{
	double result = 0.0;
	for(int i = 0; i < dimension_; i++)
		if(value_[i] > result) result = value_[i];
	return result;
}

inline double Vector::min() const
{
	double result = 0.0;
	for(int i = 0; i < dimension_; i++)
		if(value_[i] < result) result = value_[i];
	return result;
}

inline const Vector operator + (const Vector& vec1, const Vector& vec2){
	assert(vec1.dimension_ == vec2.dimension_);
	Vector temp = vec1;
	temp += vec2;
	return temp;
}

inline const Vector operator - (const Vector& vec1, const Vector& vec2){
	assert(vec1.dimension_ == vec2.dimension_);
	Vector temp = vec1;
	temp -= vec2;
	return temp;
}

// ベクトルの内積
inline const double operator * (const Vector& vec1, const Vector& vec2){
	assert(vec1.dimension_ == vec2.dimension_);
	double value = 0.0;
	for(int i = 0; i < vec1.dimension_; i++)
		value += vec1[i] * vec2[i];
	return value;
}

// ベクトルを右から定数倍
inline const Vector operator * (const Vector& vec, double factor){
	Vector temp = vec;
	return temp *= factor;
}

// ベクトルを左から定数倍
inline const Vector operator * (double factor, const Vector& vec){
	return vec * factor;
}

// ベクトルの外積．2または3次元ベクトルの場合のみ有効
inline const Vector operator %(const Vector& vec1, const Vector& vec2){
	assert(vec1.dimension_ == vec2.dimension_);
	assert(vec1.dimension_ == 2 || vec1.dimension_ == 3);
	if(vec1.dimension_ == 2){
		Vector temp(1);
		temp[0] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
		return temp;
	}else{
		Vector temp(3);
		temp[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
		temp[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
		temp[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
		return temp;
	}
}

// ベクトルを定数で除算
inline const Vector operator / (const Vector& vec, double factor){
	Vector temp = vec;
	return temp /= factor;
}

inline bool operator >= (const Vector& left, const Vector& right){
	assert(0);
	if(left.value_ >= right.value_) return true;
	return false;
}

inline bool operator <= (const Vector& left, const Vector& right){
	assert(0);
	if(left.value_ <= right.value_) return true;
	return false;
}

inline bool operator > (const Vector& left, const Vector& right){
	assert(0);
	return !(left <= right);
}

inline bool operator < (const Vector& left, const Vector& right){
	assert(0);
	return !(left >= right);
}

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_Vector_h
