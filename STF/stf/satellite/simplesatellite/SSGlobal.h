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

namespace stf {
namespace factory {
template <class Env> class SSFactory;
}

template <class Env>
struct SSGlobal : public Global<Env>{
	/*
	virtual const datatype::Time get_global_time(){
		return this->pr_clock->get_time();
	}
	virtual const datatype::DateTime get_global_datetime(){
		return this->pr_clock->get_datetime();
	}
	virtual const datatype::SatelliteModel get_satellitemodel() const{
		return this->prism_body_;
	}
	virtual const core::datapool::AocsDataPool* get_datapool() const {
		return this->pr_aocsdatapool;
	}
	virtual const core::datapool::EventDataPool* get_eventdatapool() const {
		return this->pr_eventdatapool;
	}*/

};

} /* End of namespace stf */




#endif // satellite_simplesatellite_SSGlobal_h