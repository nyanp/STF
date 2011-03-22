/**
 * @file   NJCommandReceiver.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_cmhandler_NJCommandReceiver_h
#define stf_core_devicedriver_cmhandler_NJCommandReceiver_h

#include <fstream>
#include <cstdio>
#include <cstring>
#include "../../datatype/String.h"
#include "../../core/devicedriver/cmhandler/ICommandReceiver.h"
#include "../../RootObject.h"
#include "../../environment/Simulator.h"
#include "../../core/command/Command.h"
#include "../../core/manager/CommandManager.h"
#include "../../util/Ostream.h"

namespace stf {
template<class T> struct NJGlobal;
namespace core {
namespace devicedriver {
namespace cmhandler {



//
// 通信系CPUとのインターフェースを成すコマンドレシーバのデバッグ用具象クラス．
//  プル型のコマンド（通信系からの要求をもとに，適切な値を返す）に対しては
template<class T>
class NJCommandReceiver: virtual public ICommandReceiver, public RootObject {
public:
    virtual void receive_command();
	virtual void send_packet(const datatype::String& msg);
	virtual void send_packet(int msg);
	virtual void add_command(command::Command*);
	NJCommandReceiver(int instance_id, core::manager::CommandManagerBase* manager, const datatype::String& filename,NJGlobal<T>* global)
		: RootObject(instance_id, "NJReceiver"), manager_(manager), global_(global){
			this->ifs_ = new typename T::InputFileStream(filename.to_char());
	}
    ~NJCommandReceiver() { }
private:
	core::manager::CommandManagerBase* manager_;
	NJGlobal<T>* global_;
	typename T::InputFileStream* ifs_;
};

//外部デバイスからコマンドの受信を行う．
template<class T>
void NJCommandReceiver<T>::receive_command()
{
}

//デバッグ用の特殊化．外部ファイルから1行ずつ読み込み，
template<> void NJCommandReceiver<environment::Simulator>::receive_command();


// デバッグ用なので送信機に送る変わりにコンソールに出力する
template<class T>
void NJCommandReceiver<T>::send_packet(const datatype::String& msg)
{
	util::cout << "downlink:" << msg << "at:" << this->clock_->get_time() << util::endl;
}

// デバッグ用なので送信機に送る変わりにコンソールに出力する
template<class T>
void NJCommandReceiver<T>::send_packet(int msg)
{
	util::cout << "downlink:" << msg << "at:" << this->clock_->get_time() << util::endl;
}

template<class T>
void NJCommandReceiver<T>::add_command(command::Command* cmd)
{
	this->manager_->add_command(cmd);
	cmd->connectReceiver(this);
}



} /* End of namespace stf::core::devicedriver::cmhandler */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_cmhandler_ICommandReceiver_h
