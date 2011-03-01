/**
 * @file   DCMTest.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef datatype_DCMTest_h
#define datatype_DCMTest_h

#include <cppunit/extensions/HelperMacros.h>
#include "../DCM.h"

namespace stf { 
namespace datatype {

class DCMTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE( DCMTest );

	CPPUNIT_TEST( test_init );
	CPPUNIT_TEST( test_operator_add );
	CPPUNIT_TEST( test_operator_sub );
	CPPUNIT_TEST( test_operator_mul );
	CPPUNIT_TEST( test_operator_div );
	CPPUNIT_TEST( test_operator_equal );
	CPPUNIT_TEST( test_operator_inequal );

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp(){ t_ = new DCM(); }      // 各テスト・ケースの実行直前に呼ばれる
	void tearDown(){ delete t_; }   // 各テスト・ケースの実行直後に呼ばれる

protected:
	void test_init();  // 
	void test_add();  // 
	void test_totalcount();
	void test_getjulian();
	void test_operator_add();
	void test_operator_sub();
	void test_operator_mul();
	void test_operator_div();
	void test_operator_equal();
	void test_operator_inequal();
	
	DCM* t_;
};

CPPUNIT_TEST_SUITE_REGISTRATION( DCMTest ); 

void DCMTest::test_init(){

}

void DCMTest::test_operator_add(){

}

void DCMTest::test_operator_sub(){

}

void DCMTest::test_operator_mul(){

}

void DCMTest::test_operator_div(){

}

void DCMTest::test_operator_equal(){

}

void DCMTest::test_operator_inequal(){

}

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // datatype_DCMTest_h
