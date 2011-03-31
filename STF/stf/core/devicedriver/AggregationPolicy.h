/**
 * @file   AggregationPolicy.h
 * @brief  子の値をCompositeInputに集約する方法を定めるポリシークラス群と，ポリシー選択メタ関数．
 *
 * @author Taiga Nomi
 * @date   2011.02.28
 */
#ifndef stf_core_devicedriver_AggregationPolicy_h
#define stf_core_devicedriver_AggregationPolicy_h

#include "../../datatype/Time.h"
#include "../../datatype/DCM.h"
#include "../../util/Macros.h"

namespace stf {
namespace core {
namespace devicedriver {


//! 子のScalar値を各要素に持ったVectorを親の値とする合成ポリシー．
template<class To, int N>
class NScalarAggregation {
public:
	MUST_BE_DERIVED_FROM( To, datatype::StaticVector<N> );

	template<class Parent, class Child>
	void setup(Parent* parent, Child (&child)[N]){}

	template<class Parent, class Child>
	void aggregate(Parent* parent, Child (&child)[N]){
		To value;
		const datatype::Time& t = parent->get_lastupdate();
		for(int i = 0; i < N; i++){
			value[i] += child[i]->get_value(t).value();
		}
		parent->set_value(value);
	}
};

//! 子の平均値を親の値とする合成ポリシー．
template<class ToAndFrom, int N>
class AverageAggregation {
public:
	template<class Parent, class Child>
	void setup(Parent* parent, Child (&child)[N]){}

	template<class Parent, class Child>
	void aggregate(Parent* parent, Child (&child)[N]){
		ToAndFrom value;
		const datatype::Time& t = parent->get_lastupdate();
		for(int i = 0; i < N; i++){
			value += child[i]->get_value(t);
		}
		value /= N;
		parent->set_value(value);
	}
};

//! 取付行列を用いて，子のスカラー値から親座標系でのベクトルを取得する合成ポリシー．
/*
	rankが小さく，疑似逆行列を生成できないような取付行列の場合の動作は未定義．
*/
template<class To, int N>
class ScalarDCMAggregation {
public:
	MUST_BE_DERIVED_FROM( To, datatype::StaticVector<3> );

	template<class Parent, class Child>
	void setup(Parent* parent, Child (&child)[N]){	
		datatype::StaticMatrix<N, 3> m;
		for(int i = 0; i < Numbers; i++){
			datatype::DCM d = this->childs_[i]->get_transfomer().inverse();
			for(int j = 0; j < 3; j++)
				m[i][j] = d[2][j];
		}
		this->aggregate_mat_ = m.trans() * ( m * m.trans() ).inverse();		
	}

	template<class Parent, class Child>
	void aggregate(Parent* parent, Child (&child)[N]){
		datatype::StaticVector<N> value;
		const datatype::Time& t = parent->get_lastupdate();
		for(int i = 0; i < N; i++){
			value[i] = child[i]->get_value(t);
		}
		parent->set_value(aggregate_mat_ * value);
	}
private:
	datatype::StaticMatrix<3,N> aggregate_mat_;//トルク分配行列
};

//! 取付行列を用いて，子のベクトル値から親座標系でのベクトルを取得する合成ポリシー．
/*
	rankが小さく，疑似逆行列を生成できないような取付行列の場合の動作は未定義．
*/
template<class ToAndFrom, int N>
class VectorDCMAggregation {
public:
	template<class Parent, class Child>
	void setup(Parent* parent, Child (&child)[N]){	}

	template<class Parent, class Child>
	void aggregate(Parent* parent, Child (&child)[N]){
		Parent::Target value;
		const datatype::Time& t = parent->get_lastupdate();
		for(int i = 0; i < N; i++){
			value += child[i]->get_transfomer() * child[i]->get_value(t);
		}
		value.normalize();
		parent->set_value(value);
	}
};

template<class To, class From, int Numbers, bool UseAlignment>
struct AggregationSelector {
typedef NScalarAggregation<To,Numbers> Result;
};

template<int Numbers, class ToAndFrom>
struct AggregationSelector<ToAndFrom, ToAndFrom,Numbers, false> {
typedef AverageAggregation<ToAndFrom, Numbers> Result;
};

template<int Numbers, class ToAndFrom>
struct AggregationSelector<ToAndFrom, ToAndFrom,Numbers, true> {
typedef VectorDCMAggregation<ToAndFrom, Numbers> Result;
};

template<class To, int Numbers>
struct AggregationSelector<To, datatype::Scalar,Numbers, false> {
typedef NScalarAggregation<To,Numbers> Result;
};

template<class To, int Numbers>
struct AggregationSelector<To, datatype::Scalar,Numbers, true> {
typedef ScalarDCMAggregation<To,Numbers> Result;
};

} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_AggregationPolicy_h
