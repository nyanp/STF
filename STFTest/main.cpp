//--- Hello, World! for CppUnit

#include <iostream>

#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>

/*
#include "datatype/test/DateTimeTest.h"
#include "datatype/test/DCMTest.h"
#include "datatype/test/EnvironmentsTest.h"
#include "datatype/test/EulerAngleTest.h"
#include "datatype/test/ListTest.h"
#include "datatype/test/MagneticTest.h"
#include "datatype/test/MatrixTest.h"
#include "datatype/test/OrbitCalcTest.h"
#include "datatype/test/OrbitInfoTest.h"
#include "datatype/test/QuaternionTest.h"
#include "datatype/test/ScalarTest.h"
#include "datatype/test/StaticVectorTest.h"
#include "datatype/test/StringTest.h"
#include "datatype/test/TimeTest.h"
#include "datatype/test/TypeConverterTest.h"
#include "datatype/test/VectorTest.h"*/

int main( int ac, char **av )
{

  // イベント・マネージャとテスト・コントローラを生成する
  CPPUNIT_NS::TestResult controller;

  // テスト結果収集リスナをコントローラにアタッチする
  CPPUNIT_NS::TestResultCollector result;
  controller.addListener( &result );

  // 「.」で進行状況を出力するリスナをアタッチする
  CPPUNIT_NS::BriefTestProgressListener progress;
  controller.addListener( &progress );

  // テスト・ランナーにテスト群を与え、テストする
  CPPUNIT_NS::TestRunner runner;
  runner.addTest( CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest() );
  runner.run( controller );

   // テスト結果を標準出力に吐き出す
  CPPUNIT_NS::CompilerOutputter outputter( &result, CPPUNIT_NS::stdCOut() );
  outputter.write();

  return result.wasSuccessful() ? 0 : 1;
}
