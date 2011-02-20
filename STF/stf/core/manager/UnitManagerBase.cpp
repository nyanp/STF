/**
 * @file   UnitManagerBase.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "UnitManagerBase.h"
#include "../devicedriver/IDataUpdatable.h"
#include "../mode/ModeBase.h"
#include "../../util/Ostream.h"

namespace stf {
namespace core {
namespace manager {


void UnitManagerBase::notify(const mode::ModeBase* newmode)
{
	util::cout << "unit manager update!" << util::endl;
	this->unit_list_ = newmode->getlist(SpotType());
}

void UnitManagerBase::run()
{
    //util::cout << "Uniman run:\n";
	if(unit_list_ == 0){
	//	util::cout << "skip\n";
		return;
	}
	datatype::List<HotSpot>::iterator it = unit_list_->begin();
	while(it != unit_list_->end()){
		//ここにgetTelemetryLengthを用いてストリーム長さを評価するコードが必要．TBD
		(*it).do_update();
		++it;
	}      
}


} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */