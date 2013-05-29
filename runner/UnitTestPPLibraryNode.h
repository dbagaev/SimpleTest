#pragma once

#include "TestLibraryNode.h"

#include <QString>

struct UnitTestPPLibraryNode : public TestLibraryNode
  {
  public:
    UnitTestPPLibraryNode(QString dll_name);

    virtual void Run();

    TestNode * findTest(QString i_suite_name, QString i_test_name);

  private:
    struct RunPredicate;
  };
