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

struct StencetTagsTest : public CppUnit::TestCase {
  CPPUNIT_TEST_SUITE(StencetTagsTest);
  CPPUNIT_TEST(testFor0);
  CPPUNIT_TEST(testFor1);
  CPPUNIT_TEST(testIf0);
  CPPUNIT_TEST(testIf1);
  CPPUNIT_TEST(testIf2);
  CPPUNIT_TEST(testInclude0);
  CPPUNIT_TEST(testExtends0);
  CPPUNIT_TEST(testExtends0);
  CPPUNIT_TEST(testCycle0);
  CPPUNIT_TEST(testNow0);
  CPPUNIT_TEST(testSpaceless0);
  CPPUNIT_TEST(testComment0);
  CPPUNIT_TEST(testVerbatim0);
  CPPUNIT_TEST(testVerbatim1);
  CPPUNIT_TEST_SUITE_END();
public:
  std::stringstream compare, ss;
  Variant v;

  void setUp() {
    Template::Templates().clear();
    CPPUNIT_ASSERT_EQUAL( ParseStatus::END, Template::Templates()["forTest.0"].
			  Parse("{% for i in range %}{{i}}{%empty%}empty{%endfor%}"));
    CPPUNIT_ASSERT_EQUAL( ParseStatus::END, Template::Templates()["ifTest.0"].
			  Parse("{% if testIf %}if{%elseif testElseIf %}elseif{%else%}else{%endif%}"));
    CPPUNIT_ASSERT_EQUAL( ParseStatus::END, Template::Templates()["includeTest.0"].
			  Parse("in{% include \"includeTest\" %}"));
    CPPUNIT_ASSERT_EQUAL( ParseStatus::END, Template::Templates()["includeTest"].
			  Parse("cluded"));
    CPPUNIT_ASSERT_EQUAL( ParseStatus::END, Template::Templates()["super"].
			  Parse("super {% block inherit %}noinherit{%endblock%} done"));
    CPPUNIT_ASSERT_EQUAL( ParseStatus::END, Template::Templates()["extendsTest.0"].
			  Parse("{%extends \"super\"%}"));
    CPPUNIT_ASSERT_EQUAL( ParseStatus::END, Template::Templates()["extendsTest.1"].
			  Parse("{%extends \"super\"%}{% block inherit %}inherit{%endblock%}"));
    CPPUNIT_ASSERT_EQUAL( ParseStatus::END, Template::Templates()["cycleTest.0"].
			  Parse("{% for j in range %}{% for i in range %}{% cycle j i 'literal' %} {%endfor%}{%endfor%}"));
    CPPUNIT_ASSERT_EQUAL( ParseStatus::END, Template::Templates()["nowTest.0"].
			  Parse("{% now '%a %b %d %H:%M:%S %Y' %}"));
    CPPUNIT_ASSERT_EQUAL( ParseStatus::END, Template::Templates()["spacelessTest.0"].
			  Parse("{% spaceless %}     <p>     <p>   test    this </p> </p>{% endspaceless %}"));
    CPPUNIT_ASSERT_EQUAL( ParseStatus::END, Template::Templates()["commentTest.0"].
			  Parse("te{% comment %}this shouldnt appear {%endcomment% neither should this. {% endcomment %}st"));
    CPPUNIT_ASSERT_EQUAL( ParseStatus::END, Template::Templates()["verbatimTest.0"].
			  Parse("{%verbatim a %}' {{ test }} {%endverbatim b%} ' {%endverbatim{%endverbatim a    %}"));
    CPPUNIT_ASSERT_EQUAL( ParseStatus::END, Template::Templates()["verbatimTest.1"].
			  Parse("{%verbatim a %}' {{ test }} {%endverbatim b%} ' {%endverbatim   {%endverbatim a    %}"));

    compare.str(""); ss.str("");
    v = Variant();
  }
  void testVerbatim0(){
    Template::ByName("verbatimTest.0").render(ss, v);
    CPPUNIT_ASSERT_EQUAL( std::string("' {{ test }} {%endverbatim b%} ' {%endverbatim"), ss.str());            
  }

  void testVerbatim1(){
    Template::ByName("verbatimTest.1").render(ss, v);
    CPPUNIT_ASSERT_EQUAL( std::string("' {{ test }} {%endverbatim b%} ' {%endverbatim   "), ss.str());            
  }


  void testComment0(){
    Template::ByName("commentTest.0").render(ss, v);
    CPPUNIT_ASSERT_EQUAL( std::string("test"), ss.str());            
  }
  void testSpaceless0() {
    Template::ByName("spacelessTest.0").render(ss, v);
    CPPUNIT_ASSERT_EQUAL( std::string("<p><p>   test    this </p></p>"), ss.str());            
  }
  void testNow0() {
    Template::ByName("nowTest.0").render(ss, v);
    CPPUNIT_ASSERT("" != ss.str()); // Not sure the proper test case here...
  }
  
  void testCycle0() {
    v["range"].append("value1");
    v["range"].append("value2");
    v["range"].append("value3");
    Template::ByName("cycleTest.0").render(ss, v);
    CPPUNIT_ASSERT_EQUAL( std::string("value1 value2 literal value2 value2 literal value3 value2 literal "), ss.str());        
  }

  void testExtends0(){
    Template::ByName("extendsTest.0").render(ss, v);
    CPPUNIT_ASSERT_EQUAL( std::string("super noinherit done"), ss.str());    
  }

  void testExtends1(){
    Template::ByName("extendsTest.1").render(ss, v);
    CPPUNIT_ASSERT_EQUAL( std::string("super inherit done"), ss.str());    
  }

  void testInclude0(){
    Template::ByName("includeTest.0").render(ss, v);
    CPPUNIT_ASSERT_EQUAL( std::string("included"), ss.str());    
  }
  void testIf0(){
    Template::ByName("ifTest.0").render(ss, v);
    CPPUNIT_ASSERT_EQUAL( std::string("else"), ss.str());    
  }
  void testIf1(){
    v["testIf"] = 1;
    Template::ByName("ifTest.0").render(ss, v);
    CPPUNIT_ASSERT_EQUAL( std::string("if"), ss.str());    
  }
  void testIf2() {
    v["testIf"] = 0; v["testElseIf"] = true;
    Template::ByName("ifTest.0").render(ss, v);
    CPPUNIT_ASSERT_EQUAL( std::string("elseif"), ss.str());    
  }

  void testFor0() {
    for(int i = 0;i < 1000;i++){
      v["range"].append(i);
      compare << i;
    }
    Template::ByName("forTest.0").render(ss, v);
    CPPUNIT_ASSERT_EQUAL( compare.str(), ss.str());
  }

  void testFor1(){
    v["range"] = {};
    Template::ByName("forTest.0").render(ss, v);
    CPPUNIT_ASSERT_EQUAL( std::string("empty"), ss.str());
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION(StencetTagsTest);
