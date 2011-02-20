/**
 * @file   DummyCommandReceiver.h
 * @brief  コマンドレシーバのデバッグ用クラス．外部テキストファイルからコマンドを読み込む
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_cmhandler_DummyCommandReceiver_h
#define stf_core_devicedriver_cmhandler_DummyCommandReceiver_h

#include <fstream>
#include <string>
#include "ICommandReceiver.h"
#include "../../../RootObject.h"
#include "../../../datatype/List.h"

namespace stf {
namespace core {
namespace manager {
class CommandManagerBase;
}
namespace command {
class Command;
}
namespace devicedriver {
namespace cmhandler {

//! コマンドレシーバのデバッグ用クラス．外部テキストファイルからコマンドを読み込む
/*! 
	応答が必要なコマンドについては標準出力にメッセージとして吐き出す.
	外部ファイルから読み込まれたコマンドはlast_commandに文字列として格納されるだけなので，
	ここからコマンドオブジェクトに紐づける作業はこれを継承したアプリケーション固有のデバッグコマンドクラスで行う
*/
class DummyCommandReceiver: virtual public ICommandReceiver, public RootObject {
public:
	DummyCommandReceiver(int instance_id, core::manager::CommandManagerBase* manager, const std::string &filename = "");
    ~DummyCommandReceiver() { }
    virtual void receive_command();
	virtual void send_packet(const datatype::String& msg);
	virtual void send_packet(int msg);
	virtual void add_command(command::Command*);
protected:
	core::manager::CommandManagerBase* manager_;
	std::ifstream* ifs_;
	std::string last_command_;
};


} /* End of namespace stf::core::devicedriver::cmhandler */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_cmhandler_ICommandReceiver_h
