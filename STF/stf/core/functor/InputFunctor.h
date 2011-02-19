#ifndef stf_core_functor_InputFunctor_h
#define stf_core_functor_InputFunctor_h
#include "../../util/Ostream.h"
#include "../../RootObject.h"
#include "../../datatype/String.h"
#include "../datapool/Datapool.h"
#include "../../GlobalObject.h"

// コピーコンストラクタと=演算子関数を無効にするマクロ
// これはクラスの private: 宣言の中で使うべきだ。
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

namespace stf {
namespace core {
namespace functor {

template <class T,class Holder>
class Getter_Over {
	typedef const T(Holder::*Getter)(void) const;
public:
	Getter_Over(Holder* obj, Getter getter, T* ref)
		: obj_(obj), getter_(getter), ref_(ref){}
	bool operator()() const {
		if((*obj_.*getter_)() > *ref_){
			return true;
		}
		return false;
	}
private:
	Holder* obj_;
	Getter getter_;//getter
	T* ref_;
};

template <class Holder>
class Getter_Is {
	typedef bool(Holder::*Getter)(void) const;
public:
	Getter_Is(Holder* obj, Getter getter) : obj_(obj), getter_(getter){}
	bool operator()() const {
		return (*obj_.*getter_)();
	}
private:
	Holder* obj_;
	Getter getter_;
};

// DBから取得した最新の値とrefを比較し，一致すればtrueを返す
template <class T>
class Is_Equal  {
public:
	typedef core::datapool::AocsDataPool DB;
	Is_Equal(DB* holder,int datapool_hold_index, const typename T::Hold* ref) : holder_(holder), value_(ref), datapool_hold_index_(datapool_hold_index){

	}
	bool operator()() const {
		if(holder_->get<T>(datapool_hold_index_) == *value_ ){
			return true;
		}
		return false;
	}
	int datapool_hold_index_;
	const typename T::Hold* value_;
	DB* holder_;
private:
	DISALLOW_COPY_AND_ASSIGN(Is_Equal);
};

// DBから取得した最新の値とrefの間のノルムを計算し，distance以下の値であればtrueを返す
template <class T>
class Is_Near  {
public:
	typedef core::datapool::AocsDataPool DB;
	Is_Near(DB* holder,int datapool_hold_index, const typename T::Hold* ref, double distance, int norm) 
		: holder_(holder), value_(ref), datapool_hold_index_(datapool_hold_index), distance_(distance), norm_(norm){

	}
	bool operator()() const {
		if((holder_->get<T>(datapool_hold_index_) - *value_).norm(norm_) < distance_){
			return true;
		}
		return false;
	}
	double distance_;
	int norm_;
	int datapool_hold_index_;
	const typename T::Hold* value_;
	DB* holder_;
private:
	DISALLOW_COPY_AND_ASSIGN(Is_Near);
};

// DBから取得した最新の値のノルムがrefよりおおきければtrueを返す
template <class T>
class Is_Under  {
public:
	typedef core::datapool::AocsDataPool DB;
	Is_Under(DB* holder,int datapool_hold_index, double norm) : holder_(holder), datapool_hold_index_(datapool_hold_index), distance_(norm), norm_(2){

	}
	Is_Under(DB* holder,int datapool_hold_index, int index, double value) : holder_(holder), datapool_hold_index_(datapool_hold_index), distance_(value), norm_(0),index_(index){

	}
	bool operator()() const {
		if(norm_ > 0){//ノルムで評価
			if(holder_->get<T>(datapool_hold_index_).norm(norm_) < distance_ ){
				return true;
			}
		}
		else {//インデックスで評価
			if(holder_->get<T>(datapool_hold_index_)[index_] < distance_ ){
				return true;
			}
		}
		return false;
	}
private:
	DISALLOW_COPY_AND_ASSIGN(Is_Under);
	double distance_;
	int norm_;
	int index_;
	int datapool_hold_index_;
	DB* holder_;
};


// DBから取得した最新の値のノルムがrefよりおおきければtrueを返す
template <class T>
class Is_Over  {
public:
	typedef core::datapool::AocsDataPool DB;
	Is_Over(DB* holder,int datapool_hold_index, double norm) : holder_(holder), datapool_hold_index_(datapool_hold_index), distance_(norm), norm_(2){

	}
	Is_Over(DB* holder,int datapool_hold_index, int index, double value) : holder_(holder), datapool_hold_index_(datapool_hold_index), distance_(value), norm_(0),index_(index){

	}
	bool operator()() const {
		if(norm_ > 0){//ノルムで評価
			if(holder_->get<T>(datapool_hold_index_).norm(norm_) > distance_ ){
				return true;
			}
		}
		else {//インデックスで評価
			if(holder_->get<T>(datapool_hold_index_)[index_] > distance_ ){
				return true;
			}
		}
		return false;
	}
private:
	DISALLOW_COPY_AND_ASSIGN(Is_Over);
	double distance_;
	int norm_;
	int index_;
	int datapool_hold_index_;
	DB* holder_;
};


} /* End of namespace stf::core::functor */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_functor_InputFunctor_h
