/**
 * @file   PRISMControlBlock.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "PRISMControlBlock.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {

void PRISMControlBlock::set_mode(int id, int value){
	stf_assert( id < 3 );
	switch(id){
	case 0:
		this->set_ads_(value);
	case 1:
		this->set_obs_(value);
	case 2:
		this->set_acs_(value);
	default:
		break;
	}
}

// 姿勢決定系モード
void PRISMControlBlock::set_acs_(int mode){
	this->acs_mode_ = mode;
	unsigned int mask = 0x00000001;

	(mode & (mask << 0)) ? this->strategylist_[Bdot]->enable()        : this->strategylist_[Bdot]->disable() ;
	(mode & (mask << 1)) ? this->strategylist_[RateDumping]->enable() : this->strategylist_[RateDumping]->disable() ;
	(mode & (mask << 2)) ? this->strategylist_[PD]->enable() : this->strategylist_[PD]->disable() ;
	(mode & (mask << 3)) ? this->strategylist_[PID]->enable() : this->strategylist_[PID]->disable() ;
	(mode & (mask << 4)) ? this->strategylist_[LiniarCorrection]->enable() : this->strategylist_[LiniarCorrection]->disable() ;
	(mode & (mask << 6)) ? this->strategylist_[Decoupling]->enable() : this->strategylist_[Decoupling]->disable() ;
	(mode & (mask << 7)) ? this->strategylist_[GGComp]->enable() : this->strategylist_[GGComp]->disable() ;
}

// 姿勢制御系モード
void PRISMControlBlock::set_ads_(int mode){
	this->ads_mode_ = mode;
	unsigned int mask = 0x00000001;
	// センサ取得の有効・無効はadsmodeではなく別途コマンドを用意する
	(mode & (mask << 12)) ? this->strategylist_[TRIAD]->enable() : this->strategylist_[TRIAD]->disable();
	(mode & (mask << 10)) ? this->strategylist_[EKF]->enable() : this->strategylist_[EKF]->disable();

}

// 磁気系モード
void PRISMControlBlock::set_obs_(int mode){
	this->obs_mode_ = mode;
	unsigned int mask = 0x00000001;

	(mode & (mask << 1)) ? this->strategylist_[RMMEKF]->enable() : this->strategylist_[RMMEKF]->disable();

}

} /* End of namespace stf::core::mode::strategy::control */
} /* End of namespace stf::core::mode::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */