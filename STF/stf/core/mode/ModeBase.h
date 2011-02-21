/**
 * @file   ModeBase.h
 * @brief  モードの基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_mode_ModeBase_h
#define stf_core_mode_ModeBase_h

#include "../../RootObject.h"
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
	ModeBaseを直接インスタンス化したのち，addlistでアルゴリズム定義を付け加える．
*/
class ModeBase : public RootObject , virtual public StrategyHolder{
public:
	ModeBase(int instance_id, const datatype::String& name) : RootObject(instance_id, name){};
	virtual const datatype::String& name() const { return this->name_; }
	~ModeBase(){}
private:
	ModeBase() : RootObject(0,"err!/ModeBase"){}
};

} /* End of namespace stf::core::mode */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_mode_ModeBase_h
