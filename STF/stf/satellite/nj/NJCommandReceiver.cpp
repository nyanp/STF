#include "NJCommandReceiver.h"
#include "../../core/command/Includes.h"
#include "NJGlobal.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace cmhandler {

//デバッグ用の特殊化．外部ファイルから1行ずつ読み込み，
template<> void NJCommandReceiver<environment::Simulator>::receiveCmd(){


}


} /* End of namespace stf::core::devicedriver::cmhandler */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

