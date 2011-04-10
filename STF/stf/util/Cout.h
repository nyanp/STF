/**
 * @file   Cout.h
 * @brief  標準出力のラッパ．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef util_Cout_h
#define util_Cout_h

#include "../app/Default.h"

namespace stf { 
namespace util {

extern app::Default::ios_env::OutputStream cout;
extern app::Default::ios_env::OutputFileStream clog;

app::Default::ios_env::OutputStream& endl(app::Default::ios_env::OutputStream& os);
app::Default::ios_env::OutputFileStream& endl(app::Default::ios_env::OutputFileStream& os);

} /* End of namespace stf::util */
} /* End of namespace stf */

#endif // util_Cout_h
