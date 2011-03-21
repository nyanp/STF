/**
 * @file   stfassert.h
 * @brief  assertラッパ．
 *
 * 可搬性を向上させるために，assertを直接読み込まずにこれを使う
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_util_stfassert_h
#define stf_util_stfassert_h

#if defined(_MSC_VER) || defined(__GNUC__)
#include<assert.h>
#else
#define assert(exp) \
	if( !(exp) ) {}

#endif

#endif