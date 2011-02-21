/**
 * @file   ITelemetryStoragable.h
 * @brief  テレメトリデータのストレージに対する抽象インターフェース．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_tmhandler_ITelemetryStoragable_h
#define stf_core_devicedriver_tmhandler_ITelemetryStoragable_h

#include "../../../datatype/String.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace tmhandler {

//! テレメトリデータのストレージに対する抽象インターフェース．
/*! */
class ITelemetryStoragable {
public:
    virtual void logging(int value, int address)  = 0;
    virtual void logging(double value, int address)  = 0;
    virtual void logging(datatype::String value, int address)  = 0;
    virtual ITelemetryStoragable &operator <<(int value)  = 0;
    virtual ITelemetryStoragable &operator <<(double value)  = 0;
    virtual ITelemetryStoragable &operator <<(const char* value)  = 0;
    virtual ITelemetryStoragable &endl()  = 0;
public:
    // virtual destructor for interface 
    virtual ~ITelemetryStoragable() { }
};

} /* End of namespace stf::core::devicedriver::tmhandler */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_tmhandler_ITelemetryStoragable_h
