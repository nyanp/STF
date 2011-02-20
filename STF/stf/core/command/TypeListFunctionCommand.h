/**
 * @file   TypeListFunctionCommand.h
 * @brief  複数個の引数を取るメンバ関数を起動するコマンド．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_command_TypeListFunctionCommand_h
#define stf_core_command_TypeListFunctionCommand_h

#include "Command.h"
#include <assert.h>

namespace stf {
namespace core {
namespace command {

// n個のARG型を引数に取るコマンド群．
// TypeListを使えばきれいにまとめられる筈．TBD

template<class T, class ARG, int N>
class TypeListMemberFunctionCommand : public Command {
	typedef void (T::*Func)(ARG);
public:
	TypeListMemberFunctionCommand(const datatype::Time& t, T* obj, Func f, ARG arg) 
		: Command(t,"TypeListMemberFuncCommand"), obj_(obj), f_(f), arg_(arg) {}
	~TypeListMemberFunctionCommand(){}
	virtual void init(int* params, int paramsize){
		assert(paramsize >= 1);
		arg_ = (ARG)params[0];
	}
	virtual Command* clone(const datatype::Time& t){
		return new TypeListMemberFunctionCommand<T,ARG,N>(t,obj_,f_,arg_);
	}
	virtual void execute(){
		(*obj_.*f_)(arg_);//trigger functor
	}
private:
	T* obj_;
	Func f_;
	ARG arg_;
};

template<class T, class ARG>
class TypeListMemberFunctionCommand<T,ARG,2> : public Command {
	typedef void (T::*Func)(ARG,ARG);
public:
	TypeListMemberFunctionCommand(const datatype::Time& t, T* obj, Func f, ARG arg1, ARG arg2)
		: Command(t,"TypeListMemberFuncCommand"), obj_(obj), f_(f), arg1_(arg1), arg2_(arg2) {}
	~TypeListMemberFunctionCommand(){}
	virtual void init(int* params, int paramsize){
		assert(paramsize >= 2);
		arg1_ = params[0];
		arg2_ = params[1];
	}
	virtual Command* clone(const datatype::Time& t){
		return new TypeListMemberFunctionCommand<T,ARG,2>(t,obj_,f_,arg1_,arg2_);
	}
	virtual void execute(){
		(*obj_.*f_)(arg1_, arg2_);//trigger functor
	}
private:
	T* obj_;
	Func f_;
	ARG arg1_;
	ARG arg2_;
};

template<class T, class ARG>
class TypeListMemberFunctionCommand<T,ARG,3> : public Command {
	typedef void (T::*Func)(ARG,ARG,ARG);
public:
	TypeListMemberFunctionCommand(const datatype::Time& t, T* obj, Func f, ARG arg1, ARG arg2, ARG arg3)
		: Command(t,"TypeListMemberFuncCommand"), obj_(obj), f_(f), arg1_(arg1), arg2_(arg2), arg3_(arg3) {}
	~TypeListMemberFunctionCommand(){}
	virtual void init(int* params, int paramsize){
		assert(paramsize >= 3);
		arg1_ = params[0];
		arg2_ = params[1];
		arg3_ = params[2];
	}
	virtual Command* clone(const datatype::Time& t){
		return new TypeListMemberFunctionCommand<T,ARG,3>(t,obj_,f_,arg1_,arg2_,arg3_);
	}
	virtual void execute(){
		(*obj_.*f_)(arg1_, arg2_, arg3_);//trigger functor
	}
private:
	T* obj_;
	Func f_;
	ARG arg1_;
	ARG arg2_;
	ARG arg3_;
};

template<class T, class ARG>
class TypeListMemberFunctionCommand<T,ARG,6> : public Command {
	typedef void (T::*Func)(ARG,ARG,ARG,ARG,ARG,ARG);
public:
	TypeListMemberFunctionCommand(const datatype::Time& t, T* obj, Func f, ARG arg1, ARG arg2, ARG arg3, ARG arg4, ARG arg5, ARG arg6)
		: Command(t,"TypeListMemberFuncCommand"), obj_(obj), f_(f), arg1_(arg1), arg2_(arg2), arg3_(arg3), arg4_(arg4), arg5_(arg5), arg6_(arg6) {}
	~TypeListMemberFunctionCommand(){}
	virtual void init(int* params, int paramsize){
		assert(paramsize >= 6);
		arg1_ = params[0];
		arg2_ = params[1];
		arg3_ = params[2];
		arg4_ = params[3];
		arg5_ = params[4];
		arg6_ = params[5];
	}
	virtual Command* clone(const datatype::Time& t){
		return new TypeListMemberFunctionCommand<T,ARG,6>(t,obj_,f_,arg1_,arg2_,arg3_,arg4_,arg5_,arg6_);
	}
	virtual void execute(){
		(*obj_.*f_)(arg1_, arg2_, arg3_,arg4_,arg5_,arg6_);//trigger functor
	}
private:
	T* obj_;
	Func f_;
	ARG arg1_;
	ARG arg2_;
	ARG arg3_;
	ARG arg4_;
	ARG arg5_;
	ARG arg6_;
};

} /* End of namespace stf::core::command */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_command_TypeListFunctorCommand_h
