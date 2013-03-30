/* Copyright (C) 2012-2013 Justin Berger 
   The full license is available in the LICENSE file at the root of this project and is also available at http://opensource.org/licenses/MIT. */

#include <stencet/stencet>

#include <cppunit/TestCase.h>
#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>


using namespace stencet;

struct StencetExprsTest : public CppUnit::TestCase {
  CPPUNIT_TEST_SUITE(StencetExprsTest);
  CPPUNIT_TEST(testAccess0);
  CPPUNIT_TEST(testInfixOp0);
  CPPUNIT_TEST(testInfixOp1);
  CPPUNIT_TEST(testInfixOp2);
  CPPUNIT_TEST(testInfixOp3);
  CPPUNIT_TEST_SUITE_END();
public:
  std::stringstream compare, ss;
  Variant v;

  void setUp() {
    Template::Templates().clear();
    CPPUNIT_ASSERT_EQUAL( ParseStatus::END, Template::Templates()["access0"].
			  Parse("{{str}} {{int}} {{float}} {{obj.bool}}"));

    CPPUNIT_ASSERT_EQUAL( ParseStatus::END, Template::Templates()["infix0"].
			  Parse("{{ num <= 10 }}"));

    CPPUNIT_ASSERT_EQUAL( ParseStatus::END, Template::Templates()["infix1"].
			  Parse("{{ str == 'test' }}"));

    compare.str(""); ss.str("");
    v = Variant();
  }

  void testInfixOp0(){
    v["num"] = 10;
    Template::ByName("infix0").render(ss, v);
    CPPUNIT_ASSERT_EQUAL( std::string("1"), ss.str());    
  }

  void testInfixOp1(){
    v["num"] = 8;
    Template::ByName("infix0").render(ss, v);
    CPPUNIT_ASSERT_EQUAL( std::string("1"), ss.str());    
  }

  void testInfixOp2(){
    v["num"] = 12.3;
    Template::ByName("infix0").render(ss, v);
    CPPUNIT_ASSERT_EQUAL( std::string("0"), ss.str());    
  }

  void testInfixOp3(){
    v["str"] = "test";
    Template::ByName("infix1").render(ss, v);
    CPPUNIT_ASSERT_EQUAL( std::string("1"), ss.str());    
  }

  void testAccess0(){
    v["str"] = "str";
    v["int"] = 42;
    v["float"] = 3.14;
    v["obj"]["bool"] = false;
    Template::ByName("access0").render(ss, v);
    CPPUNIT_ASSERT_EQUAL( std::string("str 42 3.14 0"), ss.str());    
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION(StencetExprsTest);
