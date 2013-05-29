#include "UnitTestPPLibraryNode.h"

#include <SimpleTest++/Win32/UnitTestDll.h>
#include <SimpleTest++/TestReporterStdout.h>

#include <iostream>
#include <algorithm>
#include <windows.h>

class NodeTestReporter : public UnitTest::TestReporter
  {
  public:
    NodeTestReporter(UnitTestPPLibraryNode * ip_root) : mp_root(ip_root) {};
  private:
    virtual void ReportTestStart(UnitTest::TestDetails const& test);
    virtual void ReportFailure(UnitTest::TestDetails const& test, char const* failure);
    virtual void ReportTestFinish(UnitTest::TestDetails const& test, float secondsElapsed);
    virtual void ReportSummary(int totalTestCount, int failedTestCount, int failureCount, float secondsElapsed);

    UnitTestPPLibraryNode * mp_root;
  };

void NodeTestReporter::ReportTestStart(UnitTest::TestDetails const& test)
  {
  auto p_node = mp_root->findTest(test.suiteName, test.testName);
  if(p_node == nullptr)
    return;

  p_node->setStatus(TestNode::StatusUnknown);
  }

void NodeTestReporter::ReportFailure(UnitTest::TestDetails const& test, char const* failure)
  {
  auto p_node = mp_root->findTest(test.suiteName, test.testName);
  if(p_node == nullptr)
    return;

  p_node->setStatus(TestNode::StatusFail);
  }

void NodeTestReporter::ReportTestFinish(UnitTest::TestDetails const& test, float secondsElapsed)
  {
  auto p_node = mp_root->findTest(test.suiteName, test.testName);
  if(p_node == nullptr)
    return;

  if(p_node->getStatus() == TestNode::StatusUnknown)
    p_node->setStatus(TestNode::StatusOK);
  }

void NodeTestReporter::ReportSummary(int totalTestCount, int failedTestCount, int failureCount, float secondsElapsed)
  {
  }

//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

class CompositionReporter : public UnitTest::TestReporter
  {
  public:
    void AddReporter(UnitTest::TestReporter * ip_reporter)
      {
      m_reporters.push_back(ip_reporter);
      }

    ~CompositionReporter()
      {
      std::for_each(m_reporters.begin(), m_reporters.end(), [](UnitTest::TestReporter * ip_reporter) { delete ip_reporter; } );
      }

  private:
    virtual void ReportTestStart(UnitTest::TestDetails const& test)
      {
      std::for_each(m_reporters.begin(), m_reporters.end(), [&](UnitTest::TestReporter * ip_reporter) { ip_reporter->ReportTestStart(test); } );
      }

    virtual void ReportFailure(UnitTest::TestDetails const& test, char const* failure)
      {
      std::for_each(m_reporters.begin(), m_reporters.end(), [&](UnitTest::TestReporter * ip_reporter) { ip_reporter->ReportFailure(test, failure); } );
      }

    virtual void ReportTestFinish(UnitTest::TestDetails const& test, float secondsElapsed)
      {
      std::for_each(m_reporters.begin(), m_reporters.end(), [&](UnitTest::TestReporter * ip_reporter) { ip_reporter->ReportTestFinish(test, secondsElapsed); } );
      }

    virtual void ReportSummary(int totalTestCount, int failedTestCount, int failureCount, float secondsElapsed)
      {
      std::for_each(m_reporters.begin(), m_reporters.end(), [=](UnitTest::TestReporter * ip_reporter) { ip_reporter->ReportSummary(totalTestCount, failedTestCount, failureCount, secondsElapsed); } );
      }

    QList<UnitTest::TestReporter *> m_reporters;
  };

//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

UnitTestPPLibraryNode::UnitTestPPLibraryNode(QString dll_name)
  {
  wchar_t p_data[1024];
  std::fill_n(p_data, 1024, 0);
  dll_name.toWCharArray(p_data);
  HMODULE library_handle = LoadLibraryW(p_data);
  if (library_handle == NULL)
    {
    std::cout<<"Test library load FAILED"<<std::endl;
    return;
    }
  try
    {
    std::cout<<"Test library loaded"<<std::endl;
    //int test_result = TestLibrary(library_handle, ip_library_path);


    MAKE_FUNCTION_POINTER(GET_TEST_LIST_NAME)
      p_GetTestListName = (MAKE_FUNCTION_POINTER(GET_TEST_LIST_NAME))
      GetProcAddress(library_handle, EVALUATE(GET_TEST_LIST_NAME));
    if (p_GetTestListName == NULL)
      {
      //throw NoInterface(GetInterfaceMessage
      //  (library_name.c_str(), WEVALUATE(RUN_LIBRARY_TESTS_NAME)));
      std::cout<<"Error getting proc pointer."<<std::endl;
      return;
      }

    UnitTest::TestList * p_list = p_GetTestListName();

    for(UnitTest::Test * p_test = p_list->GetHead(); p_test != nullptr; p_test = p_test->next)
      {
      QString test_name(p_test->m_details.testName);
      QString suite_name(p_test->m_details.suiteName);

      // Find appropriate suite
      TestNode * p_suite = findChild(suite_name, true);
      //ASSERT(p_suite != nullptr);

      TestNode * p_new_test_node = p_suite->addChild(test_name);
      
      std::cout<<"Found test: "<<p_test->m_details.suiteName<<"::"<<p_test->m_details.testName<<std::endl;
      }

    FreeLibrary(library_handle);
    //return test_result;
    }
  catch (...)
    {
    FreeLibrary(library_handle);
    throw;
    }
  }

struct UnitTestPPLibraryNode::RunPredicate : public UnitTest::ITestPredicate
  {
  RunPredicate(UnitTestPPLibraryNode * library_node) : Library(library_node) {};

  virtual bool shouldRun(const UnitTest::Test* const test) const
    {
    TestNode * p_node = Library->findChild(test->m_details.suiteName);
    if(p_node == nullptr)
      return false;

    if(!p_node->Active)
      return false;

    p_node = p_node->findChild(test->m_details.testName);
    if(p_node == nullptr)
      return false;

    return p_node->Active;
    }

  private:
    UnitTestPPLibraryNode * Library;
  };


TestNode * UnitTestPPLibraryNode::findTest(QString i_suite_name, QString i_test_name)
  {
  TestNode * p_node = findChild(i_suite_name);
  if(p_node == nullptr)
    return nullptr;

  p_node = p_node->findChild(i_test_name);

  return p_node;
  }


void UnitTestPPLibraryNode::Run()
  {
  if(!Active)
    return;

  wchar_t p_data[1024];
  std::fill_n(p_data, 1024, 0);
  Name.toWCharArray(p_data);
  HMODULE library_handle = LoadLibraryW(p_data);
  if (library_handle == NULL)
    {
    std::cout<<"Test library load FAILED"<<std::endl;
    return;
    }
  try
    {
    //std::cout<<"Starting tests for <"<<Name.toAscii().data_ptr()<<">"<<std::endl;
    //int test_result = TestLibrary(library_handle, ip_library_path);


    MAKE_FUNCTION_POINTER(RUN_LIBRARY_TESTS_PREDICATE_NAME)
      p_RunLibraryTests = (MAKE_FUNCTION_POINTER(RUN_LIBRARY_TESTS_PREDICATE_NAME))
      GetProcAddress(library_handle, EVALUATE(RUN_LIBRARY_TESTS_PREDICATE_NAME));
    if (p_RunLibraryTests == NULL)
      {
      //throw NoInterface(GetInterfaceMessage
      //  (library_name.c_str(), WEVALUATE(RUN_LIBRARY_TESTS_NAME)));
      std::cout<<"Error getting proc pointer."<<std::endl;
      return;
      }

    CompositionReporter reporters;
    reporters.AddReporter(new UnitTest::TestReporterStdout);
    reporters.AddReporter(new NodeTestReporter(this));

    RunPredicate predicate(this);
    p_RunLibraryTests(reporters, &predicate);

    std::cout<<std::endl;

    FreeLibrary(library_handle);
    //return test_result;
    }
  catch (...)
    {
    FreeLibrary(library_handle);
    throw;
    }
  }
