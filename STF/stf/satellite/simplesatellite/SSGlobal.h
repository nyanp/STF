/**
 * @file   SSGlobal.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef satellite_simplesatellite_SSGlobal_h
#define satellite_simplesatellite_SSGlobal_h
#include "../../GlobalObject.h"
#include "../../core/manager/Includes.h"
#include "../../core/devicedriver/Includes.h"
#include "../../datatype/SatelliteModel.h"


namespace stf {
namespace factory {
template <class Env> class SSFactory;
}

template <class Env>
struct SSGlobal : public Global<Env>{
	
	virtual const datatype::Time get_global_time(){
		return this->ss_clock->get_time();
	}
	virtual const datatype::DateTime get_global_datetime(){
		return this->ss_clock->get_datetime();
	}
	virtual const datatype::SatelliteModel get_satellitemodel() const{
		return this->ss_body_;
	}
	virtual const core::datapool::AocsDataPool* get_datapool() const {
		return this->ss_aocsdatapool;
	}
	virtual const core::datapool::EventDataPool* get_eventdatapool() const {
		return this->ss_eventdatapool;
	}

	datapool::AocsDataPool* ss_aocsdatapool;
	datapool::EventDataPool* ss_eventdatapool;

	devicedriver::clock::DummyClock* ss_clock;
	datatype::SatelliteModel ss_body_;
};

} /* End of namespace stf */




#endif // satellite_simplesatellite_SSGlobal_h