/**
 * @file   CompositePolicy.h
 * @brief  Compositeクラスの集約・分配則を決めるためのポリシークラス群．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_CompositePloicy_h
#define stf_core_devicedriver_CompositePloicy_h

#include "../../datatype/Time.h"
#include "../../datatype/DCM.h"

namespace stf {
namespace core {
namespace devicedriver {

template<class To, class From, int N>
struct AggregateSelector {
typedef NScalarAggregate<To, From, N> Result;
};

//! 子のScalar値を各要素に持ったVectorを親の値とする合成ポリシー．
template<class To,int N>
class NScalarAggregate {
public:
	template<class Parent,class Child>
	void setup(Parent* parent, Child (&child)[N]){}

	template<class Parent,class Child>
	void aggregate(Parent* parent, Child (&child)[N]){
		To value;
		for(int i = 0; i < N; i++){
			value[i] += child[i]->get_value(parent->get_lastupdate()).value();
		}
		parent->set_value(value);
	}
};

//! 子の平均値を親の値とする合成ポリシー．
template<class ToAndFrom,int N>
class AverageAggregate {
public:
	template<class Parent,class Child>
	void setup(Parent* parent, Child (&child)[N]){}

	template<class Parent,class Child>
	void aggregate(Parent* parent, Child (&child)[N]){
		ToAndFrom value;
		for(int i = 0; i < N; i++){
			value += child[i]->get_value(parent->get_lastupdate());
		}
		value /= N;
		parent->set_value(value);
	}
};


template<class To, int N>
class ScalarDCMAggregate {
public:
	template<class Parent,class Child>
	void setup(Parent* parent, Child (&child)[N]){	
		datatype::StaticMatrix<N,3> m;
		for(int i = 0; i < Numbers; i++){
			datatype::DCM d = this->childs_[i]->get_transfomer().inverse();
			for(int j = 0; j < 3; j++)
				m[i][j] = d[2][j];
		}
		this->aggregate_mat_ = m.trans() * ( m * m.trans() ).inverse();		
	}

	template<class Parent,class Child>
	void aggregate(Parent* parent, Child (&child)[N]){
		datatype::StaticVector<N> value;
		for(int i = 0; i < N; i++){
			value[i] = child[i]->get_value(parent->get_lastupdate());
		}
		parent->set_value(aggregate_mat_ * value);
	}
private:
	datatype::StaticMatrix<3,N> aggregate_mat_;//トルク分配行列
};

template<class ToAndFrom,int N>
class VectorDCMAggregate {
public:
	template<class Parent,class Child>
	void setup(Parent* parent, Child (&child)[N]){	}

	template<class Parent,class Child>
	void aggregate(Parent* parent, Child (&child)[N]){
		Parent::Target value;
		for(int i = 0; i < N; i++){
			value += child[i]->get_transfomer() * child[i]->get_value(parent->get_lastupdate());
		}
		value.normalize();
		parent->set_value(value);
	}
};

//! 疑似逆行列から
class SimpleDistribute {
public:
	template<class Parent,class Child,int N>
	void distribute(Parent* parent, Child (&child)[N]){
		datatype::StaticVector<N> v = parent->output_mat_ * parent->output_;
		for(int i = 0; i < N; i++){
			child[i]->set_torque(v[i]);
		}
	}

};

} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_CompositePloicy_h