/**
 * @file   GetCommand.h
 * @brief  GetterやイテレータによってSTF内部状態を応答するコマンド群．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_command_GetCommand_h
#define stf_core_command_GetCommand_h

#include "Command.h"
#include "../../interface/Iterator.h"

namespace stf {
namespace core {
namespace command {

template<class T, class U>
class GetCommand : public Command {
	typedef U (T::*Func)(void) const;
public:
	GetCommand(const datatype::Time& t, T* obj, Func f)
		: Command(t,"GetCommand"), obj_(obj), f_(f){}
	~GetCommand(){}
	virtual void init(int* params, int paramsize){}
	virtual Command* clone(const datatype::Time& t){
		return new GetCommand(t,obj_,f_);
	}
	virtual void execute(){
		U response = (*obj_.*f_)();
		this->rcv_->send_packet(response);
	}
private:
	Func f_;
	T* obj_;

};

template<class T, class Iterator, class Targ, int SCALE>
class GetIteratorCommand : public Command {
	typedef Targ (T::*Func)(void) const;
public:
	GetIteratorCommand(const datatype::Time& t, T* obj, Func f)
		: Command(t,"GetCommand"), obj_(obj), f_(f){}
	~GetIteratorCommand(){}
	virtual void init(int* params, int paramsize){}
	virtual Command* clone(const datatype::Time& t){
		return new GetIteratorCommand<T,Iterator,Targ,SCALE>(t,obj_,f_);
	}
	virtual void execute(){
		Targ response = (*obj_.*f_)();
		Iterator it(&response);
		while(!it.end()){
			this->rcv_->send_packet((int)(SCALE * it()));
			++it;
		}
	}
private:
	Func f_;
	T* obj_;
};

template<int SCALE>
class IteratorStreamCommand : public Command {
public:
	IteratorStreamCommand(const datatype::Time& t, interface::Iterator* it)
		: Command(t,"IteratorStreamCommand"), it_(it) {}
	virtual void init(int* params, int paramsize){}
	virtual Command* clone(const datatype::Time& t){
		return new IteratorStreamCommand<SCALE>(t,it_);
	}
	virtual void execute(){
		it_->init();
		while(!it_->end()){
			this->rcv_->send_packet((int)(SCALE * (*it_)()));
			++it_;
		}
	}
private:
	interface::Iterator* it_;
};


} /* End of namespace stf::core::command */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_command_GetCommand_h
