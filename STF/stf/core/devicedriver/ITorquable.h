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
    //virtual double getTorque() const  = 0;
	///　新しいトルクの指令値をセットします．デバイスへの送信はdoUpdateによって実行されます
    virtual void setTorque(double value)  = 0;

	///
    //virtual datatype::Vector getTorqueInBodyFrame() const  = 0;
    virtual ~ITorquable() { }
};

} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // interface_ITorquable_h
