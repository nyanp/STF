/**
 * @file   NJEKF.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_control_NJEKF_h
#define stf_core_strategy_control_NJEKF_h

#include "../../core/strategy/control/EKF.h"
#include "../../interface/ITelemetable.h"
#include "../../interface/Iterator.h"
#include "../../core/event/SubjectBase.h"
#include "../../core/event/Event.h"

namespace stf {
namespace interface {
template<int U> class NJEKFIterator;
}
namespace core {
namespace strategy {
namespace control {

template<int U> class NJEKFIterator;

// フレームワークのEKFを継承したNJ用のカルマンフィルタ．
// イテレータによる独自のテレメトリ生成が可能である点，
// Observerパターンによってモード変更のタイミングでパラメータ初期化が入る点が汎用EKFとの違い．
class NJEKF : public EKF, virtual public event::Observer<event::ModeChangeEvent>
{
public:
	NJEKF(int instance_id, mode::ModeBase* missionmode) : EKF(instance_id), missionmode_(missionmode){}
	virtual ~NJEKF(){}
	virtual void notify(const mode::ModeBase* value){ 
		if(value == missionmode_) return; //次が観測モードの場合はリセットしない
		this->init(); 
	}
private:
	template<int U>friend class interface::NJEKFIterator;
	const mode::ModeBase* missionmode_;
};


} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_strategy_control_input_NJEKF_h
