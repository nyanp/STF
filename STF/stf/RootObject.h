/**
 * @file   RootObject.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef RootObject_h
#define RootObject_h

#include "InstanceID.h"
#include "datatype/String.h"
#include "Macros.h"

namespace stf {
namespace datatype {
class Time;
class IAocsData;
}
namespace core {
namespace event {
class EventBase;
}
namespace devicedriver {
namespace clock {
class ITimeClock;
}
}
namespace datapool {
class AocsDataPool;
class EventDataPool;
}
}
// 数値型を除いた全クラスの基本となるクラス．
// string型で名前を保持しているが，最終的にはサイズの無駄なので削除？
class RootObject {
public:
	RootObject(int instance_id, const datatype::String& name);
	int instance_id() const{ return instance_id_; }
	virtual ~RootObject(){}
	virtual int get_datapoolKey() const;
protected:
    int oid_;
	int instance_id_;
	datatype::String name_;
    static int last_oid_;
	static core::devicedriver::clock::ITimeClock* clock_;
	//観測値が格納されるデータベースインデックス．
	int datapool_hold_index_;
	core::datapool::AocsDataPool* datapool_;
private:
    RootObject();
	DISALLOW_COPY_AND_ASSIGN(RootObject);
};

} /* End of namespace stf */

#endif // RootObject_h
