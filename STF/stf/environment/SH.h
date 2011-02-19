#ifndef stf_environment_SH_h
#define stf_environment_SH_h


#include "IODriverBase.h"

namespace stf {
namespace environment {


class SHSPI;
class SHUART;
class SHOstream;
class SHIstream;

struct SH7145 {
	template<int i>class GPIO : public GPIOBase<i> {};
	typedef SHSPI SPI;
	typedef SHUART UART;
	typedef SHOstream OutputStream;
	typedef SHIstream InputStream;
};

class SHSPI : public SPIBase {

};

class SHUART : public UARTBase {


};

class SHOstream {

};

class SHIstream {

};


} /* End of namespace stf::environment */
} /* End of namespace stf */

#endif // aocs_environment_Simulator_h
