#include "TestProject.h"
#include "UnitTestPPLibraryNode.h"

#include <iostream>

#include <SimpleTest++/Win32/UnitTestDll.h>
#include <SimpleTest++/TestReporterStdout.h>


TestProject::TestProject()
  {

  }

void TestProject::LoadDll(QString dll_name)
  {
  TestLibraryNode * node = new UnitTestPPLibraryNode(dll_name);
  node->Name = dll_name;
  node->Parent = getRoot();
  getRoot()->Children[dll_name] = node;
  }




