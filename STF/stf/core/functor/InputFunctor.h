/**
 * @file   InputFunctor.h
 * @brief  入力ファンクタ群．STFではFunctorのコンストラクタに渡して使用される
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_functor_InputFunctor_h
#define stf_core_functor_InputFunctor_h

#include "../../Macros.h"
#include "../../RootObject.h"
#include "../datapool/Datapool.h"

namespace stf {
namespace core {
namespace functor {

//! メンバ関数の戻り値を評価し，基準値以上であればtrueを返す入力ファンクタ．
/*! 
	@tparam T      メンバ関数の戻り値型．operator > が実装されている必要がある．
	@tparam Holder メンバ関数を保持するクラス．
*/
template <class T, class Holder>
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
	DISALLOW_COPY_AND_ASSIGN_2(Getter_Over, T, Holder);
	Holder* obj_;
	Getter getter_;
	T* ref_;
};

//! bool型の戻り値を持つメンバ関数を起動し，その戻り値を返す入力ファンクタ．
/*! 
	@tparam Holder メンバ関数を保持するクラス．
*/
template <class Holder>
class Getter_Is {
	typedef bool(Holder::*Getter)(void) const;
public:
	Getter_Is(Holder* obj, Getter getter) : obj_(obj), getter_(getter){}
	bool operator()() const {
		return (*obj_.*getter_)();
	}
private:
	DISALLOW_COPY_AND_ASSIGN_1(Getter_Is, Holder);
	Holder* obj_;
	Getter getter_;
};

//! AocsDataPoolの指定した列から最新のデータを取得し，基準値に一致すればtrueを返す入力ファンクタ．
/*! 
	@tparam T AocsDataPoolに収められているデータの型．operator == が実装されている必要がある．
*/
template <class T>
class Is_Equal  {
public:
	typedef core::datapool::AocsDataPool DB;
	//! コンストラクタ．
	/*!
		@param holder              データプールのインスタンス．
		@param datapool_hold_index データ判定に使用するデータプールの列番号．
		@param ref                 判定に使用する基準値．
	*/
	Is_Equal(DB* holder, int datapool_hold_index, const typename T::Hold* ref) : holder_(holder), value_(ref), datapool_hold_index_(datapool_hold_index){}

	bool operator()() const {
		if(holder_->get<T>(datapool_hold_index_) == *value_ ){
			return true;
		}
		return false;
	}
private:
	DISALLOW_COPY_AND_ASSIGN_1(Is_Equal, T);
	int datapool_hold_index_;
	const typename T::Hold* value_;
	DB* holder_;
};

//! AocsDataPoolの指定した列から最新のデータを取得し，その値と基準値とのノルムが指定した値以下であればtrueを返す入力ファンクタ．
/*! 
	@tparam T AocsDataPoolに収められているデータの型．operator < および double norm(int) が実装されている必要がある．
*/
template <class T>
class Is_Near  {
public:
	typedef core::datapool::AocsDataPool DB;
	//! コンストラクタ．
	/*!
		@param holder              データプールのインスタンス．
		@param datapool_hold_index データ判定に使用するデータプールの列番号．
		@param ref                 判定に使用する基準値．
		@param distance            判定の境界条件となるノルム値．
		@param norm                計算に使用するノルムの次元．
	*/
	Is_Near(DB* holder, int datapool_hold_index, const typename T::Hold* ref, double distance, int norm) 
		: holder_(holder), value_(ref), datapool_hold_index_(datapool_hold_index), distance_(distance), norm_(norm){

	}

	bool operator()() const {
		if((holder_->get<T>(datapool_hold_index_) - *value_).norm(norm_) < distance_){
			return true;
		}
		return false;
	}
private:
	DISALLOW_COPY_AND_ASSIGN_1(Is_Near, T);
	double distance_;
	int norm_;
	int datapool_hold_index_;
	const typename T::Hold* value_;
	DB* holder_;
};

//! AocsDataPoolの指定した列から最新のデータを取得し，その値のノルムが指定した値以下であればtrueを返す入力ファンクタ．
/*! 
	@tparam T AocsDataPoolに収められているデータの型．operator < および double norm(int) が実装されている必要がある．
*/
template <class T>
class Is_Under  {
public:
	typedef core::datapool::AocsDataPool DB;
	Is_Under(DB* holder, int datapool_hold_index, double norm) : holder_(holder), datapool_hold_index_(datapool_hold_index), distance_(norm), norm_(2){

	}
	Is_Under(DB* holder, int datapool_hold_index, int index, double value) : holder_(holder), datapool_hold_index_(datapool_hold_index), distance_(value), norm_(0), index_(index){

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
	DISALLOW_COPY_AND_ASSIGN_1(Is_Under, T);
	double distance_;
	int norm_;
	int index_;
	int datapool_hold_index_;
	DB* holder_;
};

//! AocsDataPoolの指定した列から最新のデータを取得し，その値のノルムが指定した値以上であればtrueを返す入力ファンクタ．
/*! 
	@tparam T AocsDataPoolに収められているデータの型．operator > および double norm(int) が実装されている必要がある．
*/
template <class T>
class Is_Over  {
public:
	typedef core::datapool::AocsDataPool DB;
	Is_Over(DB* holder, int datapool_hold_index, double norm) 
		: holder_(holder), datapool_hold_index_(datapool_hold_index), distance_(norm), norm_(2){}

	Is_Over(DB* holder, int datapool_hold_index, int index, double value)
		: holder_(holder), datapool_hold_index_(datapool_hold_index), distance_(value), norm_(0), index_(index){}

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
	DISALLOW_COPY_AND_ASSIGN_1(Is_Over, T);
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
