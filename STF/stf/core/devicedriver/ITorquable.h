/**
 * @file   ITorquable.h
 * @brief トルクを出力するコンポーネントに対するインターフェース
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_ITorquable_h
#define stf_core_devicedriver_ITorquable_h

namespace stf {
namespace core {
namespace devicedriver {

//! トルクを出力するコンポーネントに対するインターフェース
/*! */
class ITorquable {
public:
	//!　新しいトルクの指令値をセットします．デバイスへの送信はdo_updateによって実行されます
    virtual void set_torque(double value)  = 0;
    virtual ~ITorquable() { }
};

} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_ITorquable_h
