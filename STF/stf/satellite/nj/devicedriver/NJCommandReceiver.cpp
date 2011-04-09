/**
 * @file   NJCommandReceiver.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "NJCommandReceiver.h"
#include "../../../core/command/Includes.h"
#include "../factory/NJGlobal.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace cmhandler {

//デバッグ用の特殊化．外部ファイルから1行ずつ読み込み，
template<> void NJCommandReceiver<environment::Simulator>::receive_command(){


}


} /* End of namespace stf::core::devicedriver::cmhandler */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

