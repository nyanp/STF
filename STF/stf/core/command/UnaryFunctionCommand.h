#ifndef stf_core_command_UnaryFunctionCommand_h
#define stf_core_command_UnaryFunctionCommand_h

#include "Command.h"
#include "../functor/Functor.h"

namespace stf {
namespace core {
namespace command {

//1引数ファンク多を起動するコマンド
template<class T>
class UnaryFunctorCommand : public Command {
public:
	UnaryFunctorCommand(const datatype::Time& t, functor::IUnAryFunctor<T>* func, T arg)
		: func_(func), arg_(arg), Command(t,"UnaryFunctorCommand") {}
	~UnaryFunctorCommand(){}
	virtual void init(int* params, int paramsize){}
	virtual Command* clone(const datatype::Time& t){
		return new UnaryFunctorCommand<T>(t,func_,arg_);
	}
	virtual void execute(){
		(*func_)(arg_);//trigger functor
	}
private:
	functor::IUnAryFunctor<T>* func_;
	T arg_;
};

template<>
void UnaryFunctorCommand<int>::init(int* params, int paramsize);


// 引数なし，戻り値型Uのメンバ関数を呼び出し，返答をコマンドパケットに送出する
template<class T, class U, class ARG>
class UnAryMemberFunctionCommand : public Command {
	typedef U (T::*Func)(ARG);
public:
	UnAryMemberFunctionCommand(const datatype::Time& t, T* obj, Func f, ARG arg)
    : Command(t,"UnAryMemberFuncCommand"), obj_(obj), f_(f), arg_(arg) {}
	~UnAryMemberFunctionCommand(){}
	virtual void init(int* params, int paramsize){}
	virtual Command* clone(const datatype::Time& t){
		return new UnAryMemberFunctionCommand<T,U,ARG>(t,obj_,f_,arg_);
	}
	virtual void execute(){
		U response = (*obj_.*f_)(arg_);//trigger functor
		this->rcv_->sendPacket(response);
	}
private:
	T* obj_;
	Func f_;
	ARG arg_;
};

template<class T, class ARG>
class UnAryMemberFunctionCommand<T,void,ARG> : public Command {
	typedef void (T::*Func)(ARG);
public:
	UnAryMemberFunctionCommand(const datatype::Time& t, T* obj, Func f, ARG arg)
    : Command(t,"UnAryMemberFuncCommand"), obj_(obj), f_(f), arg_(arg) {}
	~UnAryMemberFunctionCommand(){}
	virtual void init(int* params, int paramsize){}
	virtual Command* clone(const datatype::Time& t){
		return new UnAryMemberFunctionCommand<T,void,ARG>(t,obj_,f_,arg_);
	}
	virtual void execute(){
		(*obj_.*f_)(arg_);//trigger functor
	}
private:
	T* obj_;
	Func f_;
	ARG arg_;
};


} /* End of namespace stf::core::command */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_command_UnaryFunctorCommand_h
