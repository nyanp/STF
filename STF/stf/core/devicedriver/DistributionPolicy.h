/**
 * @file   DistributionPolicy.h
 * @brief  CompositeOutputの値を子に分配する方法を定めるポリシークラス群と，ポリシー選択メタ関数．
 *
 * @author Taiga Nomi
 * @date   2011.02.28
 */
#ifndef stf_core_devicedriver_DistributionPolicy_h
#define stf_core_devicedriver_DistributionPolicy_h

#include "../../datatype/DCM.h"
#include "../../Macros.h"

namespace stf {
namespace core {
namespace devicedriver {

//! 疑似逆行列によってトルクを分配する分配ポリシー．
template<class From,int N>
class ScalarDCMDistribution {
public:
	MUST_BE_DERIVED_FROM(From, datatype::StaticVector<3>);

	template<class Parent,class Child>
	void setup(Parent* parent, Child (&child)[N]){	
		datatype::StaticMatrix<3,N> m;
		for(int i = 0; i < N; i++){
			datatype::DCM d = child[i]->get_transfomer();
			for(int j = 0; j < 3; j++)
				m[j][i] = d[j][2];
		}
		this->output_mat_ = m.trans() * ( m * m.trans() ).inverse();
	}

	template<class Parent,class Child>
	void distribute(Parent* parent, Child (&child)[N]){
		datatype::StaticVector<N> v = output_mat_ * parent->get_torque();
		for(int i = 0; i < N; i++){
			child[i]->set_torque(v[i]);
		}
	}
private:
	datatype::StaticMatrix<N,3> output_mat_;//トルク分配行列
};


template<class To, class From, int Numbers, bool UseAlignment>
struct DistributionSelector {
typedef ScalarDCMDistribution<From,Numbers> Result;
};

} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_DistributionPolicy_h
