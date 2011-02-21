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
#include <iostream>

namespace stf {
namespace core {
namespace devicedriver {
namespace cmhandler {

DummyCommandReceiver::DummyCommandReceiver(int instance_id, core::manager::CommandManagerBase* manager, const std::string &filename)
	: RootObject(instance_id,"DummyReceiver"), manager_(manager)
{
	this->manager_->set_receiver(this);

	if(filename.length() != 0)
		this->ifs_ = new std::ifstream(filename);
	else
		this->ifs_ = 0;
}

void DummyCommandReceiver::receive_command()
{
	if(ifs_ == 0) return; // ファイル指定が無ければ何もしない
	std::getline(*ifs_, last_command_);
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
	this->manager_->add_command(cmd);
	cmd->connectReceiver(this);
}

} /* End of namespace stf::core::devicedriver::cmhandler */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

