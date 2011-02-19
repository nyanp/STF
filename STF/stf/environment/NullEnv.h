/**
 * @file   NullEnv.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef aocs_environment_NullEnv_h
#define aocs_environment_NullEnv_h

namespace stf {
namespace environment {

class NullEnv {
	typedef NullEnv OutputStream;
	typedef NullEnv InputStream;
private:
	NullEnv(){}
	~NullEnv(){}
public:
	static NullEnv& getInstance();
};

} /* End of namespace stf::environment */
} /* End of namespace stf */

#endif // aocs_environment_Simulator_h
