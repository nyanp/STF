/**
 * @file   SimpleSatelliteFactory.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef factory_SimpleSatelliteFactory_h
#define factory_SimpleSatelliteFactory_h

#include "../GlobalObject.h"
#include "../factory/SatelliteFactory.h"

#include "../core/strategy/control/Includes.h"

#include "../core/manager/Includes.h"
#include "../core/devicedriver/Includes.h"
#include "../core/datapool/Datapool.h"
#include "../core/command/Includes.h"
#include "../core/event/Includes.h"
#include "../core/functor/InputFunctor.h"
#include "../core/functor/OutputFunctor.h"
#include "../core/datapool/Datapool.h"
#include "../core/mode/ModeBase.h"

#include "../core/strategy/telemetry/Includes.h"
#include "../datatype/Time.h"
#include "../InstanceID.h"
#include "simplesatellite/SSGlobal.h"

namespace stf {
namespace factory {

template<class Env>
class SimpleSatelliteFactory : public SatelliteFactory<Env>{
public:
	SimpleSatelliteFactory(){ }//this->global_ = new SSGlobal<Env>();}
	virtual ~SimpleSatelliteFactory(){ delete this->global_; }
	virtual void create_component();
	virtual void create_funcmanager();
	virtual void create_controller();
	virtual void create_telemetry();
	virtual void create_command();
	virtual void create_functor();
	virtual void create_dataupdates();
	virtual void create_switches();
	virtual void create_additional_hotspot();
	virtual void create_mode();
	virtual void create_datapool();
	virtual Global<Env>* return_created_object(){
		return this->global_;
	}
private:
	SSGlobal<Env>* global_;
};

template<class Env>
void SimpleSatelliteFactory<Env>::create_mode(){

}


template<class Env>
void SimpleSatelliteFactory<Env>::create_component(){

}

template<class Env>
void SimpleSatelliteFactory<Env>::create_funcmanager(){

}

template<class Env>
void SimpleSatelliteFactory<Env>::create_controller(){

}

template<class Env>
void SimpleSatelliteFactory<Env>::create_command(){
}

template<class Env>
void SimpleSatelliteFactory<Env>::create_telemetry(){
}

template<class Env>
void SimpleSatelliteFactory<Env>::create_dataupdates(){
}

template<class Env>
void SimpleSatelliteFactory<Env>::create_switches(){
}

template<class Env>
void SimpleSatelliteFactory<Env>::create_functor(){
}

template<class Env>
void SimpleSatelliteFactory<Env>::create_additional_hotspot(){

}

template<class Env>
void SimpleSatelliteFactory<Env>::create_datapool(){	
}


} /* End of namespace stf::factory */
} /* End of namespace stf */




#endif // factory_SimpleSatelliteFactory_h