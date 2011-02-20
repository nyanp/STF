/**
 * @file   ICommandReceiver.h
 * @brief  受信機からコマンドを受け取り，応答を返却するデバイスの抽象インターフェース．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_cmhandler_ICommandReceiver_h
#define stf_core_devicedriver_cmhandler_ICommandReceiver_h

namespace stf {
namespace datatype {
class String;
}
namespace core {
namespace command {
class Command;
}
namespace devicedriver {
namespace cmhandler {

//! 受信機からコマンドを受け取り，応答を返却するデバイスの抽象インターフェース．
/*! 
*/
class ICommandReceiver {
public:
	//! 外部通信機からコマンドを受け取る
    virtual void receive_command() = 0;
	//! 外部通信機にコマンドの応答を送信する．
	virtual void send_packet(const datatype::String& msg) = 0;
	//! 外部通信機にコマンドの応答を送信する．
	virtual void send_packet(int msg) = 0;
	//! コマンドをコマンドマネージャが保持するコマンドリストに挿入する
	virtual void add_command(command::Command*) = 0;
    virtual ~ICommandReceiver() { }
};


} /* End of namespace stf::core::devicedriver::cmhandler */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_cmhandler_ICommandReceiver_h
