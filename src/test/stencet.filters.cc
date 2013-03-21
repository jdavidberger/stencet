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

struct StencetFiltersTest : public CppUnit::TestCase {
  CPPUNIT_TEST_SUITE(StencetFiltersTest);
  CPPUNIT_TEST(capfirst0);
  CPPUNIT_TEST(capfirst1);
  CPPUNIT_TEST(default0);
  CPPUNIT_TEST(default1);
  CPPUNIT_TEST_SUITE_END();

public:
  std::stringstream compare, ss;
  Variant v;

  void setUp() {
    Template::Templates().clear();
    CPPUNIT_ASSERT_EQUAL( ParseStatus::END, Template::Templates()["capfirst0"].
			  Parse("{{ test | capfirst }}"));

    CPPUNIT_ASSERT_EQUAL( ParseStatus::END, Template::Templates()["default0"].
			  Parse("{{ test | default: 'def' }}"));

    CPPUNIT_ASSERT_EQUAL( ParseStatus::END, Template::Templates()["default1"].
			  Parse("{{ test | default: def }}"));

    compare.str(""); ss.str("");
    v = Variant();
  }
  void default0(){
    v["asdf"] = 1;
    Template::ByName("default0").render(ss, v);
    CPPUNIT_ASSERT_EQUAL( std::string("def"), ss.str());    
    ss.str("");
    v["test"] = "test";
    Template::ByName("default0").render(ss, v);
    CPPUNIT_ASSERT_EQUAL( std::string("test"), ss.str());    
  }
  void default1(){
    v["def"] = "test!";
    Template::ByName("default1").render(ss, v);
    CPPUNIT_ASSERT_EQUAL( std::string("test!"), ss.str());    
    ss.str("");
    v["test"] = "test?";
    Template::ByName("default1").render(ss, v);
    CPPUNIT_ASSERT_EQUAL( std::string("test?"), ss.str());    

  }
  void capfirst0(){
    v["test"] = "test";
    Template::ByName("capfirst0").render(ss, v);
    CPPUNIT_ASSERT_EQUAL( std::string("Test"), ss.str());    
  }

  void capfirst1(){
    v["test"] = "1test";
    Template::ByName("capfirst0").render(ss, v);
    CPPUNIT_ASSERT_EQUAL( std::string("1test"), ss.str());    
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION(StencetFiltersTest);
