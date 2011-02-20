/**
 * @file   DummyCommandReceiver.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "DummyCommandReceiver.h"
#include "../../command/Command.h"
#include "../../manager/CommandManagerBase.h"
#include "../../../datatype/String.h"
#include "../../../util/Ostream.h"
#include "../../devicedriver/clock/ITimeClock.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace cmhandler {

// デバッグ用なのでコンソールからの入力は無いと考える
void DummyCommandReceiver::receive_command()
{

}

// デバッグ用なので送信機に送る変わりにコンソールに出力する
void DummyCommandReceiver::send_packet(const datatype::String& msg)
{
	util::cout << "downlink:" << msg << "at:" << this->clock_->get_time() << util::endl;
}

// デバッグ用なので送信機に送る変わりにコンソールに出力する
void DummyCommandReceiver::send_packet(int msg)
{
	util::cout << "downlink:" << msg << "at:" << this->clock_->get_time() << util::endl;
}

void DummyCommandReceiver::add_command(command::Command* cmd)
{
	this->manager_->addCommand(cmd);
	cmd->connectReceiver(this);
}

} /* End of namespace stf::core::devicedriver::cmhandler */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

