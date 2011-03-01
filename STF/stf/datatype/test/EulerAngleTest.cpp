/**
 * @file   EulerAngleTest.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_datatype_EulerAngleTest_h
#define stf_datatype_EulerAngleTest_h

#include <cppunit/extensions/HelperMacros.h>
#include "../EulerAngle.h"

namespace stf { 
namespace datatype {


class EulerAngleTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE( EulerAngleTest );

	CPPUNIT_TEST( test_init );
	CPPUNIT_TEST( test_operator_add );
	CPPUNIT_TEST( test_operator_sub );
	CPPUNIT_TEST( test_operator_mul );
	CPPUNIT_TEST( test_operator_div );
	CPPUNIT_TEST( test_operator_equal );
	CPPUNIT_TEST( test_operator_inequal );

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp(){ v_ = new datatype::EulerAngle(); }      // 各テスト・ケースの実行直前に呼ばれる
	void tearDown(){  }   // 各テスト・ケースの実行直後に呼ばれる

protected:
	void test_init();
	void test_operator_add();
	void test_operator_sub();
	void test_operator_mul();
	void test_operator_div();
	void test_operator_equal();
	void test_operator_inequal();
	
	datatype::EulerAngle* v_;
};

CPPUNIT_TEST_SUITE_REGISTRATION( EulerAngleTest ); 

void EulerAngleTest::test_init(){

}

void EulerAngleTest::test_operator_add(){

}

void EulerAngleTest::test_operator_sub(){

}

void EulerAngleTest::test_operator_mul(){

}

void EulerAngleTest::test_operator_div(){

}

void EulerAngleTest::test_operator_equal(){

}

void EulerAngleTest::test_operator_inequal(){

}
} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_EulerAngleTest_h
