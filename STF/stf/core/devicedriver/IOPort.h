/**
 * @file   IOPort.h
 * @brief  他機器との接続を型に基づいて行うための入出力ポート．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_IOPort_h
#define stf_core_devicedriver_IOPort_h

#include "../../util/loki/HierarchyGenerators.h"
#include "../../datatype/Time.h"

namespace stf {
namespace core {
namespace devicedriver {

template<class T> struct InputPort;

//! データの出力を表明するポート．
/*! 
	@tparam T   出力する型．
*/	
template<class T>
struct OutputPort {
	//! コンストラクタ．ポートのポインタを初期化
	OutputPort() : nextholder_(0) {}

	//! get_in_bodyframe関数から呼び出される，データの更新を行う関数．
	/*! OutputPortを継承した具象クラスは各々の更新ルーチンを実装しなければならない．本来ならこれは純粋仮想関数としておくべきだが，
	 *  OutputPortsが使用するLokiのFieldヘルパは抽象クラスを扱えない．そのため，ここではassert(0)を実行する関数を実装し，
	 *  派生クラス側での未実装をコンパイル時でなく，実行時に検出する仕様としている．
	 */
	virtual void do_compute(const datatype::Time& t){
		//util::cout << "do_compute must be implemented" << util::endl;
		assert(0);
	}
	virtual const T& get_in_bodyframe() const{ return value_b_;}

	//! データの取得を行う関数．
	virtual const T& get_in_bodyframe(const datatype::Time& t){ do_compute(t); return value_b_; }

	const datatype::Time& get_lastupdate() const{ return last_update_;}

	//! 機体座標系における取得値
	T value_b_;

	//! 接続された入力ポート
	InputPort<T>* nextholder_;

	//! value_b_の最終更新時刻
	datatype::Time last_update_;
};

//! データの入力を表明するポート．
/*! 
	@tparam T   入力する型．
*/	
template<class T>
struct InputPort {
	//! コンストラクタ．ポートのポインタを初期化．
	InputPort() : prevholder_(0) {}

	//! 双方向のリンクリストを形成することで，出力ポートとの接続を確立する．
	virtual void connect_source_(OutputPort<T>* outputport) { 
		prevholder_ = outputport; 
		prevholder_->nextholder_ = this;
	}

	//! 接続された出力ポート
	OutputPort<T>* prevholder_;
};

//! 入力ポートを纏め，インターフェースを提供するクラス．
/*! 
	@tparam TList   入力ポート群．LokiのTypeListで表現する
*/	
template<class TList>
class InputPorts : public Loki::GenScatterHierarchy<TList, core::devicedriver::InputPort>{
public:
	//! i番目の入力ポートに，出力ポートを持ったコンポーネントを接続する．
	template<int i,class T> 
	void connect_source(T* outputport) {
		return Loki::Field<i>(*this).connect_source_(outputport); 
	}

	//! i番目の入力ポートを取得する．
	template<int i,class T>
	InputPort<T>& inputport() {
		return Loki::Field<i>(*this);
	}

	//! i番目の入力ポートに接続された出力ポートを取得する．何も接続されていないポートに対して実行した場合の動作は未定義．
	template<int i,class T>
	OutputPort<T>& source(){
		return *(Loki::Field<i>(*this).prevholder_);
	}

	//! i番目の入力ポートに接続された出力ポートの，最終更新時刻を取得する．
	template<int i>
	const datatype::Time& getLastInputTime() {
		return Loki::Field<i>(*this).prevholder_->last_update_;
	}

	//! i番目の入力ポートに出力ポートが接続しているかを取得．
	template<int i>
	bool input_isconnected() {
		if(Loki::Field<i>(*this).prevholder_ == 0) return false;
		else return true;
	}
};

//! 出力ポートを纏め，インターフェースを提供するクラス．
/*! 
	@tparam TList   出力ポート群．LokiのTypeListで表現する
*/	
template<class TList>
class OutputPorts : public Loki::GenScatterHierarchy<TList, OutputPort>{
public:
	//! 伝搬関数のデフォルト実装．（何もしない）
	virtual void do_compute(const datatype::Time& t){}

	//! i番目の出力ポートから現在の値を伝搬無しで取得する．
	template<int i,class T>
	const T& get() const{	
		return Loki::Field<i>(*this).get_in_bodyframe();
	}

	//! i番目の出力ポートを取得する．
	template<int i,class T>
	OutputPort<T>& outputport() {
		return Loki::Field<i>(*this);
	}

	//! i番目の出力ポートの，最終更新時刻を取得する．
	template<int i>
	const datatype::Time& getLastOutputtime() {	
		return Loki::Field<i>(*this).get_lastupdate();
	}

	//! i番目の出力ポートの，最終更新時刻を設定する．
	template<int i>
	void setLastOutputtime(const datatype::Time& time){
		Loki::Field<i>(*this).last_update_ = time;
	}

	//! i番目の出力ポートに入力ポートが接続しているかを取得．
	template<int i>
	bool output_isconnected() {
		if(Loki::Field<i>(*this).nextholder_ == 0) return false;
		else return true;
	}
};


} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_IOPort_h