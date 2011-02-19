#include <core/mode/Mode.h>
#include <interface/IConsistencyCheckable.h>
#include <interface/ITelemetryStoragable.h>

#include "HealthManager.h"

namespace core {
namespace manager {




HealthManager::HealthManager()
{
}

HealthManager::~HealthManager()
{
}

void HealthManager::addToChkList(interface::IConsistencyCheckable *check)
{
	this->check_list_.push_back(check);
}

void HealthManager::removeFromChkList(interface::IConsistencyCheckable *check)
{
	check_list_.erase(std::remove(check_list_.begin(),check_list_.end(),check));//include algorithmが必要．一時的       
}

void HealthManager::clearChkList()
{
	this->check_list_.clear();    
}

void HealthManager::run()
{
     util::cout << "Helman run:\n";     
}

bool HealthManager::runnable() const 
{
    return true;
}

void HealthManager::notify(const core::mode::Mode &mode)
{
     util::cout << "\tmodechangeEvent on HealthManager\n";
     this->mode_ = &mode;
	 mode.setCheckList(this->check_list_);     
}

void HealthManager::writeToTelemetry(interface::ITelemetryStoragable *storage)
{
	*storage << "helMan:";
	storage->endl();    
}

int HealthManager::getTelemetryLength() const 
{
    return 0;
}

} /* End of namespace core::manager */
} /* End of namespace core */
