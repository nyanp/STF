/**
 * @file   HealthManagerBase.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef core_manager_HealthManager_h
#define core_manager_HealthManager_h

#include <algorithm>
#include <vector>

#include <interface/IModeChangeEventListener.h>
#include "util/Ostream.h"
#include "AOCSManager.h"

namespace interface {
class IConsistencyCheckable;
} /* End of namespace interface */
namespace core {
namespace mode {
class Mode;
} /* End of namespace core::mode */
} /* End of namespace core */
namespace interface {
class ITelemetryStoragable;
} /* End of namespace interface */

namespace core {
namespace manager {

class HealthManager : public AOCSManager, virtual public interface::IModeChangeEventListener {

 public:

    HealthManager();

    virtual ~HealthManager();

    virtual void addToChkList(interface::IConsistencyCheckable *check);

    virtual void removeFromChkList(interface::IConsistencyCheckable *check);

    virtual void clearChkList();

    void run();

    bool runnable() const ;

    void notify(const core::mode::Mode &mode);

    void writeToTelemetry(interface::ITelemetryStoragable *storage);

    int getTelemetryLength() const ;


 protected:
    std::vector< interface::IConsistencyCheckable* > check_list_;
    /* {pointer=true}*/
};

} /* End of namespace core::manager */
} /* End of namespace core */

#endif // core_manager_HealthManager_h
