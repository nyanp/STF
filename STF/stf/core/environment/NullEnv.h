/**
 * @file   NullEnv.h
 * @brief  空の環境クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_environment_NullEnv_h
#define stf_core_environment_NullEnv_h

namespace stf {
namespace core {
namespace environment {

//! 空の環境クラス．
/*! */
class NullEnv {
	typedef NullEnv OutputStream;
	typedef NullEnv OutputFileStream;
	typedef NullEnv InputFileStream;
private:
	NullEnv(){}
	~NullEnv(){}
public:
	static NullEnv& get_instance();
};

} /* End of namespace stf::core::environment */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_environment_Simulator_h
