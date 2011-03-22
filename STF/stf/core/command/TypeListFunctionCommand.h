/**
 * @file   TypeListFunctionCommand.h
 * @brief  複数個の引数を取るメンバ関数を起動するコマンド．TypeListを使って纏めたい->TBD
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_command_TypeListFunctionCommand_h
#define stf_core_command_TypeListFunctionCommand_h

#include "../../util/stfassert.h"
#include "Command.h"
#include "../../util/Trace.h"

namespace stf {
namespace core {
namespace command {

//! N引数のメンバ関数を起動するコマンド．
/*! @tparam T   メンバ関数を保持するクラス．
	@tparam ARG 引数の型．
	@tparam N   引数の数．
 */
template<class T, class ARG, int N>
class TypeListMemberFunctionCommand : public Command {
	typedef void (T::*Func)(ARG);
public:
	TypeListMemberFunctionCommand(const datatype::Time& t, T* obj, Func f, ARG arg) 
		: Command(t, "TypeListMemberFuncCommand"), obj_(obj), f_(f), arg_(arg) {}
	~TypeListMemberFunctionCommand(){}
	virtual void init(int* params, int paramsize){
		stf_assert(paramsize >= 1);
		arg_ = (ARG)params[0];
	}
	virtual Command* clone(const datatype::Time& t){
		return new TypeListMemberFunctionCommand<T, ARG, N>(t, obj_, f_, arg_);
	}
	virtual void execute(){
		util::Trace trace(util::Trace::kCommand, name_);
		(*obj_.*f_)(arg_);//trigger functor
	}
private:
	T* obj_;
	Func f_;
	ARG arg_;
};

//! 2引数のメンバ関数を起動するコマンド．
/*! @tparam T   メンバ関数を保持するクラス．
	@tparam ARG 引数の型．
 */
template<class T, class ARG>
class TypeListMemberFunctionCommand<T, ARG, 2> : public Command {
	typedef void (T::*Func)(ARG, ARG);
public:
	TypeListMemberFunctionCommand(const datatype::Time& t, T* obj, Func f, ARG arg1, ARG arg2)
		: Command(t, "TypeListMemberFuncCommand"), obj_(obj), f_(f), arg1_(arg1), arg2_(arg2) {}
	~TypeListMemberFunctionCommand(){}
	virtual void init(int* params, int paramsize){
		stf_assert(paramsize >= 2);
		arg1_ = params[0];
		arg2_ = params[1];
	}
	virtual Command* clone(const datatype::Time& t){
		return new TypeListMemberFunctionCommand<T, ARG, 2>(t, obj_, f_, arg1_, arg2_);
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

//! 3引数のメンバ関数を起動するコマンド．
/*! @tparam T   メンバ関数を保持するクラス．
	@tparam ARG 引数の型．
 */
template<class T, class ARG>
class TypeListMemberFunctionCommand<T, ARG, 3> : public Command {
	typedef void (T::*Func)(ARG, ARG, ARG);
public:
	TypeListMemberFunctionCommand(const datatype::Time& t, T* obj, Func f, ARG arg1, ARG arg2, ARG arg3)
		: Command(t, "TypeListMemberFuncCommand"), obj_(obj), f_(f), arg1_(arg1), arg2_(arg2), arg3_(arg3) {}
	~TypeListMemberFunctionCommand(){}
	virtual void init(int* params, int paramsize){
		stf_assert(paramsize >= 3);
		arg1_ = params[0];
		arg2_ = params[1];
		arg3_ = params[2];
	}
	virtual Command* clone(const datatype::Time& t){
		return new TypeListMemberFunctionCommand<T, ARG, 3>(t, obj_, f_, arg1_, arg2_, arg3_);
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

//! 4引数のメンバ関数を起動するコマンド．
/*! @tparam T   メンバ関数を保持するクラス．
	@tparam ARG 引数の型．
 */
template<class T, class ARG>
class TypeListMemberFunctionCommand<T, ARG, 4> : public Command {
	typedef void (T::*Func)(ARG, ARG, ARG, ARG);
public:
	TypeListMemberFunctionCommand(const datatype::Time& t, T* obj, Func f, ARG arg1, ARG arg2, ARG arg3, ARG arg4)
		: Command(t, "TypeListMemberFuncCommand"), obj_(obj), f_(f), arg1_(arg1), arg2_(arg2), arg3_(arg3), arg4_(arg4) {}
	~TypeListMemberFunctionCommand(){}
	virtual void init(int* params, int paramsize){
		stf_assert(paramsize >= 4);
		arg1_ = params[0];
		arg2_ = params[1];
		arg3_ = params[2];
		arg4_ = params[3];
	}
	virtual Command* clone(const datatype::Time& t){
		return new TypeListMemberFunctionCommand<T, ARG, 4>(t, obj_, f_, arg1_, arg2_, arg3_, arg4_);
	}
	virtual void execute(){
		(*obj_.*f_)(arg1_, arg2_, arg3_, arg4_);//trigger functor
	}
private:
	T* obj_;
	Func f_;
	ARG arg1_;
	ARG arg2_;
	ARG arg3_;
	ARG arg4_;
};

//! 5引数のメンバ関数を起動するコマンド．
/*! @tparam T   メンバ関数を保持するクラス．
	@tparam ARG 引数の型．
 */
template<class T, class ARG>
class TypeListMemberFunctionCommand<T, ARG, 5> : public Command {
	typedef void (T::*Func)(ARG, ARG, ARG, ARG, ARG);
public:
	TypeListMemberFunctionCommand(const datatype::Time& t, T* obj, Func f, ARG arg1, ARG arg2, ARG arg3, ARG arg4, ARG arg5)
		: Command(t, "TypeListMemberFuncCommand"), obj_(obj), f_(f), arg1_(arg1), arg2_(arg2), arg3_(arg3), arg4_(arg4), arg5_(arg5) {}
	~TypeListMemberFunctionCommand(){}
	virtual void init(int* params, int paramsize){
		stf_assert(paramsize >= 5);
		arg1_ = params[0];
		arg2_ = params[1];
		arg3_ = params[2];
		arg4_ = params[3];
		arg5_ = params[4];
	}
	virtual Command* clone(const datatype::Time& t){
		return new TypeListMemberFunctionCommand<T, ARG, 5>(t, obj_, f_, arg1_, arg2_, arg3_, arg4_, arg5_);
	}
	virtual void execute(){
		(*obj_.*f_)(arg1_, arg2_, arg3_, arg4_, arg5_);//trigger functor
	}
private:
	T* obj_;
	Func f_;
	ARG arg1_;
	ARG arg2_;
	ARG arg3_;
	ARG arg4_;
	ARG arg5_;
};

//! 6引数のメンバ関数を起動するコマンド．
/*! @tparam T   メンバ関数を保持するクラス．
	@tparam ARG 引数の型．
 */
template<class T, class ARG>
class TypeListMemberFunctionCommand<T, ARG, 6> : public Command {
	typedef void (T::*Func)(ARG, ARG, ARG, ARG, ARG, ARG);
public:
	TypeListMemberFunctionCommand(const datatype::Time& t, T* obj, Func f, ARG arg1, ARG arg2, ARG arg3, ARG arg4, ARG arg5, ARG arg6)
		: Command(t, "TypeListMemberFuncCommand"), obj_(obj), f_(f), arg1_(arg1), arg2_(arg2), arg3_(arg3), arg4_(arg4), arg5_(arg5), arg6_(arg6) {}
	~TypeListMemberFunctionCommand(){}
	virtual void init(int* params, int paramsize){
		stf_assert(paramsize >= 6);
		arg1_ = params[0];
		arg2_ = params[1];
		arg3_ = params[2];
		arg4_ = params[3];
		arg5_ = params[4];
		arg6_ = params[5];
	}
	virtual Command* clone(const datatype::Time& t){
		return new TypeListMemberFunctionCommand<T, ARG, 6>(t, obj_, f_, arg1_, arg2_, arg3_, arg4_, arg5_, arg6_);
	}
	virtual void execute(){
		(*obj_.*f_)(arg1_, arg2_, arg3_, arg4_, arg5_, arg6_);//trigger functor
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
