/**
 * @file   RootObject.cpp
 * @brief  数値型を除いた全クラスの基本となるクラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "RootObject.h"
#include "core/devicedriver/clock/ITimeClock.h"

namespace stf {

core::devicedriver::clock::ITimeClock* RootObject::clock_ = 0;
core::datapool::EventDataPool* RootObject::eventdatapool_ = 0;
int RootObject::last_oid_ = 0;

RootObject::RootObject(const datatype::String& name) : name_(name), datapool_(0), oid_(RootObject::last_oid_++){}

int RootObject::get_datapoolKey() const { 
	return this->datapool_hold_index_; 
}

} /* End of namespace stf */
