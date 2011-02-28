/**
 * @file   OutputAll.h
 * @brief  データプールの内容を全て出力するテレメトリ生成ストラテジ．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_telemetry_OutputAll_h
#define stf_core_strategy_telemetry_OutputAll_h

#include "ITelemetryStrategy.h"
#include "../../../GlobalObject.h"
#include "../StrategyBase.h"
#include "../../datapool/Datapool.h"
#include "../../event/EventBase.h"
#include "../../devicedriver/tmhandler/ITelemetryStoragable.h"
#include "../../../interface/Iterator.h"
#include "../../../datatype/IAocsData.h"
#include "../../../datatype/List.h"
#include "../../../interface/Iterator.h"

namespace stf {
namespace core {
namespace strategy {
namespace telemetry {

//! データプールの内容を全て出力するテレメトリ生成ストラテジ．
/*! 
	@tparam T     出力時にキャストする型．
	@tparam SCALE キャスト前に掛ける係数．

	@code 
	OutputAll<unsigned short, 100> output;//データプールから取ったdouble値を100倍し，unsigned shortにキャストしてからストレージに渡す
	OutputAll output;//データプールの値をそのままストレージに渡す
	@endcode
*/
template<class T = double, int SCALE = 1>
class OutputAll : public StrategyBase,  virtual public ITelemetryStrategy, virtual public interface::Iterator{
public:
	OutputAll(int instance_id, devicedriver::tmhandler::ITelemetryStoragable* storage,
		const core::datapool::AocsDataPool* pool,
		const core::datapool::EventDataPool* eventpool
		) : StrategyBase(instance_id, "OutputAll"), storage_(storage), datapooliter_(pool)
	{
		this->createindex_(pool);
		this->tmlistiter_ = this->tmlist_.begin();
	}
	~OutputAll(){}
	virtual void write_to_telemetry();
	virtual void add_tmlist(interface::Iterator* tm){ this->tmlist_.add(*tm);}
	virtual void remove_tmlist(interface::Iterator* tm) { this->tmlist_.remove(*tm);}
    virtual void init();
	virtual bool end();
	virtual void operator ++();
	virtual double operator()();
protected:
	datatype::List<interface::Iterator> tmlist_;
	datatype::List<interface::Iterator>::iterator tmlistiter_;
	devicedriver::tmhandler::ITelemetryStoragable* storage_;
	core::datapool::AocsDataPoolIterator datapooliter_;
	//const core::datapool::EventDataPool* eventpool_;
	void write_(const double* data, int length);
	void createindex_(const core::datapool::AocsDataPool* pool);
};

template<class T, int SCALE>
void OutputAll<T, SCALE>::init(){
	this->datapooliter_.init();
	datatype::List<interface::Iterator>::iterator it = tmlist_.begin();
	while(it != tmlist_.end()){
		(*it).init();
		++it;
	}
	this->tmlistiter_ = this->tmlist_.begin();
}

template<class T, int SCALE>
bool OutputAll<T, SCALE>::end(){
	if(!this->datapooliter_.end()) return false;
	datatype::List<interface::Iterator>::iterator it = tmlist_.begin();
	while(it != tmlist_.end()){
		if(!(*it).end()) return false;
		++it;
	}
	return true;//すべてのイテレータが走査完了していたときだけtrue
}

template<class T, int SCALE>
void OutputAll<T, SCALE>::operator ++(){
	if(!this->datapooliter_.end()){
		++(this->datapooliter_);
	}
	else{
		++(*this->tmlistiter_);
		if((*this->tmlistiter_).end()){
			++this->tmlistiter_;
		}
	}	
}

template<class T, int SCALE>
double OutputAll<T, SCALE>::operator()(){
	if(!this->datapooliter_.end()){
		return this->datapooliter_();
	}
	else{
		return (*this->tmlistiter_)();
	}
}

template<class T, int SCALE>
void OutputAll<T, SCALE>::write_to_telemetry(){
	(*this->storage_) << this->clock_->get_time().total_milliseconds();
	this->datapooliter_.init();
	while(!datapooliter_.end()){
		(*this->storage_) << (T)(SCALE * datapooliter_());
		++datapooliter_;
	}
	
	this->storage_->endl();	
}

template<class T, int SCALE>
void OutputAll<T, SCALE>::createindex_(const core::datapool::AocsDataPool* pool)
{
	(*this->storage_) << "Time(ms)";
	for(int i = 0; i < pool->rows(); i++){
		if(pool->is_created(i)){
			const double* data = pool->get(i)->to_stream();
			for(int j = 0; j < pool->get(i)->stream_length(); j++){
				(*this->storage_) << pool->getname(i).to_char();
			}
		}
	}
	this->storage_->endl();
}

template<class T, int SCALE>
void OutputAll<T, SCALE>::write_(const double* data, int length)
{
	for(int i = 0; i < length; i++){
		(*this->storage_) << data[i];
	}
}



} /* End of namespace stf::core::strategy::telemetry */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_strategy_telemetry_OutputAll_h