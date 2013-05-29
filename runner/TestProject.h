#pragma once

#include "TestNode.h"

class TestProject : public TestNode
  {

  public:
    TestProject();

    void LoadDll(QString dll_name);

  TestNode * getRoot() { return this; }

  };