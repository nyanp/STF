#ifndef AssertHelper_h
#define AssertHelper_h

#include <cppunit/extensions/HelperMacros.h>


#define STF_CPPUNIT_VECTOR_ASSERT_2( v, v0, v1 ) \
	CPPUNIT_ASSERT( v[0] == v0 ); CPPUNIT_ASSERT( v[1] == v1 );

#define STF_CPPUNIT_VECTOR_ASSERT_3( v, v0, v1, v2 ) \
	CPPUNIT_ASSERT( v[0] == v0 ); CPPUNIT_ASSERT( v[1] == v1 ); CPPUNIT_ASSERT( v[2] == v2 );

#define STF_CPPUNIT_VECTOR_ASSERT_4( v, v0, v1, v2, v3 ) \
	CPPUNIT_ASSERT( v[0] == v0 ); CPPUNIT_ASSERT( v[1] == v1 ); CPPUNIT_ASSERT( v[2] == v2 ); CPPUNIT_ASSERT( v[3] == v3 );

#define STF_CPPUNIT_VECTOR_ASSERT_5( v, v0, v1, v2, v3, v4 ) \
	CPPUNIT_ASSERT( v[0] == v0 ); CPPUNIT_ASSERT( v[1] == v1 ); CPPUNIT_ASSERT( v[2] == v2 ); CPPUNIT_ASSERT( v[3] == v3 ); \
	CPPUNIT_ASSERT( v[4] == v4 );

#define STF_CPPUNIT_VECTOR_ASSERT_6( v, v0, v1, v2, v3, v4, v5 ) \
	CPPUNIT_ASSERT( v[0] == v0 ); CPPUNIT_ASSERT( v[1] == v1 ); CPPUNIT_ASSERT( v[2] == v2 ); CPPUNIT_ASSERT( v[3] == v3 ); \
	CPPUNIT_ASSERT( v[4] == v4 ); CPPUNIT_ASSERT( v[5] == v5 );

#define STF_CPPUNIT_VECTOR_ASSERT_7( v, v0, v1, v2, v3, v4, v5, v6 ) \
	CPPUNIT_ASSERT( v[0] == v0 ); CPPUNIT_ASSERT( v[1] == v1 ); CPPUNIT_ASSERT( v[2] == v2 ); CPPUNIT_ASSERT( v[3] == v3 ); \
	CPPUNIT_ASSERT( v[4] == v4 ); CPPUNIT_ASSERT( v[5] == v5 ); CPPUNIT_ASSERT( v[6] == v6 );

#define STF_CPPUNIT_VECTOR_ASSERT_8( v, v0, v1, v2, v3, v4, v5, v6, v7 ) \
	CPPUNIT_ASSERT( v[0] == v0 ); CPPUNIT_ASSERT( v[1] == v1 ); CPPUNIT_ASSERT( v[2] == v2 ); CPPUNIT_ASSERT( v[3] == v3 ); \
	CPPUNIT_ASSERT( v[4] == v4 ); CPPUNIT_ASSERT( v[5] == v5 ); CPPUNIT_ASSERT( v[6] == v6 ); CPPUNIT_ASSERT( v[7] == v7 );


#define STF_CPPUNIT_VECTOR_ASSERT_DOUBLE_2( v, v0, v1, delta ) \
	CPPUNIT_ASSERT_DOUBLES_EQUAL( v[0], v0, delta ); CPPUNIT_ASSERT_DOUBLES_EQUAL( v[1], v1, delta );

#define STF_CPPUNIT_VECTOR_ASSERT_DOUBLE_3( v, v0, v1, v2, delta ) \
	CPPUNIT_ASSERT_DOUBLES_EQUAL( v[0], v0, delta ); CPPUNIT_ASSERT_DOUBLES_EQUAL( v[1], v1, delta ); CPPUNIT_ASSERT_DOUBLES_EQUAL( v[2], v2, delta );

#define STF_CPPUNIT_VECTOR_ASSERT_DOUBLE_4( v, v0, v1, v2, v3, delta ) \
	CPPUNIT_ASSERT_DOUBLES_EQUAL( v[0], v0, delta ); CPPUNIT_ASSERT_DOUBLES_EQUAL( v[1], v1, delta ); CPPUNIT_ASSERT_DOUBLES_EQUAL( v[2], v2, delta ); CPPUNIT_ASSERT_DOUBLES_EQUAL( v[3], v3, delta );

#define STF_CPPUNIT_VECTOR_ASSERT_DOUBLE_5( v, v0, v1, v2, v3, v4, delta ) \
	CPPUNIT_ASSERT_DOUBLES_EQUAL( v[0], v0, delta ); CPPUNIT_ASSERT_DOUBLES_EQUAL( v[1], v1, delta ); CPPUNIT_ASSERT_DOUBLES_EQUAL( v[2], v2, delta ); CPPUNIT_ASSERT_DOUBLES_EQUAL( v[3], v3, delta ); \
	CPPUNIT_ASSERT_DOUBLES_EQUAL( v[4], v4, delta );

#define STF_CPPUNIT_VECTOR_ASSERT_DOUBLE_6( v, v0, v1, v2, v3, v4, v5, delta ) \
	CPPUNIT_ASSERT_DOUBLES_EQUAL( v[0], v0, delta ); CPPUNIT_ASSERT_DOUBLES_EQUAL( v[1], v1, delta ); CPPUNIT_ASSERT_DOUBLES_EQUAL( v[2], v2, delta ); CPPUNIT_ASSERT_DOUBLES_EQUAL( v[3], v3, delta ); \
	CPPUNIT_ASSERT_DOUBLES_EQUAL( v[4], v4, delta ); CPPUNIT_ASSERT_DOUBLES_EQUAL( v[5], v5, delta );

#define STF_CPPUNIT_VECTOR_ASSERT_DOUBLE_7( v, v0, v1, v2, v3, v4, v5, v6, delta ) \
	CPPUNIT_ASSERT_DOUBLES_EQUAL( v[0], v0, delta ); CPPUNIT_ASSERT_DOUBLES_EQUAL( v[1], v1, delta ); CPPUNIT_ASSERT_DOUBLES_EQUAL( v[2], v2, delta ); CPPUNIT_ASSERT_DOUBLES_EQUAL( v[3], v3, delta ); \
	CPPUNIT_ASSERT_DOUBLES_EQUAL( v[4], v4, delta ); CPPUNIT_ASSERT_DOUBLES_EQUAL( v[5], v5, delta ); CPPUNIT_ASSERT_DOUBLES_EQUAL( v[6], v6, delta );

#define STF_CPPUNIT_VECTOR_ASSERT_DOUBLE_8( v, v0, v1, v2, v3, v4, v5, v6, v7, delta ) \
	CPPUNIT_ASSERT_DOUBLES_EQUAL( v[0], v0, delta ); CPPUNIT_ASSERT_DOUBLES_EQUAL( v[1], v1, delta ); CPPUNIT_ASSERT_DOUBLES_EQUAL( v[2], v2, delta ); CPPUNIT_ASSERT_DOUBLES_EQUAL( v[3], v3, delta ); \
	CPPUNIT_ASSERT_DOUBLES_EQUAL( v[4], v4, delta ); CPPUNIT_ASSERT_DOUBLES_EQUAL( v[5], v5, delta ); CPPUNIT_ASSERT_DOUBLES_EQUAL( v[6], v6, delta ); CPPUNIT_ASSERT_DOUBLES_EQUAL( v[7], v7, delta );
#endif