/**
 * @file   ADCBase.h
 * @brief  AD変換器ドライバの抽象クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_ADCBase_h
#define stf_core_devicedriver_ADCBase_h

#include "../../util/stfassert.h"
#include "../CDHComponent.h"
#include "ConvertPolicy.h"
#include "../../../datatype/Environments.h"

namespace stf {
namespace core {
namespace devicedriver {

//! AD変換器ドライバの抽象クラス．
/*! 
	アプリケーションに応じて，これを継承したAD変換器クラスで適切なdo_updateを実装することで実体化が可能になる．
	@tparam NUM AD変換対象のチャネル数．
	@tparam Env コンポーネントの環境クラス．
*/
template<int NUM, class Env = ENV>
class ADCBase : public CDHComponent< datatype::Voltage, NUM, Env >  {
public:
	ADCBase(int instance_id) :  CDHComponent<datatype::Voltage,NUM, Env>(instance_id, "ADCBase") {}
	virtual ~ADCBase(){}
protected:
};

//! ADCのデジタル値を物理値に変換して保持するコンポーネント．
/*! 
	変換本体はポリシークラスのconvertが受け持つ．クラスTはdoubleからのimplicitなコンストラクタ，またはdoubleを右辺に取るoperator=を持っている必要がある(Scalar,Voltageなど).
	@tparam T                保持する物理値の型．
	@tparam NUM              保持する物理値のチャネル数．
	@tparam ADCNUM           対象のADCが持つ総チャネル数．
	@tparam Env              コンポーネントの環境クラス．
	@tparam ConversionPolicy convert関数の実装を決定する変換ポリシークラス．
*/
template<class T, int NUM, int ADCNUM = NUM, class Env = ENV, class ConversionPolicy = FirstOrderConvert>
class MultiSensor : public CDHComponent< T, NUM, Env >, public ConversionPolicy {
public:
	MultiSensor(int instance_id, ADCBase<ADCNUM, Env>* adc, int offset) : adcsource_(adc), offset_(offset), CDHComponent< T, NUM, Env >(instance_id, "TempSensor")
	{
		stf_assert(offset + NUM <= ADCNUM);//ADCの範囲をこえない
	}
	virtual void do_update(){
		for(int i = 0; i < NUM; i++){
			this->value_[i] = convert((*adcsource_)[i + offset_].value());
		}
	}
	virtual ~MultiSensor(){}
private:
	ADCBase<ADCNUM, Env>* adcsource_;
	int offset_;
};

} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_ADCBase_h
