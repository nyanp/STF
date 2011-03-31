/**
 * @file   SelectingOutput.h
 * @brief  指定したイテレータをテレメトリとして整形するテレメトリ生成ストラテジ．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 * @todo   CreateIndexの実装
 */
#ifndef stf_core_strategy_telemetry_SelectingOutput_h
#define stf_core_strategy_telemetry_SelectingOutput_h
#include "ITelemetryStrategy.h"
#include "../../../GlobalObject.h"
#include "../StrategyBase.h"
#include "../../datapool/Datapool.h"
#include "../../event/Event.h"
#include "../../devicedriver/tmhandler/ITelemetryStoragable.h"
#include "../../../interface/Iterator.h"
#include "../../../datatype/IAocsData.h"
#include "../../devicedriver/clock/DummyClock.h"
#include "../../../datatype/List.h"
#include "../../../interface/Iterator.h"

namespace stf {
namespace core {
namespace strategy {
namespace telemetry {

//! 指定したイテレータをテレメトリとして整形するテレメトリ生成ストラテジ．
/*! 
	@tparam T     出力時にキャストする型．
	@tparam SCALE キャスト前に掛ける係数．

	@code 
	SelectingOutput<unsigned short, 100> output;//データプールから取ったdouble値を100倍し，unsigned shortにキャストしてからストレージに渡す
	SelectingOutput output;//データプールの値をそのままストレージに渡す
	@endcode
*/
template<class T, int SCALE>
class SelectingOutput : public StrategyBase,  virtual public ITelemetryStrategy, virtual public interface::Iterator{
public:
	SelectingOutput(int instance_id, devicedriver::tmhandler::ITelemetryStoragable* storage,
		const core::datapool::AocsDataPool* pool,
		const core::datapool::EventDataPool* eventpool
		) : StrategyBase(instance_id, "SelectingOutput"), storage_(storage), pool_(pool)
	{
		this->createindex_(pool);
		this->tmlistiter_ = this->tmlist_.begin();
	}
	~SelectingOutput(){}
	virtual void write_to_telemetry();
	virtual void add_tmlist(interface::Iterator* tm){ this->tmlist_.add(*tm);}
	//初期化時にのみ呼ぶことができる
	void set_tmlist_by_datapoolrows(int index){
		interface::DataIterator* it = new interface::DataIterator(this->pool_->get(index));
		this->tmlist_.add(*it);
	}
	virtual void remove_tmlist(interface::Iterator* tm) { this->tmlist_.remove(*tm);}
    virtual void init();
	virtual bool end();
	virtual void operator ++();
	virtual double operator()();
protected:
	datatype::List<interface::Iterator> tmlist_;
	datatype::List<interface::Iterator>::iterator tmlistiter_;
	devicedriver::tmhandler::ITelemetryStoragable* storage_;
	const core::datapool::AocsDataPool* pool_;
	//const core::datapool::EventDataPool* eventpool_;
	void write_(const double* data, int length);
	void createindex_(const core::datapool::AocsDataPool* pool);
};

template<class T, int SCALE>
void SelectingOutput<T, SCALE>::init(){
	datatype::List<interface::Iterator>::iterator it = tmlist_.begin();
	while(it != tmlist_.end()){
		(*it).init();
		++it;
	}
	this->tmlistiter_ = this->tmlist_.begin();
}

template<class T, int SCALE>
bool SelectingOutput<T, SCALE>::end(){
	datatype::List<interface::Iterator>::iterator it = tmlist_.begin();
	while(it != tmlist_.end()){
		if(!(*it).end()) return false;
		++it;
	}
	return true;//すべてのイテレータが走査完了していたときだけtrue
}

template<class T, int SCALE>
void SelectingOutput<T, SCALE>::operator ++(){
	++(*this->tmlistiter_);
	if((*this->tmlistiter_).end()){
		++this->tmlistiter_;
	}	
}

template<class T, int SCALE>
double SelectingOutput<T, SCALE>::operator()(){
	return (*this->tmlistiter_)();
}

template<class T, int SCALE>
void SelectingOutput<T, SCALE>::write_to_telemetry(){
	(*this->storage_) << this->clock_->get_time().total_milliseconds();

	datatype::List<interface::Iterator>::iterator it = this->tmlist_.begin();
	while(it != tmlist_.end()){
		while(!(*it).end()){
			(*this->storage_) << (*it)();
		}
	}

	this->storage_->endl();	
}

template<class T, int SCALE>
void SelectingOutput<T, SCALE>::createindex_(const core::datapool::AocsDataPool* pool)
{
	(*this->storage_) << "Time(ms)";
	//TBD
	this->storage_->endl();
}

template<class T, int SCALE>
void SelectingOutput<T, SCALE>::write_(const double* data, int length)
{
	for(int i = 0; i < length; i++){
		(*this->storage_) << data[i];
	}
}



} /* End of namespace stf::core::strategy::telemetry */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_strategy_telemetry_SelectingOutput_h