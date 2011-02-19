#include "Datapool.h"

namespace stf {
namespace core {
namespace datapool {


AocsDataPool::AocsDataPool(int instance_id): DataPoolBase(instance_id){
	this->table_ = new Tuple<datatype::IAocsData>*[kMaxDataPoolRows];
}

const datatype::IAocsData* AocsDataPool::get(int rows) const{
	return table_[rows]->get_data_at(table_[rows]->index());
}
const datatype::IAocsData* AocsDataPool::get(int rows,int cols) const{
	return table_[rows]->get_data_at(cols);
}
// 最新の値を取る
datatype::Time AocsDataPool::gettime(int index) const{
	return table_[index]->gettime();//copy
}
const datatype::String& AocsDataPool::getname(int index) const{
	return table_[index]->name();
}


// 指定したインスタンスIDが生成したタプルへのポインタを取得（テレメトリ用）
Tuple<datatype::IAocsData>* AocsDataPool::get_ptr(int index) {
	assert( index < kMaxDataPoolRows );
	return table_[index];
}

EventDataPool::EventDataPool(int instance_id): DataPoolBase(instance_id){
	this->table_ = new Tuple<core::event::EventBase>*[kMaxDataPoolRows];
}

const core::event::EventBase* EventDataPool::get(int rows) const{
	return table_[rows]->get_data_at(table_[rows]->index());
}
const core::event::EventBase* EventDataPool::get(int rows,int cols) const{
	return table_[rows]->get_data_at(cols);
}
// 最新の値を取る
datatype::Time EventDataPool::gettime(int index) const{
	return table_[index]->gettime();//copy
}
const datatype::String& EventDataPool::getname(int index) const{
	return table_[index]->name();
}


// 指定したインスタンスIDが生成したタプルへのポインタを取得（テレメトリ用）
Tuple<core::event::EventBase>* EventDataPool::get_ptr(int index) {
	assert( index < kMaxDataPoolRows );
	return table_[index];
}




} /* End of namespace stf::core::datapool */
} /* End of namespace stf::core */
} /* End of namespace stf */
