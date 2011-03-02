/**
 * @file   EnvironmentsTest.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_datatype_EnvironmentsTest_h
#define stf_datatype_EnvironmentsTest_h

#include <cppunit/extensions/HelperMacros.h>
#include "../Environments.h"

namespace stf { 
namespace datatype {


class EnvironmentTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE( EnvironmentTest );

	CPPUNIT_TEST( test_init );
	CPPUNIT_TEST( test_operator_add );
	CPPUNIT_TEST( test_operator_sub );
	CPPUNIT_TEST( test_operator_mul );
	CPPUNIT_TEST( test_operator_div );
	CPPUNIT_TEST( test_operator_equal );
	CPPUNIT_TEST( test_operator_inequal );

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp(){ 
		v_ = new datatype::Voltage(); 
		a_ = new datatype::Current();
		t_ = new datatype::Temperature();
	}      // 各テスト・ケースの実行直前に呼ばれる
	void tearDown(){
		delete v_;
		delete a_;
		delete t_;
	}   // 各テスト・ケースの実行直後に呼ばれる

protected:
	void test_init();
	void test_operator_add();
	void test_operator_sub();
	void test_operator_mul();
	void test_operator_div();
	void test_operator_equal();
	void test_operator_inequal();
	
	datatype::Voltage* v_;
	datatype::Current* a_;
	datatype::Temperature* t_;
};

CPPUNIT_TEST_SUITE_REGISTRATION( EnvironmentTest ); 

void EnvironmentTest::test_init(){

}

void EnvironmentTest::test_operator_add(){
	//組み込み型の加算
	*v_ += 1.0;
	*a_ += 1.0;
	*t_ += 1.0;


}

void EnvironmentTest::test_operator_sub(){

}

void EnvironmentTest::test_operator_mul(){

}

void EnvironmentTest::test_operator_div(){

}

void EnvironmentTest::test_operator_equal(){

}

void EnvironmentTest::test_operator_inequal(){

}

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_EnvironmentsTest_h
