/**
 * @file   SmallMTQ.h
 * @brief  ソフトウェアシミュレーションレベルで動作する小規模磁気トルカドライバ．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_mtq_SmallMTQ_h
#define stf_core_devicedriver_mtq_SmallMTQ_h

#include "MTQBase.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace mtq {

//! ソフトウェアシミュレーションレベルで動作する小規模磁気トルカドライバ．
/*! 
	@tparam T コンポーネントの環境クラス．
*/
template<class T>
class SmallMTQ : public MTQBase<T> {
public:
	~SmallMTQ(){}
	//50mNm出力，線形性誤差1％
	SmallMTQ(const datatype::DCM &angle) : MTQBase(angle, 0.05, 1){}
private:
};

} /* End of namespace stf::core::devicedriver::mtq */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_mtq_MTQ_h
