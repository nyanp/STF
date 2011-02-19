
#include "EKFParamaters.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {

EKFParamaters::EKFParamaters()
: b0(3),P0(6,6)
{

}
EKFParamaters::~EKFParamaters()
{

}

} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */
