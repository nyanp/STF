/**
 * @file   Cout.cpp
 * @brief  標準出力のラッパ．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "Cout.h"


namespace stf { 
namespace util {

app::Default::ios_env::OutputStream cout;
app::Default::ios_env::OutputFileStream clog("log.csv");

app::Default::ios_env::OutputStream& endl(app::Default::ios_env::OutputStream& os){
	os << "\n";
	return os;
}

app::Default::ios_env::OutputFileStream& endl(app::Default::ios_env::OutputFileStream& os){
	os << "\n";
	return os;
}

} /* End of namespace stf::util */
} /* End of namespace stf */