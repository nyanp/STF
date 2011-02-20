/**
 * @file   ITorquable.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef interface_ITorquable_h
#define interface_ITorquable_h

#include "../../datatype/Vector.h"
#include "../../datatype/StaticVector.h"

namespace stf {
namespace core {
namespace devicedriver {

class ITorquable {
public:
	///
    //virtual double get_torque() const  = 0;
	///　新しいトルクの指令値をセットします．デバイスへの送信はdo_updateによって実行されます
    virtual void set_torque(double value)  = 0;

	///
    //virtual datatype::Vector get_torque_bodyframe() const  = 0;
    virtual ~ITorquable() { }
};

} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // interface_ITorquable_h
