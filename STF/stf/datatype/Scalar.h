#ifndef stf_datatype_Scalar_h
#define stf_datatype_Scalar_h

#include <assert.h>
#include "IAocsData.h"

namespace stf { 
namespace util {
template <class T>class Ostream;
}
namespace datatype {

///物理量を表すベクトル表現クラス．
class Scalar : public IAocsData {
public:
	Scalar() : value_(0.0){}
	Scalar(double value) : value_(value) {}
	Scalar(const Scalar& rhs) : value_(rhs.value_){}
	Scalar& operator = (const Scalar& rhs) { value_ = rhs.value_; return *this;}
	~Scalar(){}
	virtual void reset(){ value_ = 0; }
	virtual void normalize(){}
	double value () const { return value_; }
	virtual const double* toStream() const { return &value_; }
	virtual int getStreamLength() const { return 1; }
	inline Scalar& operator += (const Scalar& s);
	inline Scalar& operator -= (const Scalar& s);
	inline Scalar& operator *= (const Scalar& s);
	inline Scalar& operator /= (const Scalar& s);
protected:
	double value_;
private:
	friend inline bool operator == (const Scalar& left, const Scalar& right);
	friend inline bool operator != (const Scalar& left, const Scalar& right);
	friend inline bool operator >= (const Scalar& left, const Scalar& right);
	friend inline bool operator <= (const Scalar& left, const Scalar& right);
	friend inline bool operator > (const Scalar& left, const Scalar& right);
	friend inline bool operator < (const Scalar& left, const Scalar& right);
	friend inline Scalar operator + (const Scalar& s);
	friend inline Scalar operator - (const Scalar& s);
	friend inline Scalar operator + (const Scalar& s1,const Scalar& s2);
	friend inline Scalar operator - (const Scalar& s1,const Scalar& s2);
	friend inline Scalar operator * (const Scalar& s1,const Scalar& s2);
	friend inline Scalar operator / (const Scalar& s1,const Scalar& s2);
	friend inline Scalar operator * (const Scalar& s,double d);
	friend inline Scalar operator * (double d,const Scalar& s);
	friend inline Scalar operator / (const Scalar& s,double d);
	template<class T>friend class stf::util::Ostream;
};

Scalar& Scalar::operator += (const Scalar& s){
	this->value_ += s.value_;
	return *this;
}

Scalar& Scalar::operator -= (const Scalar& s){
	this->value_ += s.value_;
	return *this;
}

Scalar& Scalar::operator *= (const Scalar& s){
	this->value_ += s.value_;
	return *this;
}

Scalar& Scalar::operator /= (const Scalar& s){
	this->value_ += s.value_;
	return *this;
}
inline Scalar operator - (const Scalar& s){
	Scalar temp = s;
	temp.value_ *= -1;
	return temp;
}

inline Scalar operator + (const Scalar& s){
	Scalar temp = s;
	return temp;
}

inline Scalar operator + (const Scalar& s1, const Scalar& s2){
	Scalar temp = s1;
	temp.value_ += s2.value_;
	return temp;
}

inline Scalar operator - (const Scalar& s1, const Scalar& s2){
	Scalar temp = s1;
	temp.value_ -= s2.value_;
	return temp;
}

inline Scalar operator * (const Scalar& s1, const Scalar& s2){
	Scalar temp = s1;
	temp.value_ *= s2.value_;
	return temp;
}

inline Scalar operator * (const Scalar& s,double d){
	Scalar temp = s;
	temp.value_ *= d;
	return temp;
}

inline Scalar operator * (double d,const Scalar& s){
	Scalar temp = s;
	temp.value_ *= d;
	return temp;
}

inline Scalar operator / (const Scalar& s,double d){
	Scalar temp = s;
	temp.value_ /= d;
	return temp;
}

inline Scalar operator / (const Scalar& s1, const Scalar& s2){
	Scalar temp = s1;
	temp.value_ /= s2.value_;
	return temp;
}

inline bool operator == (const Scalar& left, const Scalar& right){
	if(left.value_ == right.value_) return true;
	return false;
}

inline bool operator != (const Scalar& left, const Scalar& right){
	return !(left == right);
}

inline bool operator >= (const Scalar& left, const Scalar& right){
	if(left.value_ >= right.value_) return true;
	return false;
}

inline bool operator <= (const Scalar& left, const Scalar& right){
	if(left.value_ <= right.value_) return true;
	return false;
}

inline bool operator > (const Scalar& left, const Scalar& right){
	return !(left <= right);
}

inline bool operator < (const Scalar& left, const Scalar& right){
	return !(left >= right);
}


} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_Scalar_h
