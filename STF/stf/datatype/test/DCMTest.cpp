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
#include "AssertHelper.h"

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
	CPPUNIT_TEST( test_inverse );

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
	void test_inverse();
	
	DCM* t_;
};

CPPUNIT_TEST_SUITE_REGISTRATION( DCMTest ); 

void DCMTest::test_init(){
	CPPUNIT_ASSERT( t_->is_unit() );
	t_->reset();
	CPPUNIT_ASSERT( t_->is_unit() );
}

void DCMTest::test_operator_add(){
	datatype::DCM dcm;
	
	*t_ += dcm;

	STF_CPPUNIT_VECTOR_ASSERT_3( (*t_)[0], 2.0, 0.0, 0.0 );
	STF_CPPUNIT_VECTOR_ASSERT_3( (*t_)[1], 0.0, 2.0, 0.0 );
	STF_CPPUNIT_VECTOR_ASSERT_3( (*t_)[2], 0.0, 0.0, 2.0 );

	(*t_)[0][0] = (*t_)[1][1] = (*t_)[2][2] = 0.0;

	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			(*t_)[i][j] += i + j;

	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			CPPUNIT_ASSERT( (*t_)[i][j] == i + j );

	t_->reset();

	datatype::DCM dcm_a, dcm_b;

	dcm_a[0][0] =  1.0; dcm_a[0][1] =  1.0; dcm_a[0][2] =  1.0;
	dcm_a[1][0] = -1.0; dcm_a[1][1] = -1.0; dcm_a[1][2] = -1.0;
	dcm_a[2][0] =  0.0; dcm_a[2][1] =  0.0; dcm_a[2][2] =  0.0;	

	dcm_b[0][0] = 1.0; dcm_b[0][1] = 0.5; dcm_b[0][2] = 2.0;
	dcm_b[1][0] = 1.0; dcm_b[1][1] = 0.5; dcm_b[1][2] = 2.0;
	dcm_b[2][0] = 1.0; dcm_b[2][1] = 0.5; dcm_b[2][2] = 2.0;

	*t_ = dcm_a + dcm_b;

	STF_CPPUNIT_VECTOR_ASSERT_3( (*t_)[0], 2.0,  1.5, 3.0 );
	STF_CPPUNIT_VECTOR_ASSERT_3( (*t_)[1], 0.0, -0.5, 1.0 );
	STF_CPPUNIT_VECTOR_ASSERT_3( (*t_)[2], 1.0,  0.5, 2.0 );
}

void DCMTest::test_operator_sub(){
	datatype::DCM dcm;
	
	*t_ -= dcm;

	STF_CPPUNIT_VECTOR_ASSERT_3( (*t_)[0], 0.0, 0.0, 0.0 );
	STF_CPPUNIT_VECTOR_ASSERT_3( (*t_)[1], 0.0, 0.0, 0.0 );
	STF_CPPUNIT_VECTOR_ASSERT_3( (*t_)[2], 0.0, 0.0, 0.0 );

	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			(*t_)[i][j] -= i + j;

	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			CPPUNIT_ASSERT( (*t_)[i][j] == - i - j );

	t_->reset();

	datatype::DCM dcm_a, dcm_b;

	dcm_a[0][0] =  1.0; dcm_a[0][1] =  1.0; dcm_a[0][2] =  1.0;
	dcm_a[1][0] = -1.0; dcm_a[1][1] = -1.0; dcm_a[1][2] = -1.0;
	dcm_a[2][0] =  0.0; dcm_a[2][1] =  0.0; dcm_a[2][2] =  0.0;	

	dcm_b[0][0] = 1.0; dcm_b[0][1] = 0.5; dcm_b[0][2] = 2.0;
	dcm_b[1][0] = 1.0; dcm_b[1][1] = 0.5; dcm_b[1][2] = 2.0;
	dcm_b[2][0] = 1.0; dcm_b[2][1] = 0.5; dcm_b[2][2] = 2.0;

	*t_ = dcm_a - dcm_b;

	STF_CPPUNIT_VECTOR_ASSERT_3( (*t_)[0],  0.0,  0.5, -1.0 );
	STF_CPPUNIT_VECTOR_ASSERT_3( (*t_)[1], -2.0, -1.5, -3.0 );
	STF_CPPUNIT_VECTOR_ASSERT_3( (*t_)[2], -1.0, -0.5, -2.0 );
}

void DCMTest::test_operator_mul(){
	datatype::DCM dcm;
	*t_ *= dcm;
	CPPUNIT_ASSERT( t_->is_unit() );

	datatype::DCM dcm_a;
	datatype::DCM dcm_b;

	dcm_a[0][0] =  1; dcm_a[0][1] = 4; dcm_a[0][2] =  3;
	dcm_a[1][0] =  0; dcm_a[1][1] = 3; dcm_a[1][2] = -1;
	dcm_a[2][0] =  2; dcm_a[2][1] = 2; dcm_a[2][2] =  2;	

	dcm_b[0][0] =  1; dcm_b[0][1] = -5; dcm_b[0][2] = 2;
	dcm_b[1][0] =  1; dcm_b[1][1] = 2;  dcm_b[1][2] = 2;
	dcm_b[2][0] =  0; dcm_b[2][1] = 3;  dcm_b[2][2] = 2;

	*t_ = dcm_a * dcm_b;

	STF_CPPUNIT_VECTOR_ASSERT_3( (*t_)[0],  5.0, 12.0, 16.0 );
	STF_CPPUNIT_VECTOR_ASSERT_3( (*t_)[1],  3.0,  3.0,  4.0 );
	STF_CPPUNIT_VECTOR_ASSERT_3( (*t_)[2],  4.0,  0.0, 12.0 );
}

void DCMTest::test_operator_div(){
	*t_ /= 2;
	*t_ *= 2;

	CPPUNIT_ASSERT( t_->is_unit() );

	*t_ /= 2;

	STF_CPPUNIT_VECTOR_ASSERT_3( (*t_)[0], 0.5, 0.0, 0.0 );
	STF_CPPUNIT_VECTOR_ASSERT_3( (*t_)[1], 0.0, 0.5, 0.0 );
	STF_CPPUNIT_VECTOR_ASSERT_3( (*t_)[2], 0.0, 0.0, 0.5 );
}

void DCMTest::test_operator_equal(){
	datatype::DCM dcm;

	CPPUNIT_ASSERT( dcm == *t_ );
	CPPUNIT_ASSERT( *t_ == dcm );
}

void DCMTest::test_operator_inequal(){
	datatype::DCM dcm;
	dcm[2][2] += 0.1;

	CPPUNIT_ASSERT( dcm != *t_ );
	CPPUNIT_ASSERT( *t_ != dcm );
}

void DCMTest::test_inverse(){
	CPPUNIT_ASSERT( *t_ == t_->inverse() );//単位行列の逆行列
}

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // datatype_DCMTest_h
