/**
 * @file   CDHComponent.h
 * @brief  AD変換器や温度計など，複数のセンサを一括して取り扱うコンポーネントの基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */

#ifndef stf_core_devicedriver_CDHComponent_h
#define stf_core_devicedriver_CDHComponent_h

#include "IOPort.h"
#include "IDataUpdatable.h"
#include "ISwitchable.h"
#include "../../RootObject.h"
#include "../../interface/Iterator.h"

namespace stf {
namespace datatype {
class String;
}
namespace interface {
template<class Env, class T, int NUM> class CDHComponentIterator;
}
namespace core {
namespace devicedriver {

//! AD変換器や温度計など，複数のセンサを一括して取り扱うコンポーネントの基底クラス．
/*! 
	@tparam T   測定している物理量を表す型．
	@tparam NUM 観測チャネル数．
	@tparam Env コンポーネントの環境クラス．
*/
template<class Env, class T, int NUM>
class CDHComponent : public RootObject, virtual public IDataUpdatable, virtual public ISwitchable {
public:
	enum { NumberOfChannels = NUM };
	typedef T   Hold; //!< 測定対象の型．
	typedef Env Environment;//!< 環境クラス．

	CDHComponent(const datatype::String& name) : RootObject(name) {}
	void connect(core::datapool::AocsDataPool* pool, int rows, const datatype::String name){ 
		this->datapool_hold_index_ = pool->create(this, rows, name);
		datapool_ = pool; 
	}
	virtual void on(){ is_on_ = true;}
	virtual void off(){ is_on_ = false;}
	virtual bool is_on() const{ return is_on_; }
	virtual void do_update() = 0;
	const T& operator [] (int i) const { stf_assert( i < NUM); return value_[i]; }
	T& operator [] (int i) { stf_assert( i < NUM);return value_[i]; }
	virtual ~CDHComponent(){}
protected:
	bool is_on_;
	T value_[NUM];
private:
	friend class interface::CDHComponentIterator<Env, T, NUM>;
    CDHComponent();
};

//! 電圧と電流など，異なる物理量を複合的に取り扱うコンポーネントの基底クラス．
/*! 
	@tparam Env     コンポーネントの環境クラス．
	@tparam TList   測定している物理量を表す型．LokiのTypelistを与える
*/
template<class Env, class TList>
class CDHMultiComponent : public RootObject, public OutputPorts<TList>, virtual public IDataUpdatable, virtual public ISwitchable {
public:
	typedef Env Environment;//!< 環境クラス．

	CDHMultiComponent(const datatype::String& name) : RootObject(name) {}
	virtual void on(){ is_on_ = true;}
	virtual void off(){ is_on_ = false;}
	virtual bool is_on() const{ return is_on_; }
protected:
	bool is_on_;
};

} /* End of namespace stf::core::component */
} /* End of namespace stf::core */

namespace interface {

//! scalar型など, value()でdoubleを取れる型のCDHComponentに対して使えるイテレータ
/*! 
	@tparam Env コンポーネントの環境クラス．
	@tparam T   対象CDHComponentが測定している物理量を表す型．
	@tparam NUM 対象CDHComponentの観測チャネル数．
*/
template<class Env, class T, int NUM>
class CDHComponentIterator : public Iterator {
public:
	CDHComponentIterator(core::devicedriver::CDHComponent<Env, T, NUM>* data) : data_(data), index_(0){}
	virtual void init(){ index_  = 0; }
	virtual bool end(){
		if(index_ >= NUM) return true; return false;
	}
	virtual void operator ++(){
		index_++;
	}
	virtual double operator()(){
		return data_->value_[index_].value();
	}
private:
	const core::devicedriver::CDHComponent<Env, T, NUM>* data_;
	int index_;
};

}
} /* End of namespace stf */

#endif // stf_core_devicedriver_CDHComponent_h
