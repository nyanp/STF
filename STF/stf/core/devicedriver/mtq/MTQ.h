/**
 * @file   MTQ.h
 * @brief  ソフトウェアシミュレーションレベルで動作する磁気トルカドライバ．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_mtq_MTQ_h
#define stf_core_devicedriver_mtq_MTQ_h

#include "MTQBase.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace mtq {

//! ソフトウェアシミュレーションレベルで動作する磁気トルカドライバ．
/*! 
	@tparam T コンポーネントの環境クラス．
*/
template<class T>
class MTQ : public MTQBase<T> {
public:
	~MTQ(){}
	//1Nm出力，線形性誤差5％
	MTQ(const datatype::DCM &angle) : MTQBase(angle, 1, -1, 5){}
private:
	MTQ(){}
};

} /* End of namespace stf::core::devicedriver::mtq */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_mtq_MTQ_h
