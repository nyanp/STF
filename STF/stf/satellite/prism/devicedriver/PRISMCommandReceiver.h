/**
 * @file   PRISMCommandReceiver.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_cmhandler_PRISMCommandReceiver_h
#define stf_core_devicedriver_cmhandler_PRISMCommandReceiver_h

#include <fstream>
#include <cstdio>
#include <cstring>
#include "../../../datatype/String.h"
#include "../../../core/devicedriver/cmhandler/ICommandReceiver.h"
#include "../../../RootObject.h"
#include "../../../core/environment/Simulator.h"
#include "../../../core/command/Command.h"
#include "../../../core/manager/CommandManagerBase.h"
#include "../../../util/Cout.h"
#include "../PRISMfwd.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace cmhandler {


template<class T>
core::command::Command* __prism_powercmd_analyze(char* cmd, int* params, int paramlength, const datatype::Time& t, const stf::PRISMGlobal<T>* g);
template<class T>
core::command::Command* __prism_cdhcmd_analyze(char* cmd, int* params, int paramlength, const datatype::Time& t, const stf::PRISMGlobal<T>* g);
template<class T>
core::command::Command* __prism_adcscmd_analyze(char* cmd, int* params, int paramlength, const datatype::Time& t, const stf::PRISMGlobal<T>* g);

template<>
core::command::Command* __prism_powercmd_analyze<environment::Simulator<app::PRISM> >(char* cmd, int* params, int paramlength, const datatype::Time& t, const PRISMGlobal<environment::Simulator<app::PRISM> >*);
template<>
core::command::Command* __prism_cdhcmd_analyze<environment::Simulator<app::PRISM> >(char* cmd, int* params, int paramlength, const datatype::Time& t, const PRISMGlobal<environment::Simulator<app::PRISM> >*);
template<>
core::command::Command* __prism_adcscmd_analyze<environment::Simulator<app::PRISM> >(char* cmd, int* params, int paramlength, const datatype::Time& t, const PRISMGlobal<environment::Simulator<app::PRISM> >*);


//
// 通信系CPUとのインターフェースを成すコマンドレシーバのデバッグ用具象クラス．
//  プル型のコマンド（通信系からの要求をもとに，適切な値を返す）に対しては
template<class T>
class PRISMCommandReceiver: virtual public ICommandReceiver, public RootObject {
public:
    virtual void receive_command();
	virtual void send_packet(const datatype::String& msg);
	virtual void send_packet(int msg);
	virtual void add_command(command::Command*);
	PRISMCommandReceiver( core::manager::CommandManagerBase* manager, const datatype::String& filename, PRISMGlobal<T>* global)
		: RootObject("PRISMReceiver"), manager_(manager), global_(global){
			this->ifs_ = new typename T::InputFileStream(filename.to_char());
	}
    ~PRISMCommandReceiver() { }
private:
	void analyzeCommand_(char* cmd);
	core::manager::CommandManagerBase* manager_;
	PRISMGlobal<T>* global_;
	typename T::InputFileStream* ifs_;
};

//外部デバイスからコマンドの受信を行う．
template<class T>
void PRISMCommandReceiver<T>::receive_command()
{
}

//デバッグ用の特殊化．外部ファイルから1行ずつ読み込み，
template<> void PRISMCommandReceiver<environment::Simulator<app::PRISM> >::receive_command();


// デバッグ用なので送信機に送る変わりにコンソールに出力する
template<class T>
void PRISMCommandReceiver<T>::send_packet(const datatype::String& msg)
{
	util::cout << "downlink:" << msg << "at:" << this->clock_->get_time() << util::endl;
}

// デバッグ用なので送信機に送る変わりにコンソールに出力する
template<class T>
void PRISMCommandReceiver<T>::send_packet(int msg)
{
	util::cout << "downlink:" << msg << "at:" << this->clock_->get_time() << util::endl;
}
template<class T>
void PRISMCommandReceiver<T>::add_command(command::Command* cmd)
{
	this->manager_->add_command(cmd);
	cmd->connectReceiver(this);
}


//コマンドを解釈して，対応するオブジェクトを投げる
template<class T>
void PRISMCommandReceiver<T>::analyzeCommand_(char* cmd)
{
	char subsystem;
	char* cmd;
	char* params;
	int paramlength;
	//コマンド解釈部

	//
	const datatype::Time t = this->clock_->get_time();
	switch(subsystem)
	{
	case 'p':
		this->add_command(__prism_powercmd_analyze(cmd, params, paramlength, t, this->global_));
		break;

	case 'c':
		this->add_command(__prism_cdhcmd_analyze(cmd, params, paramlength, t, this->global_));
		break;
	case 'a':
		this->add_command(__prism_adcscmd_analyze(cmd, params, paramlength, t, this->global_));
		break;
	default:
		util::cout << "command parse error" << util::endl;
		break;
	}

}


} /* End of namespace stf::core::devicedriver::cmhandler */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_cmhandler_ICommandReceiver_h
