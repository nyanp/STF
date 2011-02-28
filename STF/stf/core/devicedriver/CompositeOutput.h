/**
 * @file   CompositeOutput.h
 * @brief  AOCSActuatorの集合体を表現するクラス．

 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_CompositeOutput_h
#define stf_core_devicedriver_CompositeOutput_h
#include <assert.h>
#include "AOCSActuator.h"
#include "../datapool/Datapool.h"
#include "DistributionPolicy.h"

namespace stf {
namespace core {
namespace devicedriver {

//! AOCSActuatorの集合体を表すクラス．
/*! 
	@tparam Leaf             纏めるAOCSActuatorの型．
	@tparam Numbers          チャネル数．
	@tparam UseAlignment     取り付け行列に基づいた指令値の分配を行うか
	@tparam DistributionPolicy 分配に使用するポリシークラス．

	Compositeデザインパターンを使うことで，単体のAOCSActuatorと同等の扱いが可能．
	軸ごとに通信系統が独立したアクチュエータを，一個のモジュールのように操作できる．

	@code
	RW rw[4]; //1軸ホイール
	CompositeOutput<RW, 4> rwmodule; //4軸ホイールモジュール
	
	for(int i = 0; i < 4; i ++)
		rwmodule.append_child(rw[i]);//モジュールに子を登録
	
	datatype::StaticVector<3> torque;
	rwmodule.set_torque(torque);//指令値をセット
	
	rwmodule.do_update();//指令値を子に分配
	@endcode
	
	Compositeから子への分配規則は，DistributionPolicyポリシー・クラスが決定する．
	DistributionPolicyは以下の2つのメソッドを持っている必要がある．
	
	:setup:子が既定の個数登録された段階で実行される，ポリシークラスの初期化メソッド．空でも良い．
	:distribute:Compositeの値を子に分配するメソッド．
	
	テンプレート引数を省略した場合，ポリシーはDistributionSelectorメタ関数によって自動的に決定される．
*/
template
<
	class Leaf, 
	int Numbers, 
	bool UseAlignment = false, 
	class DistributionPolicy = typename DistributionSelector<typename Leaf::Hold, typename Leaf::Target, Numbers, UseAlignment>::Result 
>
class CompositeOutput : public AOCSActuator<typename Leaf::Target, typename Leaf::Target, typename Leaf::Environment>, public DistributionPolicy {
public:
	STF_STATIC_ASSERT( Numbers <= 255 , CHILD_NUMBER_OVERFLOW );

	typedef Leaf Child;
	enum { UseAlignmentForDistribution = UseAlignment, NumberOfChilds = Numbers };

	CompositeOutput(int instance_id, const datatype::DCM& dcm)
		: AOCSActuator<typename Leaf::Target, typename Leaf::Target, typename Leaf::Environment>(instance_id, "Composite", dcm), index_(0)
	{
		for(int i = 0; i < Numbers; i++) childs_[index_] = 0;
	}

	virtual ~CompositeOutput(){}
	virtual void do_update();
	void append_child(Leaf* c);
private:
	Child* childs_[Numbers];
	unsigned char index_;//max 255 childs
};

//! Compositeが纏める子オブジェクトを登録する．
template <class Leaf, int Numbers, bool UseAlignment, class DistributionPolicy>
void CompositeOutput<Leaf, Numbers, UseAlignment, DistributionPolicy>::append_child(Leaf* c){
	assert(index_ < Numbers);
	childs_[index_] = c;
	index_++;
	if(index_ == Numbers){//子が出そろった
		setup(this, childs_);//Policy Class Method
	}
}

//! 親から子へ再帰的にUpdateを実行する．
template <class Leaf, int Numbers, bool UseAlignment, class DistributionPolicy>
void CompositeOutput<Leaf, Numbers, UseAlignment, DistributionPolicy>::do_update(){
	if(this->datapool_ != 0){
		this->datapool_->set<CompositeOutput<Leaf, Numbers> >(datapool_hold_index_, this->output_);//
	}

	distribute(this, childs_); //Policy Class Method

	for(unsigned char i = 0; i < Numbers; ++i){
		if(childs_[i] != 0)
			childs_[i]->do_update();
	}
}

} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_CompositeOutput_h
