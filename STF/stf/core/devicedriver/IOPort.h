/**
 * @file   IOPort.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_IOPort_h
#define stf_core_devicedriver_IOPort_h

#include "../../util/loki/HierarchyGenerators.h"
#include "../../datatype/Time.h"
#include "../../util/Ostream.h"

namespace stf {
namespace core {
namespace devicedriver {

template<class T> struct InputPort;
	
template<class T>
struct OutputPort {
	T value_b_;//Body座標系における取得値
	InputPort<T>* nextholder_;
	datatype::Time last_update_;
	virtual void do_compute(const datatype::Time& t){
		util::cout << "do_compute must be implemented" << util::endl;
		assert(0);
	}//純粋仮想関数として宣言したいが，LokiのFieldアクセスは抽象クラスを扱えないので実行時終了．改善の余地あり
	virtual const T& getValueInBodyFrame() const{ return value_b_;}
	virtual const T& getValueInBodyFrame(const datatype::Time& t){ do_compute(t); return value_b_; }
	const datatype::Time& getLastUpdateTime() const{ return last_update_;}
};

template<class T>
struct InputPort {
	InputPort() : prevholder_(0) {}
	OutputPort<T>* prevholder_;
	//virtual void setValueInBodyFrame(const T& value){}
	virtual void connectSource_(OutputPort<T>* outputport) { 
		prevholder_ = outputport; 
		prevholder_->nextholder_ = this;//双方向リンクリストの生成
	}
};

template<class TList>
class InputPorts : public Loki::GenScatterHierarchy<TList, core::devicedriver::InputPort>{
public:
	// タイプリストのi番目のInputPortにホルダーをセットする
	template<int i,class T> 
	void connectSource(T* outputport) {
		return Loki::Field<i>(*this).connectSource_(outputport); 
	}
	template<int i,class T>
	InputPort<T>& inputport() {
		return Loki::Field<i>(*this);
	}
	template<int i,class T>
	OutputPort<T>& source(){
		return *(Loki::Field<i>(*this).prevholder_);
	}
	template<int i>
	const datatype::Time& getLastInputTime() {
		return Loki::Field<i>(*this).prevholder_->last_update_;
	}
};

template<class TList>
class OutputPorts : public Loki::GenScatterHierarchy<TList, OutputPort>{
public:
	virtual void do_compute(const datatype::Time& t){}
	// タイプリストのi番目のOutputPortから値を取得する
	template<int i,class T>
	const T& get() const{	
		return Loki::Field<i>(*this).getValueInBodyFrame();
	}
	template<int i,class T>
	OutputPort<T>& outputport() {
		return Loki::Field<i>(*this);
	}

	template<int i>
	const datatype::Time& getLastOutputtime() {	
		return Loki::Field<i>(*this).getLastUpdateTime();
	}
	template<int i>
	void setLastOutputtime(const datatype::Time& time){
		Loki::Field<i>(*this).last_update_ = time;
	}
};


} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_IOPort_h