#ifndef scube_core_devicedriver_tmhandler_DummyStorage_h
#define scube_core_devicedriver_tmhandler_DummyStorage_h

namespace scube {
namespace core {
namespace devicedriver {
namespace tmhandler {

class DummyStorage {
public:
	DummyStorage(){}
	virtual ~DummyStorage(){}
	virtual void writeStream(){}
private:
};

} /* End of namespace scube::core::devicedriver::tmhandler */
} /* End of namespace scube::core::devicedriver */
} /* End of namespace scube::core */
} /* End of namespace scube */

#endif // scube_core_devicedriver_tmhandler_DummyStorage_h
