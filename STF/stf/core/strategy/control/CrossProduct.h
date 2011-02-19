/**
 * @file   CrossProduct.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_control_CrossProduct_h
#define stf_core_strategy_control_CrossProduct_h

#include "../StrategyBase.h"
#include "../../../datatype/StaticVector.h"
#include "../../../datatype/List.h"
#include "../../../datatype/Magnetic.h"
#include "../../devicedriver/IOPort.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {


//クロスプロダクト則を用いて要求出力トルクを磁気モーメントに変換する．
//要求トルク方向と地磁場ベクトルが直交するときに駆動しないと擾乱が大きい．
//入力:3軸トルク(T), 衛星座標系磁場(B)
//出力:3軸磁気モーメント(M)
class CrossProduct
	: virtual public StrategyBase, 
	public devicedriver::InputPorts< TYPELIST_2( datatype::StaticVector<3>, datatype::MagneticField ) >,
	public devicedriver::OutputPorts< TYPELIST_1( datatype::MagneticMoment ) >
{
public:
	CrossProduct(int instance_id) : StrategyBase(instance_id, "CrossProduct"){}
	CrossProduct(int instance_id, 
		devicedriver::OutputPort<datatype::StaticVector<3>>* torquer_source,
		devicedriver::OutputPort<datatype::MagneticField>* b_source,
		devicedriver::InputPort<datatype::MagneticMoment>* mag_out = 0
		);
	~CrossProduct(){}
	virtual void do_compute(const datatype::Time& t);
protected:
};


} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_strategy_control_input_CrossProduct_h
