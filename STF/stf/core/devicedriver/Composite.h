#ifndef core_component_Composite_h
#define core_component_Composite_h
#include <assert.h>
#include "AOCSComponent.h"
#include "AOCSActuator.h"
#include "AOCSSensor.h"
#include "../../datatype/Matrix.h"
#include "../../datatype/List.h"
#include "../../datatype/Quaternion.h"
#include "../../util/Ostream.h"
#include "../datapool/Datapool.h"

namespace stf {
namespace core {
namespace devicedriver {
//
// Composite
//  AOCSComponentの集合体を表すクラス．
//  Compositeデザインパターンを使い，単体のAOCSComponentと同等の扱いができる．
//  必要な物理量をコンポーネント単独のインターフェースで得られない場合
// （軸ごとに通信系統が違うアクチュエータや，複数軸の観測値を組み合わせる前提のセンサなど）に使う．

template<class Leaf,int Numbers>
class CompositeInput : public AOCSSensor<typename Leaf::Target> {
public:
	CompositeInput(int instance_id, const datatype::DCM& dcm) : AOCSSensor<typename Leaf::Target>(instance_id,"Composite",dcm), index_(0)
	{
		for(int i = 0; i < Numbers; i++) childs_[index_] = 0;
	}
	virtual ~CompositeInput(){}
	virtual void doUpdate();
	virtual void aggregate();
	virtual typename Leaf::Target inputFilter(const typename Leaf::Target& value){ return value; }//compositeはフィルタをそのまま返す
	void appendChild(Leaf* c);
protected:
private:
	Leaf* childs_[Numbers];
	unsigned char index_;//max 255 childs
};

template<class Leaf,int Numbers>
class CompositeOutput : public AOCSActuator<typename Leaf::Target> {
public:
	CompositeOutput(int instance_id, const datatype::DCM& dcm) : AOCSActuator<typename Leaf::Target>(instance_id,"Composite",dcm), output_mat_(Numbers,3), index_(0)
	{
		for(int i = 0; i < Numbers; i++) childs_[index_] = 0;
		output_mat_.unitize(); //デフォルトでトルク分配行列は単位行列
	}
	virtual ~CompositeOutput(){}
	virtual void doUpdate();
	virtual void distribute();
	virtual void matrixset();//疑似逆行列を用いてトルク分配行列を生成
	void appendChild(Leaf* c);
protected:
private:
	Leaf* childs_[Numbers];
	datatype::Matrix output_mat_;//トルク分配行列
	unsigned char index_;//max 255 childs
};

template <class Leaf,int Numbers>
void CompositeInput<Leaf,Numbers>::appendChild(Leaf* c){
	assert(index_ < Numbers);
	childs_[index_] = c;
	index_++;
}

template <class Leaf,int Numbers>
void CompositeOutput<Leaf,Numbers>::appendChild(Leaf* c){
	assert(index_ < Numbers);
	childs_[index_] = c;
	index_++;
	if(index_ == Numbers){//子が出そろった
		this->matrixset();
	}
}

//Input:親から子へ再帰的にUpdateを実行する．
// 実センサから値を取得→各センサオブジェクトがローカルに保持した値をCompositeに集約→Body座標系での値としてDBに登録
template <class Leaf,int Numbers>
void CompositeInput<Leaf,Numbers>::doUpdate(){
	for(unsigned char i = 0; i < Numbers; ++i){
		if(childs_[i] != 0)
			childs_[i]->doUpdate();
	}
	aggregate();
	if(this->datapool_ != 0){
		datapool_->set<CompositeInput<Leaf,Numbers>>(datapool_hold_index_,this->value_);
	}
}

//リーフコンポーネントが取得した値を合成するメソッド．
//必要に応じて部分特殊化を使い，物理量とアプリケーションに対して適切な合成を行う
template <class Leaf,int Numbers>
void CompositeInput<Leaf,Numbers>::aggregate(){
	typename Leaf::Target v;
	int updatedsensors = 0;
	for(unsigned char i = 0; i < Numbers; ++i){
		if(childs_[i] != 0){
			if(childs_[i]->getLastUpdateTime() > this->getLastUpdateTime()){//古いものはスキップ？
				v += childs_[i]->getValueInBodyFrame();//単純加算で合成できる？
				updatedsensors ++;
			}
		}
	}
	if(updatedsensors == 0){//子供が更新していないので自分も何もしない
		return;
	}
	v.normalize();//物理量を正規化
	this->setValueInBodyFrame(v);
}


//Output:親から子へ再帰的にUpdateを実行する．
// Body座標系での指令値をDBから読み込み→各センサへトルクを分配→各センサオブジェクトがローカルに保持した値を実アクチュエータに送信
template <class Leaf,int Numbers>
void CompositeOutput<Leaf,Numbers>::doUpdate(){
	if(this->datapool_ != 0){
		this->datapool_->set<CompositeOutput<Leaf,Numbers>>(datapool_hold_index_,this->value_b_);//
	}
	distribute();
	for(unsigned char i = 0; i < Numbers; ++i){
		if(childs_[i] != 0)
			childs_[i]->doUpdate();
	}
}

//リーフコンポーネントに出力（トルク等）を分配するメソッド．
//必要に応じて部分特殊化を使い，物理量とアプリケーションに対して適切な分配を行う
template <class Leaf,int Numbers>
void CompositeOutput<Leaf,Numbers>::distribute(){
	//util::cout << value_;
	//util::cout << output_mat_;
	datatype::Vector v = this->output_mat_ * this->value_;
	for(int i = 0; i < Numbers; i++){
		childs_[i]->setTorque(v[i]);
	}

}

//子コンポーネントがZ軸まわりのトルクを出すと仮定して，
//疑似逆行列でエネルギー最小のトルク分配行列を計算．
template <class Leaf,int Numbers>
void CompositeOutput<Leaf,Numbers>::matrixset(){
	datatype::Matrix m(3,Numbers);
	for(int i = 0; i < Numbers; i++){
		datatype::DCM d = this->childs_[i]->getDCM();
		for(int j = 0; j < 3; j++)
			m[j][i] = d[j][2];
	}
	this->output_mat_ = m.trans() * ( m * m.trans() ).inverse();
}


} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // core_component_Composite_h
