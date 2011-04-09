/**
 * @file   RW.h
 * @brief  ソフトウェアシミュレーションレベルで動作するRWドライバ．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_rw_RW_h
#define stf_core_devicedriver_rw_RW_h

#include "RWBase.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace rw {

//! ソフトウェアシミュレーションレベルで動作するRWドライバ．
/*! 
	@tparam Env コンポーネントの環境クラス．
*/
template<class Env>
class RW : public RWBase<Env> {
public:
	~RW(){}
	// 1Nm, 500Nms
	RW(const datatype::DCM &angle) : RWBase(angle, 1, -1, 500){}
private:
};

} /* End of namespace stf::core::devicedriver::rw */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_mtq_RW_h
