/**
 * @file   CompositeInput.h
 * @brief  AOCSSensorの集合体を表現するクラス群．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_CompositeInput_h
#define stf_core_devicedriver_CompositeInput_h
#include <assert.h>
#include "AOCSSensor.h"
#include "../datapool/Datapool.h"
#include "AggregationPolicy.h"

namespace stf {
namespace core {
namespace devicedriver {


//! AOCSSensorの集合体を表すクラス．
/*! 
	@tparam Leaf             纏めるAOCSSensorの型．
	@tparam Numbers          チャネル数．
	@tparam UseAlignment     取り付け行列に基づいた取得値の集約を行うか
	@tparam AggregationPolicy  集約に使用するポリシークラス．

	Compositeデザインパターンを使い，単体のAOCSSensorと同等の扱いができる．
	軸ごとに指令値を送る必要があるアクチュエータを一括して扱う際に利用できる．

	@code
	Gyro gyro[3]; //1軸サンセンサ
	CompositeInput<Gyro,3> gyromodule; //3軸ホイールモジュール．子のScalarをX,Y,Z軸の順で当てたStaticVectorが親の値となる
	
	for(int i = 0; i < 3; i ++)
		gyromodule.append_child(gyro[i]);//モジュールに子を登録

	gyromodule.do_update();//子それぞれから値を取得

	STT stt[2]; //2軸スターセンサ
	CompositeInput<STT,2> sttmodule; //2軸スターセンサモジュール．子のQuaternionの平均値が親のQuaternionとなる

	sttmodule.append_child(stt[0]);
	sttmodule.append_child(stt[1]);

	sttmodule.do_update();

	@endcode
	
	子からCompositeへの集約規則は，AggregationPolicyポリシー・クラスが決定する．
	AggregationPolicyは以下の2つのメソッドを持っている必要がある．
	
	:setup:子が既定の個数登録された段階で実行される，ポリシークラスの初期化メソッド．空でも良い．
	:aggregate:子の値をCompositeに集約するメソッド．
	
	テンプレート引数を省略した場合，ポリシーはAggregationSelectorメタ関数によって自動的に決定される．

	,  UseAlignment  ,  型(集約前)  ,  型(集約後)  ,  AggregationSelectorが選択するAggregationPolicy
	,     false      ,    Scalar    ,    Scalar    ,  AverageAggregation(平均値合成)
	,     false      ,    Scalar    ,    Vector    ,  NScalarAggregation(i番目の子の値をvalue[i]に代入)
	,     false      ,    Vector    ,    Vector    ,  AverageAggregation(平均値合成)
	,      true      ,    Scalar    ,    Scalar    ,  未定義
	,      true      ,    Scalar    ,    Vector    ,  ScalarDCMAggregation(取り付け行列の疑似逆行列から機体座標系の物理量を計算)
	,      true      ,    Vector    ,    Vector    ,  VectorDCMAggregation(取り付け行列の疑似逆行列から機体座標系の物理量を計算)
*/
template<class Leaf, int Numbers, bool UseAlignment = false, class AggregationPolicy = typename AggregationSelector<typename Leaf::Target,typename Leaf::Hold,Numbers,UseAlignment>::Result >
class CompositeInput : public AOCSSensor<typename Leaf::Target>, public AggregationPolicy {
public:
	CompositeInput(int instance_id, const datatype::DCM& dcm) : AOCSSensor<typename Leaf::Target>(instance_id,"Composite",dcm), index_(0)
	{
		for(int i = 0; i < Numbers; i++) childs_[index_] = 0;
	}
	virtual ~CompositeInput(){}
	virtual void do_update();
	virtual typename Leaf::Target filter(const typename Leaf::Target& value){ return value; }//compositeはフィルタをそのまま返す
	void append_child(Leaf* c);
protected:
private:
	Leaf* childs_[Numbers];
	unsigned char index_;//max 255 childs
};

//! Compositeが纏める子オブジェクトを登録する．
template <class Leaf, int Numbers, bool UseAlignment, class AggregationPolicy>
void CompositeInput<Leaf,Numbers,UseAlignment,AggregationPolicy>::append_child(Leaf* c){
	assert(index_ < Numbers);
	childs_[index_] = c;
	index_++;
	if(index_ == Numbers){//子が出そろった
		setup(this,childs_);//Policy Class Method
	}
}

//! 親から子へ再帰的にUpdateを実行する．
template <class Leaf, int Numbers, bool UseAlignment, class AggregationPolicy>
void CompositeInput<Leaf,Numbers,UseAlignment,AggregationPolicy>::do_update(){
	for(unsigned char i = 0; i < Numbers; ++i){
		if(childs_[i] != 0)
			childs_[i]->do_update();
	}

	aggregate(this,childs_); //Policy Class Method

	if(this->datapool_ != 0){
		datapool_->set<CompositeInput<Leaf,Numbers>>(datapool_hold_index_,this->value_);
	}
}

} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_CompositeInput_h
