/**
 * @file   NJSwitchable.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_NJSwitchable_h
#define stf_core_devicedriver_NJSwitchable_h

#include "../../core/devicedriver/ISwitchable.h"
#include "../../core/devicedriver/IDataUpdatable.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace nj {

// 電源スイッチを操作可能なコンポーネント群．
template<class Env, int Ports = 1>
class NJSimpleComponent : virtual public ISwitchable, virtual public IDataUpdatable {
public:
	virtual ~NJSimpleComponent(){}
	virtual void on(){ is_on_ = true; }
	virtual void off(){ is_on_ = false; }
	virtual bool is_on () const { return is_on_; }
	virtual void do_update(){}
private:
	typename Env::GPIO<Ports> io_;
	bool is_on_;
};

template<class Env>
class NJTDI : public NJSimpleComponent<Env, 5> {
public:

private:

};

template<class Env>
class NJRX : public NJSimpleComponent<Env> {
public:

private:

};

template<class Env>
class NJTX : public NJSimpleComponent<Env>  {
public:

private:

};

template<class Env>
class NJBatteryManager : public NJSimpleComponent<Env>  {
public:

private:

};

template<class Env>
class NJHeaterManager : public NJSimpleComponent<Env, 2>  {
public:

private:

};

} /* End of namespace stf::core::devicedriver::nj */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_NJFOG_NJFOG_h
