/**
 * @file   IEnabable.h
 * @brief  有効化・無効化制御が可能なコンポーネントに対するインターフェース．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_interface_IEnabable_h
#define stf_interface_IEnabable_h

namespace stf {
namespace interface {

//! 有効化・無効化制御が可能なコンポーネントに対するインターフェース．
/*! */
class IEnabable {
public:
    virtual void enable()  = 0;
    virtual void disable()  = 0;
	virtual bool is_enable () const = 0;
    virtual ~IEnabable() { }
};

} /* End of namespace stf::interface */
} /* End of namespace stf */

#endif // stf_interface_IEnabable_h
