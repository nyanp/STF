/**
 * @file   ADCBase.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_ADCBase_h
#define stf_core_devicedriver_ADCBase_h

#include "../CDHComponent.h"
#include "../../../datatype/Envitonments.h"

namespace stf {
namespace core {
namespace devicedriver {


///センサ，アクチュエータの基本クラス．
template<int NUM, class Env = ENV>
class ADCBase : public CDHComponent< datatype::Voltage, NUM, Env >  {
public:
	ADCBase(int instance_id) :  CDHComponent<datatype::Voltage,NUM,Env>(instance_id,"ADCBase") {}
	virtual void doUpdate(){}
	virtual ~ADCBase(){}
protected:
	typename Env::GPIO<NUM> gpio_;
};


class FirstOrderConvert {
public:
	void set(double sf, double offset){ scale_factor_ = sf; offset_ = offset; }
	double convert(double input) { return scale_factor_ * input + offset_; }
private:
	double scale_factor_;
	double offset_;
};

class SecondOrderConvert {
public:
	void set(double a, double b, double c){ a_ = a; b_ = b; c_ = c; }
	double convert(double input) { return a_ * a_ * input + b_ * input + c_; }
private:
	double a_;
	double b_;
	double c_;
};

//ADCのデジタル値を物理値に変換して保持するコンポーネント．変換本体はポリシークラスのconvertが受け持つ．
//クラスTはdoubleからのimplicitなコンストラクタを持っている必要がある(scalarなど).
template<class T, int NUM, int ADCNUM = NUM, class Env = ENV, class ConversionPolicy = FirstOrderConvert>
class MultiSensor : public CDHComponent< T, NUM, Env >, public ConversionPolicy {
public:
	MultiSensor(int instance_id, ADCBase<ADCNUM,Env>* adc, int offset) : adcsource_(adc), offset_(offset), CDHComponent< T, NUM, Env >(instance_id,"TempSensor")
	{
		assert(offset + NUM <= ADCNUM);//ADCの範囲をこえない
	}
	virtual void doUpdate(){
		for(int i = 0; i < NUM; i++){
			this->value_[i] = convert((*adcsource_)[i + offset_].value());
		}
	}
	virtual ~MultiSensor(){}
private:
	ADCBase<ADCNUM,Env>* adcsource_;
	int offset_;
};



} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_ADCBase_h
