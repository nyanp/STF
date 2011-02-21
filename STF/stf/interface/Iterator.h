/**
 * @file   Iterator.h
 * @brief  STFが提供するイテレータとその抽象インターフェース．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_interface_Iterator_h
#define stf_interface_Iterator_h

#include "../datatype/IAocsData.h"
#include "ITelemetable.h"
#include "../datatype/DateTime.h"

namespace stf {
namespace interface {

//! イテレータの抽象インターフェース．
/*! 
	STFの内部オブジェクト用に用意されるイテレータ群の共通インターフェース．
	すべて片方向のinput iteratorで，かつ返す値はdouble型に限定されている．
	使い方は以下のとおり．
	@code
	Object* obj = new Object();//走査対象
	Iterator it(obj);
	while(!it.end()){
		std::cout << (*it)() << ",";
		++it;
	}
	@endcode
*/
class Iterator {
public:
    virtual void init()  = 0;
	virtual bool end() = 0;
	virtual void operator ++() = 0;
	virtual double operator()() = 0;
	Iterator(){}
};

//! IAocsDataの各要素を取得する入力イテレータ．
/*! */
class DataIterator : public Iterator {
public:
	DataIterator(const datatype::IAocsData* data): index_(0) {
		size_ = data->stream_length();
		data_ = data->to_stream();
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

//! 秒，ミリ秒の順で時刻を取得する入力イテレータ．
/*! */
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

//! 日，時間，分，秒の順でDateTimeを取得する入力イテレータ．
/*! */
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
