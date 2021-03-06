/**
 * @file   RootObject.h
 * @brief  数値型を除いた全クラスの基本となるクラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef RootObject_h
#define RootObject_h

#include "datatype/String.h"
#include "util/Macros.h"

namespace stf {
namespace datatype {
class Time;
class IAocsData;
}
namespace core {
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

//! 数値型を除いた全クラスの基本となるクラス．
/*! 
	オブジェクトの生成は基本的に初期化時のみを想定しており，暗黙のコピーを禁止している．
	string型で名前を保持しているが，最終的にはサイズの無駄なので削除したい．
*/
class RootObject {
public:
	RootObject(const datatype::String& name);
	const datatype::String& name() const { return name_; }
	virtual ~RootObject(){}
	virtual int get_datapoolKey() const;

protected:
	//! オブジェクトID．メモリが割り当てられた順に番号が振られる
    const int oid_;
	//! オブジェクト名．
	const datatype::String name_;

	static core::devicedriver::clock::ITimeClock* clock_;
	static core::datapool::EventDataPool* eventdatapool_;
	//観測値が格納されるデータベースインデックス．
	int datapool_hold_index_;
	core::datapool::AocsDataPool* datapool_;

private:
    RootObject();
	DISALLOW_COPY_AND_ASSIGN(RootObject);
	static int last_oid_;
};

} /* End of namespace stf */

#endif // RootObject_h
