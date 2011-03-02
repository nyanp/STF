/**
 * @file   MagneticTest.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_datatype_MagneticTest_h
#define stf_datatype_MagneticTest_h

#include <cppunit/extensions/HelperMacros.h>
#include "../Magnetic.h"

namespace stf { 
namespace datatype {


class MagneticTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE( MagneticTest );

	CPPUNIT_TEST( test_init );
	CPPUNIT_TEST( test_operator_add );
	CPPUNIT_TEST( test_operator_sub );
	CPPUNIT_TEST( test_operator_mul );
	CPPUNIT_TEST( test_operator_div );
	CPPUNIT_TEST( test_operator_equal );
	CPPUNIT_TEST( test_operator_inequal );

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp(){ t_ = new MagneticMoment(); }      // 各テスト・ケースの実行直前に呼ばれる
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
	
	MagneticMoment* t_;
};

CPPUNIT_TEST_SUITE_REGISTRATION( MagneticTest ); 

void MagneticTest::test_init(){

}

void MagneticTest::test_operator_add(){

}

void MagneticTest::test_operator_sub(){

}

void MagneticTest::test_operator_mul(){

}

void MagneticTest::test_operator_div(){

}

void MagneticTest::test_operator_equal(){

}

void MagneticTest::test_operator_inequal(){

}

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_MagneticTest_h
