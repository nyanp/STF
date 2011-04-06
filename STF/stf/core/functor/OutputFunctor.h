/**
 * @file   OutputFunctor.h
 * @brief  出力ファンクタ群．STFではFunctorのコンストラクタに渡して使用される
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 * @todo   出力ファンクタのバリエーション拡充
 */
#ifndef stf_core_functor_OutputFunctor_h
#define stf_core_functor_OutputFunctor_h

#include "../../datatype/String.h"

namespace stf {
namespace core {
namespace manager {
class ModeManager;
}
namespace mode {
class Mode;
}
namespace functor {

//! コンストラクタで与えた文字列を標準出力に吐き出すだけの出力ファンクタ．
/*! 
*/
struct MSG {
	MSG(const datatype::String& msg) : msg_(msg) {}
	void operator()() const ;
private:
	const datatype::String msg_;
};

//! モード変更を実施する出力ファンクタ．
/*! 
*/
struct ModeChangeFunc{
	ModeChangeFunc(core::manager::ModeManager* modeman, const core::mode::Mode& next) : next_(next), modeman_(modeman){}
	int operator()() const;
private:
	const core::mode::Mode& next_;
	core::manager::ModeManager* modeman_;
};

} /* End of namespace stf::core::fuctor */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_functor_OutputFunctor_h
