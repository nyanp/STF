#include "RootObject.h"
#include "GlobalObject.h"
#include "util/Ostream.h"
#include "core/devicedriver/clock/ITimeClock.h"
#include "datatype/IAocsData.h"
#include "core/datapool/Datapool.h"
#include "InstanceID.h"

namespace stf {

core::devicedriver::clock::ITimeClock* RootObject::clock_ = 0;
int RootObject::last_oid_ = 0;

RootObject::RootObject(int instance_id, const datatype::String& name) : instance_id_(instance_id), name_(name), datapool_(0)
{
	oid_ = RootObject::last_oid_++;
}

/*datatype::Time RootObject::getLastUpdateTime() const {
	datatype::Time t;
	if(this->datapool_ == 0){
		return t;
	}else {
		return this->datapool_->gettime(datapool_hold_index_);
	}
}*/
int RootObject::getDataPoolKey() const { 
	return this->datapool_hold_index_; 
}

/*
	template<typename T> void RootObject::connect(util::Type2Type<T>, int rows, const datatype::String name){ 
	this->datapool_hold_index_ = Global<ENV>::getDataPool().create(util::Type2Type<T>(),rows,name);
	datapool_ = &Global<ENV>::getDataPool(); }*/

//template<> void RootObject::connect<datatype::Quaternion>(util::Type2Type<datatype::Quaternion>, int rows, const datatype::String name);
} /* End of namespace stf */
