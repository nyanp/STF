#ifndef stf_interface_Iterator_h
#define stf_interface_Iterator_h

#include "../datatype/IAocsData.h"
#include "../datatype/ITelemetable.h"
#include "../datatype/DateTime.h"

namespace stf {
namespace interface {
//CPUによる電源のオンオフ制御が可能なコンポーネントに対するインターフェース．
class Iterator {
public:
    virtual void init()  = 0;
	virtual bool end() = 0;
	virtual void operator ++() = 0;
	virtual double operator()() = 0;
	Iterator(){}
protected:

};


class DataIterator : public Iterator {
public:
	DataIterator(const datatype::IAocsData* data): index_(0) {
		size_ = data->getStreamLength();
		data_ = data->toStream();
	}
	virtual void init(){ index_ = 0; }
	virtual bool end(){ if(index_ == size_) return true; return false;}
	virtual void operator ++() { index_ ++; }
	virtual double operator()() { return (data_[index_]); }
private:
	const double* data_;
	int index_;
	int size_;
};

class TimeIterator : public Iterator {
public:
	TimeIterator(const datatype::Time* t): index_(0), t_(t) {}
	virtual void init(){ index_ = 0; }
	virtual bool end(){ if(index_ == SIZE) return true; return false;}
	virtual void operator ++() { index_ ++; }
	virtual double operator()() { 
		assert(index_ < 2);
		if(index_ == 0) return t_->seconds();
		return t_->milliseconds();
	}
private:
	const datatype::Time* t_;
	int index_;
	static const int SIZE = 2;
};

class DateTimeIterator : public Iterator {
public:
	DateTimeIterator(const datatype::DateTime* t): index_(0), t_(t) {}
	virtual void init(){ index_ = 0; }
	virtual bool end(){ if(index_ == SIZE) return true; return false;}
	virtual void operator ++() { index_ ++; }
	virtual double operator()() { 
		assert(index_ < 4);
		switch(index_){
		case 0:
			return t_->dates();
		case 1:
			return t_->hours();
		case 2:
			return t_->minutes();
		case 3:
			return t_->seconds();
		default:
			assert(0);
			break;
		}
		return 0;
	}
private:
	const datatype::DateTime* t_;
	int index_;
	static const int SIZE = 4;
};


} /* End of namespace stf::interface */
} /* End of namespace stf */

#endif // stf_core_interface_Iterator_h
