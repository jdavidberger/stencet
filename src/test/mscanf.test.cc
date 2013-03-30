/* Copyright (C) 2012-2013 Justin Berger 
   The full license is available in the LICENSE file at the root of this project and is also available at http://opensource.org/licenses/MIT. */

#include <cppunit/TestCase.h>
#include <stencet/mscanf.h>
#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

struct MscanfTest : public CppUnit::TestCase {
  CPPUNIT_TEST_SUITE(MscanfTest);
  CPPUNIT_TEST(testMscanfNormal);
  CPPUNIT_TEST(testMscanfTrim);
  CPPUNIT_TEST(testMscanfWhitespace);
  CPPUNIT_TEST_SUITE_END();

  void testMscanfNormal() {
    std::string i, list;
    CPPUNIT_ASSERT_EQUAL( 3, msscanf("for idx in range", "for ${i} in ${list}", i, list));
    CPPUNIT_ASSERT_EQUAL( std::string("idx"), i);
    CPPUNIT_ASSERT_EQUAL( std::string("range"), list);
  }

  void testMscanfTrim() {
    std::string i, list;
    CPPUNIT_ASSERT_EQUAL( 3, msscanf("   for idx in range", "for ${i} in ${list}", i, list));
    CPPUNIT_ASSERT_EQUAL( std::string("idx"), i);
    CPPUNIT_ASSERT_EQUAL( std::string("range"), list);
    i.clear(); list.clear();
    CPPUNIT_ASSERT_EQUAL( 3, msscanf("for idx in range    ", "for ${i} in ${list}", i, list));
    CPPUNIT_ASSERT_EQUAL( std::string("idx"), i);
    CPPUNIT_ASSERT_EQUAL( std::string("range"), list);
  }

  void testMscanfWhitespace(){
    std::string i, list;
    CPPUNIT_ASSERT_EQUAL( 3, msscanf("for idx     in range", "for ${i} in ${list}", i, list));
    CPPUNIT_ASSERT_EQUAL( std::string("idx"), i);
    CPPUNIT_ASSERT_EQUAL( std::string("range"), list);
    i.clear();list.clear();
    CPPUNIT_ASSERT_EQUAL( 3, msscanf("    for     idx     in \n\n \trange", "for ${i} in ${list}", i, list));
    CPPUNIT_ASSERT_EQUAL( std::string("idx"), i);
    CPPUNIT_ASSERT_EQUAL( std::string("range"), list);
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION(MscanfTest);
