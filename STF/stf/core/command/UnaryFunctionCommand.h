/**
 * @file   UnaryFunctionCommand.h
 * @brief  １引数のファンクタやメンバ関数を起動するコマンド．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_command_UnaryFunctionCommand_h
#define stf_core_command_UnaryFunctionCommand_h

#include "Command.h"
#include "../functor/Functor.h"

namespace stf {
namespace core {
namespace command {

//! 1引数のファンクタを起動するコマンド．
/*! 引数がintの場合，init関数で引数の再設定が可能．
	@code
	UnaryFunctorCommand<int> command_prototype(t, functor, 0);

	UnaryFunctorCommand<int>* newcommand = command_prototype.clone();
	int[] param = { 1 };
	//引数を1に変更
	newcommand->init(param, 1);
	@endcode
	@tparam T ファンクタ起動時の引数型．
*/
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
		(*func_)(arg_);
	}
private:
	functor::IUnAryFunctor<T>* func_;
	T arg_;
};

template<>
void UnaryFunctorCommand<int>::init(int* params, int paramsize);

//! 1引数のメンバ関数を起動するコマンド．
/*! 戻り値型Uのメンバ関数を呼び出し，返答をコマンドパケットに送出する. 
	@tparam T   メンバ関数を保持するクラス．
	@tparam U   メンバ関数の戻り値型．
	@tparam ARG メンバ関数の引数型．
*/
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
		U response = (*obj_.*f_)(arg_);
		this->rcv_->send_packet(response);
	}
private:
	T* obj_;
	Func f_;
	ARG arg_;
};

//! 1引数のメンバ関数を起動するコマンド．(void特殊化版)
/*! 戻り値型voidのメンバ関数を呼び出す. 
	@tparam T   メンバ関数を保持するクラス．
	@tparam ARG メンバ関数の引数型．
*/
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
		(*obj_.*f_)(arg_);
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
