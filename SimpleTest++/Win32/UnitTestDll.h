#pragma once

#define EMBED_UNIT_TESTING
#ifdef EMBED_UNIT_TESTING

#include "../SimpleTest++.h"

#define SUBSTITUTE(x) x
#define MAKE_STRING(x) #x
#define EVALUATE(x) MAKE_STRING(x)

#define MAKE_FUNCTION_POINTER(x) SUBSTITUTE(x)##FunctionPointer

#define RUN_LIBRARY_TESTS_NAME RunLibraryTests
#define RUN_LIBRARY_TESTS_PREDICATE_NAME RunLibraryTestsWithPredicate
#define GET_TEST_LIST_NAME GetTestList

namespace UnitTest {

  struct ITestPredicate
    {
    virtual bool shouldRun(const Test* const) const = 0;

    bool operator()(const Test* const test) const { return shouldRun(test); };
    };

  };

typedef void (*MAKE_FUNCTION_POINTER(RUN_LIBRARY_TESTS_NAME))
  (UnitTest::TestReporter&, const wchar_t*);

typedef void (*MAKE_FUNCTION_POINTER(RUN_LIBRARY_TESTS_PREDICATE_NAME))
  (UnitTest::TestReporter&, UnitTest::ITestPredicate *);

typedef UnitTest::TestList * (*MAKE_FUNCTION_POINTER(GET_TEST_LIST_NAME))
  ();

/*! \def IMPLEMENT_LIBRARY_INTERFACE
 * The presence of this macro within the library is the only requirement
 * for providing library unit-test interface.
 * \n\n
 */
#define IMPLEMENT_TEST_LIBRARY_INTERFACE() \
  extern "C" __declspec(dllexport) void RUN_LIBRARY_TESTS_NAME(UnitTest::TestReporter& \
    i_test_reporter, const wchar_t* ip_test_name) \
    { \
      UnitTest::TestRunner test_runner(i_test_reporter); \
      UnitTest::TestList& test_list = UnitTest::Test::GetTestList(); \
      if (ip_test_name == 0) \
        test_runner.RunTestsIf(test_list, 0, UnitTest::True(), 0); \
      else \
        test_runner.RunTestsIf(test_list, 0, UnitTest::True()/*NameMatcher(ip_test_name)*/, 0); \
    } \
  extern "C" __declspec(dllexport) void RUN_LIBRARY_TESTS_PREDICATE_NAME(UnitTest::TestReporter& \
    i_test_reporter, UnitTest::ITestPredicate * ip_predicate) \
    { \
    UnitTest::TestRunner test_runner(i_test_reporter); \
    UnitTest::TestList& test_list = UnitTest::Test::GetTestList(); \
    if (ip_predicate == nullptr) \
      test_runner.RunTestsIf(test_list, 0, UnitTest::True(), 0); \
    else \
      test_runner.RunTestsIf(test_list, 0, *ip_predicate, 0); \
    }   \
  extern "C" __declspec(dllexport) UnitTest::TestList * GET_TEST_LIST_NAME()\
    {  \
    return &UnitTest::Test::GetTestList();  \
    }  \

#endif // EMBED_UNIT_TESTING
