/**
 * @file   Cout.h
 * @brief  標準出力のラッパ．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef util_Cout_h
#define util_Cout_h

#include"../Config.h"

namespace stf { 
namespace util {

extern ENV::OutputStream cout;
extern ENV::OutputFileStream clog;

ENV::OutputStream& endl(ENV::OutputStream& os);
ENV::OutputFileStream& endl(ENV::OutputFileStream& os);

} /* End of namespace stf::util */
} /* End of namespace stf */

#endif // util_Cout_h
