#ifndef stf_core_devicedriver_ISwitchable_h
#define stf_core_devicedriver_ISwitchable_h

namespace stf {
namespace core {
namespace devicedriver {
//CPUによる電源のオンオフ制御が可能なコンポーネントに対するインターフェース．
class ISwitchable {
public:
    virtual void on()  = 0;
    virtual void off()  = 0;
	virtual bool is_on () const = 0;
    virtual ~ISwitchable() { }
};


} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_ISwitchable_h
