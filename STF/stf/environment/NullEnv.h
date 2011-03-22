/**
 * @file   NullEnv.h
 * @brief  空の環境クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef aocs_environment_NullEnv_h
#define aocs_environment_NullEnv_h

namespace stf {
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

} /* End of namespace stf::environment */
} /* End of namespace stf */

#endif // aocs_environment_Simulator_h
