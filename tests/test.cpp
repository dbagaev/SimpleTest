#include <SimpleTest++/Win32/UnitTestDll.h>

#include <iostream>

IMPLEMENT_TEST_LIBRARY_INTERFACE()

TEST(SimpleTest1)
  {
  std::cout<<"Test 1..."<<std::endl;
  }

SUITE(Suite1)
  {

  TEST(SuiteTest1)
    {
    std::cout<<"SuiteTest 1..."<<std::endl;
    }

  TEST(SuiteTest2)
    {
    std::cout<<"SuiteTest 2..."<<std::endl;
    }

  }

SUITE(RealSuite)
  {

  TEST(RealTest1)
    {
    std::cout<<"Real 1..."<<std::endl;
    CHECK(true);
    CHECK(false);
    }

  TEST(RealTest2)
    {
    std::cout<<"Real 2..."<<std::endl;
    CHECK_EQUAL(1, 1);
    CHECK(1, 2);
    }

  }


