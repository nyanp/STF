/**
 * @file   Datapool.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_datapool_Datapool_h
#define stf_core_datapool_Datapool_h
#include<assert.h>
#include"DatapoolSettings.h"
#include"../../datatype/IAocsData.h"
#include"../../datatype/List.h"
#include"../../util/Ostream.h"
#include"../../RootObject.h"
#include"../../datatype/Time.h"
#include"../../datatype/StaticVector.h"
#include"../../datatype/String.h"
#include"../devicedriver/clock/ITimeClock.h"
#include "../../util/TypeList.h"
#include "../../util/Ostream.h"
#include "../../util/loki/HierarchyGenerators.h"
#include "../../util/loki/Tuple.h"
#include "../../interface/Iterator.h"

namespace stf {
namespace core {
namespace event {
class EventBase;
}
namespace devicedriver {
template<class T,int U> class CompositeInput;
template<class T,int U> class CompositeOutput;
namespace mtq{
template<class T> class MTQ;
}
namespace stt{
template<class T> class STT;
}
namespace gyro{
template<class T> class Gyro;
}
}
namespace datapool {

	
/*
template<class T> class Tupl
{
public:
	Tupl() : capacity_(0), index_(-1){}
	void create(int capacity){
		capacity_ = capacity;
		assert(capacity > 0);
		value_ = new Loki::Tuple<TYPELIST_2(datatype::Time, T)>[capacity];
	}
	void set(T value){
		index_ ++;
		//Loki::Field<0>(value_[index_]) = t;
		Loki::Field<1>(value_[index_]) = value;
	}
	const T& get(){
		return Loki::Field<1>(value_[index_]);
	}
	~Tupl(){ delete value_; }
	int capacity_;
	int index_;
	Loki::Tuple< TYPELIST_2(datatype::Time, T) >* value_;
	//T::Hold* value_;
};

template<class TList>
class DB : public Loki::GenScatterHierarchy<TList,Tupl>{
public:
	template<int i>void create(int capacity){
		Loki::Field<i>(*this).create(capacity);
	}

	template<int i,class T> const T& get(){
		return Loki::Field<i>(*this).get();
	}
	template<int i,class T> void set(T value){
		Loki::Field<i>(*this).set(value);
	}

};
*/

/*
// HotSpot: Datapoolの型指定
typedef devicedriver::CompositeOutput<devicedriver::mtq::MTQ<ENV>,3> ThreeAxisMTQ;
typedef devicedriver::CompositeInput<devicedriver::gyro::Gyro<ENV>,3> ThreeAxisGyro;
typedef devicedriver::CompositeInput<devicedriver::stt::STT<ENV>,2> TwoAxisSTT;
typedef devicedriver::gyro::Gyro<ENV> Gyro;
typedef devicedriver::stt::STT<ENV> STT;
typedef devicedriver::mtq::MTQ<ENV> MTQ;
typedef Loki::GenScatterHierarchy< TYPELIST_11( STT, STT, TwoAxisSTT, Gyro, Gyro, Gyro, ThreeAxisGyro, MTQ, MTQ, MTQ, ThreeAxisMTQ ) , Tupl> POOL;*/


//リングバッファ型のIAocsData-Timeタプルを格納するクラス．
template<class Base>
class Tuple
{
public:
	template <class T>
	Tuple(int capacity, util::Type2Type<T>, const datatype::String& name) : capacity_(capacity), index_(0), name_(name){
		assert(capacity > 0);
		this->data_ = new Base*[capacity];
		for(int i = 0; i < capacity; i++)
			this->data_[i] = new T;
		this->time_ = new datatype::Time[capacity];
	}
	~Tuple(){
		delete[] data_;
		delete[] time_;
	}
	template <class T>
	void set(const datatype::Time& time, const T& value){
		index_ ++;
		index_ %= capacity_;
		*(static_cast<T*>(data_[index_])) = value;//copy
		time_[index_] = time;//copy
		//T& dd = (static_cast<T*>(data_))[index_];
		//Base* ddd = &dd;
		Base* d = data_[index_];
	}
	template <class T>
	const T& get(){
		return *(static_cast<T*>(data_[index_]));
	}
	const datatype::Time& gettime(){
		return time_[index_];
	}
	template <class T>
	void print(){
		util::cout << "Index:" << this->index_ << util::endl;
		util::cout << "Time  /  Record" << util::endl;
		for(int i = 0; i < capacity_; i++){
			util::cout << time_[i] << "   " <<(static_cast<T*>(data_))[i] << util::endl;
		}
	}
	int size() const { return capacity_; }
	int index() const { return index_; }
	const Base* get_data_at(int index) const{ 
		assert(index < capacity_); 

		return (data_)[index_]; 
	}
	const datatype::Time& get_time_at(int index) const{ assert(index < capacity_); return time_[index]; }
	const datatype::String& name() const { return name_; }
private:
	Base** data_;
	int capacity_;
	int index_;
	datatype::String name_;//データベース名，デバッグ用
	datatype::Time* time_;

};

/*
template<class T>
class Datapool//: public RootObject
{
public:
	Datapool(int instance_id);
	~Datapool(void){}
	// 最新の値を元の型として取る
	template<class Producer> typename Producer::Hold get(int index) const{
		return table_[index]->get<Producer::Hold>();//copy
	}
	const T* get(int rows) const{
		return table_[rows]->get_data_at(table_[rows]->index());
	}
	const T* get(int rows,int cols) const{
		return table_[rows]->get_data_at(cols);
	}
	// 最新の値を取る
	datatype::Time gettime(int index) const{
		return table_[index]->gettime();//copy
	}
	const datatype::String& getname(int index) const{
		return table_[index]->name();
	}
	// 値をセット
	template<class Producer> void set(int index, const typename Producer::Hold& value){
		table_[index]->set<typename Producer::Hold>(this->clock_->getTime(),value);
	}

	template<class Producer> typename Producer::Hold& get_at(int index, int rows) const {
		return table_[index]->get_at<Producer::Hold>(rows);//copy
	}

	//初期化時にのみ使用．動的生成
	//IAocsDataをHoldしているRoot配下のクラスであれば何でも取れる
	template<class Producer> int create(Producer* producer,unsigned short capacity, const datatype::String& name = "unknown"){
		this->createdindex_++;
		this->table_[createdindex_] = new Tuple<T>(capacity,util::Type2Type<Producer::Hold>(),name);
		return createdindex_ ;
	}

	//初期化時にのみ使用．動的生成
	//IAocsDataをHoldしているRoot配下のクラスであれば何でも取れる
	template<class Datatype> int create(util::Type2Type<Datatype>,unsigned short capacity, const datatype::String& name = "unknown"){
		this->createdindex_++;
		this->table_[createdindex_] = new Tuple<T>(capacity,util::Type2Type<Datatype>(),name);
		return createdindex_ ;
	}
	//初期化時にのみ使用．動的生成
	//IAocsDataをHoldしているRoot配下のクラスであれば何でも取れる
	template<class Producer> int create(int id,unsigned short capacity, const datatype::String& name = "unknown"){
		this->createdindex_++;
		this->table_[createdindex_] = new Tuple<T>(capacity,util::Type2Type<Producer::Hold>(),name);
		return createdindex_ ;
	}

	template<class Producer> void show(int index) const{
		table_[index]->print<Producer::Hold>();
	}
	// 指定したインスタンスIDが生成したタプルへのポインタを取得（テレメトリ用）
	Tuple<T>* get_ptr(int index) {
		assert( index < kMaxDataPoolRows );
		return table_[index];
	}
	const int rows () const{ return this->kMaxDataPoolRows; }
	bool isCreated(int index) const{ 
		assert( index < kMaxDataPoolRows && index >= 0); 
		if(index < createdindex_) return true;
		else return false;
	}
private:
	Tuple<T>** table_;
	static const int kMaxDataPoolRows = 255;
	int createdindex_;
};

template<class T>
Datapool<T>::Datapool(int instance_id) : createdindex_(-1) //,RootObject(instance_id, "Datapool")
{
	this->table_ = new Tuple<T> *[kMaxDataPoolRows];
}

*/

class DataPoolBase : public RootObject
{
public:
	DataPoolBase(int instance_id): createdindex_(-1) , RootObject(instance_id, "DataPoolBase"){}
	~DataPoolBase(void){}
	const int rows () const{ return this->kMaxDataPoolRows; }
	bool isCreated(int index) const{ 
		assert( index < kMaxDataPoolRows && index >= 0); 
		if(index <= createdindex_) return true;
		else return false;
	}
protected:
	static const int kMaxDataPoolRows = 255;
	int createdindex_;
};

class AocsDataPoolIterator;

class AocsDataPool : public DataPoolBase//: public RootObject
{
public:
	AocsDataPool(int instance_id);
	~AocsDataPool(void){}
	// 最新の値を元の型として取る
	template<class Producer> typename Producer::Hold get(int index) const{
		return table_[index]->get<Producer::Hold>();//copy
	}
	const datatype::IAocsData* get(int rows) const;
	const datatype::IAocsData* get(int rows,int cols) const;
	template<class T>const T& get(int rows){
		return this->table_[rows]->get<T>();
	}
	// 最新の値を取る
	datatype::Time gettime(int index) const;
	const datatype::String& getname(int index) const;
	// 値をセット
	template<class Producer> void set(int index, const typename Producer::Hold& value){
		table_[index]->set<typename Producer::Hold>(this->clock_->getTime(),value);
	}
	template<class Producer> typename Producer::Hold& get_at(int index, int rows) const {
		return table_[index]->get_at<Producer::Hold>(rows);//copy
	}
	//初期化時にのみ使用．動的生成
	//IAocsDataをHoldしているRoot配下のクラスであれば何でも取れる
	template<class Producer> int create(Producer* producer,unsigned short capacity, const datatype::String& name = "unknown"){
		this->createdindex_++;
		this->table_[createdindex_] = new Tuple<datatype::IAocsData>(capacity,util::Type2Type<Producer::Hold>(),name);
		return createdindex_ ;
	}
	//初期化時にのみ使用．動的生成
	//IAocsDataをHoldしているRoot配下のクラスであれば何でも取れる
	template<class Datatype> int create(util::Type2Type<Datatype>,unsigned short capacity, const datatype::String& name = "unknown"){
		this->createdindex_++;
		this->table_[createdindex_] = new Tuple<datatype::IAocsData>(capacity,util::Type2Type<Datatype>(),name);
		return createdindex_ ;
	}
	//初期化時にのみ使用．動的生成
	//IAocsDataをHoldしているRoot配下のクラスであれば何でも取れる
	template<class Producer> int create(int id,unsigned short capacity, const datatype::String& name = "unknown"){
		this->createdindex_++;
		this->table_[createdindex_] = new Tuple<datatype::IAocsData>(capacity,util::Type2Type<Producer::Hold>(),name);
		return createdindex_ ;
	}
	template<class Producer> void show(int index) const{
		table_[index]->print<Producer::Hold>();
	}
	// 指定したインスタンスIDが生成したタプルへのポインタを取得（テレメトリ用）
	Tuple<datatype::IAocsData>* get_ptr(int index) ;
private:
	//template<class T, int i> friend class AocsDataPoolIterator;
	Tuple<datatype::IAocsData>** table_;
};

class EventDataPool : public DataPoolBase//: public RootObject
{
public:
	EventDataPool(int instance_id);
	~EventDataPool(void){}
	// 最新の値を元の型として取る
	template<class Producer> typename Producer::Hold get(int index) const{
		return table_[index]->get<Producer::Hold>();//copy
	}
	const core::event::EventBase* get(int rows) const;
	const core::event::EventBase* get(int rows,int cols) const;
	// 最新の値を取る
	datatype::Time gettime(int index) const;
	const datatype::String& getname(int index) const;
	// 値をセット
	template<class Producer> void set(int index, const typename Producer::Hold& value){
		table_[index]->set<typename Producer::Hold>(this->clock_->getTime(),value);
	}

	template<class Producer> typename Producer::Hold& get_at(int index, int rows) const {
		return table_[index]->get_at<Producer::Hold>(rows);//copy
	}

	//初期化時にのみ使用．動的生成
	//IAocsDataをHoldしているRoot配下のクラスであれば何でも取れる
	template<class Producer> int create(Producer* producer,unsigned short capacity, const datatype::String& name = "unknown"){
		this->createdindex_++;
		this->table_[createdindex_] = new Tuple<core::event::EventBase>(capacity,util::Type2Type<Producer::Hold>(),name);
		return createdindex_ ;
	}

	//初期化時にのみ使用．動的生成
	//IAocsDataをHoldしているRoot配下のクラスであれば何でも取れる
	template<class Datatype> int create(util::Type2Type<Datatype>,unsigned short capacity, const datatype::String& name = "unknown"){
		this->createdindex_++;
		this->table_[createdindex_] = new Tuple<core::event::EventBase>(capacity,util::Type2Type<Datatype>(),name);
		return createdindex_ ;
	}
	//初期化時にのみ使用．動的生成
	//IAocsDataをHoldしているRoot配下のクラスであれば何でも取れる
	template<class Producer> int create(int id,unsigned short capacity, const datatype::String& name = "unknown"){
		this->createdindex_++;
		this->table_[createdindex_] = new Tuple<core::event::EventBase>(capacity,util::Type2Type<Producer::Hold>(),name);
		return createdindex_ ;
	}

	template<class Producer> void show(int index) const{
		table_[index]->print<Producer::Hold>();
	}
	// 指定したインスタンスIDが生成したタプルへのポインタを取得（テレメトリ用）
	Tuple<core::event::EventBase>* get_ptr(int index) ;
private:
	Tuple<core::event::EventBase>** table_;
};

//すべての列の最新データをなめるイテレータ
class AocsDataPoolIterator : public interface::Iterator {
public:
	AocsDataPoolIterator(const AocsDataPool* pool) : pool_(pool), index_(0), rows_(0) {
		focusrow_(0);
	}
	virtual void init(){
		rows_ = 0;
		focusrow_(rows_);
	}
	virtual bool end(){
		if(pool_->isCreated(rows_)) return false;
		else return true;
	}
	virtual void operator ++() { 
		index_ ++;
		if(index_ >= localstreamsize_){//次の列へ
			rows_++;
			focusrow_(rows_);
		}
	}
	virtual double operator()() {
		return this->localstream_[index_] ;		
	}
private:
	void focusrow_(int row){
		if(!pool_->isCreated(rows_)) return;
		const datatype::IAocsData* d = pool_->get(row);
		localstream_ = d->toStream();
		localstreamsize_ = d->getStreamLength();
		index_ = 0;
	}
	const AocsDataPool* pool_;
	const double* localstream_;
	int localstreamsize_;
	int index_;
	int rows_;
};


//すべての列の最新データをなめるイテレータ
class EventDataPoolIterator : public interface::Iterator {
public:
	EventDataPoolIterator(const EventDataPool* pool) : pool_(pool), index_(0), rows_(0) {
		focusrow_(0);
	}
	virtual void init(){
		rows_ = 0;
		focusrow_(rows_);
	}
	virtual bool end(){
		if(pool_->isCreated(rows_)) return false;
		else return true;
	}
	virtual void operator ++() { 
		index_ ++;
		if(index_ >= localstreamsize_){//次の列へ
			rows_++;
			focusrow_(rows_);
		}
	}
	virtual double operator()() {
		return 0;//not implemented yet	
	}
private:
	void focusrow_(int row){
		if(!pool_->isCreated(rows_)) return;
		const core::event::EventBase* d = pool_->get(row);
		//d->
		index_ = 0;
	}
	const EventDataPool* pool_;
	//const double* localstream_;
	int localstreamsize_;
	int index_;
	int rows_;
};

/*
template<class Class>
class DataBase_ {
public:
	static const Class& get() {
		assert(iscreated_ && index_ > 0);
		return data_[index_ - 1];
	}
	static const Class& get_at(int index)  {
		assert(index < poolsize && iscreated_);
		return data_[index];
	}	
	static void set(const Class& value){
		assert(index_ < poolsize && iscreated_);
		data_[index_] = value;//copy to database
		index_++;
	}
private:
	DataBase_() {}
	~DataBase_(){ delete[] data_;}
	DataBase_(const DataBase_& rhs){}
	DataBase_& operator = (const DataBase_& rhs){}

	static void init_(unsigned short capacity){
		assert(capacity_ == 0);
		assert(capacity > 0);
		index_ = 0;
		capacity_ = size;
		data_ = new Class[size];
	}
	friend class Datapool;
	static unsigned short capacity_;
	static unsigned char index_;
	static Class** data_;
};

template <class Class> unsigned short DataBase_<Class>::capacity_;
template <class Class> int DataBase_<Class>::index_;
template <class Class> Class* DataBase_<Class>::data_;
*/

} /* End of namespace stf::core::datapool */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_datapool_Datapool_h

