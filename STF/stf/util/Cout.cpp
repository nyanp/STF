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

ENV::OutputStream cout;
ENV::OutputFileStream clog("log.csv");

ENV::OutputStream& endl(ENV::OutputStream& os){
	os << "\n";
	return os;
}

ENV::OutputFileStream& endl(ENV::OutputFileStream& os){
	os << "\n";
	return os;
}

} /* End of namespace stf::util */
} /* End of namespace stf */