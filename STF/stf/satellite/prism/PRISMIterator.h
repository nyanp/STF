/**
 * @file   PRISMIterator.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef  stf_satellite_prism_PRISMIterator_h
#define stf_satellite_prism_PRISMIterator_h

#include "../../interface/Iterator.h"
#include "PRISMEKF.h"
#include "PRISMRMMEKF.h"
#include "PRISMTRIAD.h"
#include "PRISMTelemetryStrategy.h"
#include "PRISMControlBlock.h"

namespace stf {
namespace interface {

template<int SCALE,int SIZE, class BASE>
class PRISMIteratorBase : public Iterator {
public:
	PRISMIteratorBase(const BASE* data) : data_(data), index_(0) {}
	virtual void init(){ index_ = 0;}
	virtual bool end(){ if(index_ == SIZE) return true; return false;}
	virtual void operator ++() { index_ ++; }
protected:
	int index_;
	const BASE* data_;
};


// PRISMのテレメトリに必要なEKFのテレメトリ出力を定義。
template<int SCALE>
class PRISMEKFIterator : public PRISMIteratorBase<SCALE,13,core::strategy::control::PRISMEKF> {
public:
	PRISMEKFIterator(const core::strategy::control::PRISMEKF* data): PRISMIteratorBase<SCALE,13,core::strategy::control::PRISMEKF>(data) {}
	virtual double operator()() {
		if(index_ < 4) return (SCALE * data_->q_[index_]);
		if(index_ < 7) return (SCALE * data_->bref_[index_ - 4]);
		return (SCALE * data_->P_[index_ - 7][index_ - 7]);
	}
private:
};

// PRISMのテレメトリに必要なEKFのテレメトリ出力を定義。
template<int SCALE>
class PRISMRMMEKFIterator : public PRISMIteratorBase<SCALE,3,core::strategy::control::PRISMRMMEKF> {
public:
	PRISMRMMEKFIterator(const core::strategy::control::PRISMRMMEKF* data): PRISMIteratorBase<SCALE,3,core::strategy::control::PRISMRMMEKF>(data) {}
	virtual double operator()() {		
		return data_->value_b_[index_];
	}
private:
};

// TRIADからQuaternionの推定値をテレメトリとして出力．
template<int SCALE>
class PRISMSunMagTRIADIterator : public PRISMIteratorBase<SCALE,4,core::strategy::control::PRISMSunMagTRIAD> {
public:
	PRISMSunMagTRIADIterator(const core::strategy::control::PRISMSunMagTRIAD* data): PRISMIteratorBase<SCALE,4,core::strategy::control::PRISMSunMagTRIAD>(data) {}
	virtual double operator()() {
		return data_->value_b_[index_];
	}
private:
};


class PRISMControlBlockIterator : public PRISMIteratorBase<1,3,core::strategy::control::PRISMControlBlock> {
public:
	PRISMControlBlockIterator(const core::strategy::control::PRISMControlBlock* data): PRISMIteratorBase<1,3,core::strategy::control::PRISMControlBlock>(data) {}
	virtual double operator()() {
		switch(this->index_){
		case 0:
			return data_->ads_mode_;
		case 1:
			return data_->acs_mode_;
		case 2:
			return data_->obs_mode_;
		}
		assert(0);//out of inde
		return 0;
	}
};

// TBD: not implemented yet
template<int SCALE, int DEPTH> class PRISMTelemetryIterator : public Iterator{
public:
	PRISMTelemetryIterator(const core::strategy::telemetry::PRISMTelemetryStrategy<SCALE>* data) : data_(data) {}
	virtual void init(){}
	virtual bool end(){ return true; }
	virtual void operator ++() {}
	virtual double operator()() {}
private:
	const core::strategy::telemetry::PRISMTelemetryStrategy<SCALE>* data_;

};

} /* End of namespace stf::interface */
} /* End of namespace stf */

#endif //  stf_satellite_prism_PRISMIterator_h
