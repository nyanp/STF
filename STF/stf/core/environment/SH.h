/**
 * @file   SH.h
 * @brief  SH7145プロセッサ用の環境クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_environment_SH_h
#define stf_core_environment_SH_h


#include "IODriverBase.h"

namespace stf {
namespace core {
namespace environment {

class SHSPI;
class SHUART;
class SHOstream;
class SHOfstream;
class SHIfstream;

//! Renesas SH7145プロセッサ用の環境クラス．
/*! */
struct SH7145 {
	//! Renesas SHプロセッサ用のGPIOクラス．未実装．
	/*! 
		@todo 実装を行う
	*/
	template<int i>class GPIO : public GPIOBase<i> {};
	typedef SHSPI SPI;
	typedef SHUART UART;
	typedef SHOstream OutputStream;
	typedef SHOfstream OutputFileStream;
	typedef SHIfstream InputFileStream;
};

//! Renesas SHプロセッサ用のSPIクラス．未実装．
/*! 
	@todo 実装を行う
 */
class SHSPI : public SPIBase {

};

//! Renesas SHプロセッサ用のUARTクラス．未実装．
/*! 
	@todo 実装を行う
 */
class SHUART : public UARTBase {


};

//! Renesas SHプロセッサ用の出力ストリームクラス．未実装．
/*! 
	@todo 実装を行う
 */
class SHOstream {

};

//! Renesas SHプロセッサ用の入力ストリームクラス．未実装．
/*! 
	@todo 実装を行う
 */
class SHIstream {

};


} /* End of namespace stf::core::environment */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_environment_Simulator_h
