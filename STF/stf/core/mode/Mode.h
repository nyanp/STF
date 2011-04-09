/**
 * @file   Mode.h
 * @brief  モードの基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_mode_Mode_h
#define stf_core_mode_Mode_h

#include "../../RootObject.h"
#include "../../Config.h"
#include "../../util/loki/TypeManip.h"
#include "ModeHotSpot.h"

namespace stf {
namespace datatype {
class String;
}
namespace core {
namespace mode {

//! モードの基底クラス．
/*! 
	基本的にモードの多様性はインスタンスレベルで表現するため，
	Modeを直接インスタンス化したのち，addlistでアルゴリズム定義を付け加える．
*/
class Mode : public RootObject, virtual public StrategyHolder{
public:
	Mode( const datatype::String& name) : RootObject(name){}
	virtual const datatype::String& name() const { return this->name_; }
	~Mode(){}
};

} /* End of namespace stf::core::mode */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_mode_Mode_h
