/**
 * @file   ScalarTest.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_datatype_ScalarTest_h
#define stf_datatype_ScalarTest_h

#include <cppunit/extensions/HelperMacros.h>
#include "../Scalar.h"

namespace stf { 
namespace datatype {

class ScalarTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE( ScalarTest );

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
		v_ = new datatype::Scalar;
	}      // 各テスト・ケースの実行直前に呼ばれる
	void tearDown(){
		delete v_;
	}   // 各テスト・ケースの実行直後に呼ばれる

protected:
	void test_init();
	void test_operator_add();
	void test_operator_sub();
	void test_operator_mul();
	void test_operator_div();
	void test_operator_equal();
	void test_operator_inequal();
	
	datatype::Scalar* v_;
};

CPPUNIT_TEST_SUITE_REGISTRATION( ScalarTest ); 

void ScalarTest::test_init(){
	CPPUNIT_ASSERT( v_->value() == 0.0 );

	v_->reset();

	CPPUNIT_ASSERT( v_->value() == 0.0 );
}

void ScalarTest::test_operator_add(){
	//組み込み型の加算
	*v_ += 1.0;
	CPPUNIT_ASSERT( v_->value() == 1.0 );

	*v_ += -1.0;
	CPPUNIT_ASSERT( v_->value() == 0.0 );

	datatype::Scalar s1(2);
	datatype::Scalar s2(3);
	datatype::Scalar s3 = s1 + s2;
	CPPUNIT_ASSERT( s3.value() == 5.0 );

	datatype::Scalar s4 = s1 + 3;
	CPPUNIT_ASSERT( s4.value() == 5.0 );

	datatype::Scalar s5 = 3 + s1;
	CPPUNIT_ASSERT( s5.value() == 5.0 );
}

void ScalarTest::test_operator_sub(){
	*v_ -= 1.0;
	CPPUNIT_ASSERT( v_->value() == -1.0 );

	*v_ -= -1.0;
	CPPUNIT_ASSERT( v_->value() == 0.0 );

	datatype::Scalar s1(2);
	datatype::Scalar s2(3);
	datatype::Scalar s3 = s1 - s2;
	CPPUNIT_ASSERT( s3.value() == -1.0 );

	datatype::Scalar s4 = s1 - 3;
	CPPUNIT_ASSERT( s4.value() == -1.0 );

	datatype::Scalar s5 = 3 - s1;
	CPPUNIT_ASSERT( s5.value() == 1.0 );
}

void ScalarTest::test_operator_mul(){
	*v_ *= 1.0;
	CPPUNIT_ASSERT( v_->value() == 0.0 );

	*v_ += 2.0;
	*v_ *= 5;
	CPPUNIT_ASSERT( v_->value() == 10.0 );

	datatype::Scalar s1(2);
	datatype::Scalar s2(3);
	datatype::Scalar s3 = s1 * s2;
	CPPUNIT_ASSERT( s3.value() == 6.0 );

	datatype::Scalar s4 = s2 * 3;
	CPPUNIT_ASSERT( s4.value() == 9.0 );

	datatype::Scalar s5 = 3 * s2;
	CPPUNIT_ASSERT( s5.value() == 9.0 );
}

void ScalarTest::test_operator_div(){
	*v_ /= 1.0;
	CPPUNIT_ASSERT( v_->value() == 0.0 );

	*v_ += 10.0;
	*v_ /= 5;
	CPPUNIT_ASSERT( v_->value() == 2.0 );

	datatype::Scalar s1(6);
	datatype::Scalar s2(3);
	datatype::Scalar s3 = s1 / s2;
	CPPUNIT_ASSERT( s3.value() == 2.0 );

	datatype::Scalar s4 = s2 / 3;
	CPPUNIT_ASSERT( s4.value() == 1.0 );

	datatype::Scalar s5 = 3 / s2;
	CPPUNIT_ASSERT( s5.value() == 1.0 );
}

void ScalarTest::test_operator_equal(){
	datatype::Scalar s1;
	CPPUNIT_ASSERT( *v_ == s1 );

	datatype::Scalar s2(3);
	*v_ += 3;
	CPPUNIT_ASSERT( *v_ == s2 );

	CPPUNIT_ASSERT( *v_ == 3 );

	CPPUNIT_ASSERT( 3 == *v_ );
}

void ScalarTest::test_operator_inequal(){
	datatype::Scalar s1(1);
	CPPUNIT_ASSERT( *v_ != s1 );

	datatype::Scalar s2(3);
	*v_ += 5;
	CPPUNIT_ASSERT( *v_ != s2 );

	CPPUNIT_ASSERT( *v_ != 3 );

	CPPUNIT_ASSERT( 3 != *v_ );
}

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_ScalarTest_h
