#ifndef SIMPLETEST_TESTLIST_H
#define SIMPLETEST_TESTLIST_H


namespace UnitTest {

class Test;

class TestList
{
public:
    TestList();
    void Add (Test* test);

    Test* GetHead() const;

private:
    Test* m_head;
    Test* m_tail;
};


class ListAdder
{
public:
    ListAdder(TestList& list, Test* test);
};

}


#endif
