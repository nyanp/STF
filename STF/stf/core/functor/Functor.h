/**
 * @file   Functor.h
 * @brief  衛星の異常判定や状況対処を実装するための汎用ファンクタ．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_functor_Functor_h
#define stf_core_functor_Functor_h
#include "../../util/Ostream.h"
#include "../../RootObject.h"
#include "../../datatype/String.h"
#include "../datapool/Datapool.h"
#include "../../GlobalObject.h"
#include "InputFunctor.h"
#include "OutputFunctor.h"


namespace stf {
namespace core {
namespace mode {
class ModeBase;
}
namespace functor {

//! 引数なしファンクタの抽象インターフェース．
/*! 
*/
class IFunctor {
public:
	virtual void operator()() const = 0;
};

//! 1引数ファンクタの抽象インターフェース．
/*! 
	@tparam T 引数の型．
*/
template<class T>
class IUnAryFunctor {
public:
	virtual int operator()(const T& arg) const = 0; 
};

//! ファンクタクラス．
/*! 
	入力ファンクタと出力ファンクタをポインタに保持するファンクタ．
	条件判定のアルゴリズムを入力ファンクタに，対処のアルゴリズムを出力ファンクタに分離することで，
	異常対処やアプリケーション固有の条件判定式を柔軟に生成する．
	ファンクタはSystemManagerまたはユーザーコードの中で実行される．
	@code

	extern Functor< Getter_Over<Scalar, Gyro>, MSG > functor; //ジャイロの取得値が一定値を超えたら，デバッグメッセージを出力するファンクタ
	extern Functor< Getter_Over<Scalar, Gyro>, ModeChangeFunc > functor; //ジャイロの取得値が一定値を超えたら，モードを切り替えるファンクタ

	@endcode
	@tparam InputFunctor  入力ファンクタの型．
	@tparam OutputFunctor 出力ファンクタの型．
*/
template <class InputFunctor,class OutputFunctor>
class Functor : virtual public IFunctor{
public:
	Functor(const InputFunctor* in,const OutputFunctor* out) : in_(in), out_(out) {}
	virtual void operator()() const {
		if((*in_)()){//引数なし，bool値trueが帰ってきたら
			(*out_)();//指定の動作を実施
		}
	}
private:
	const InputFunctor* in_;
	const OutputFunctor* out_;
};

//! 1引数ファンクタクラス．
/*! 
	引数無しの入力ファンクタと1引数の出力ファンクタをポインタに保持するファンクタ．
	@tparam InputFunctor  入力ファンクタの型．
	@tparam OutputFunctor 出力ファンクタの型．
	@tparam Arg           出力ファンクタの起動時引数の型．
*/
template <class InputFunctor,class OutputFunctor,class Arg>
class UnAryFunctor : public IFunctor{
public:
	UnAryFunctor(const InputFunctor* in,const OutputFunctor* out,const Arg& arg) : in_(in), out_(out), arg_(arg) {}
	virtual int operator()() const {
		if((*in_)()){//引数なし，bool値trueが帰ってきたら
			return (*out_)(arg_);//指定の動作を実施
		}
		return 0;
	}
private:
	const InputFunctor* in_;
	const OutputFunctor* out_;
	const Arg& arg_;
};

} /* End of namespace stf::core::fuctor */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_functor_Functor_h
