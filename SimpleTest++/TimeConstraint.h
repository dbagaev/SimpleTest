#ifndef SIMPLETEST_TIMECONSTRAINT_H
#define SIMPLETEST_TIMECONSTRAINT_H

#include "TimeHelpers.h"

namespace UnitTest {

class TestResults;
class TestDetails;

class TimeConstraint
{
public:
    TimeConstraint(int ms, TestDetails const& details);
    ~TimeConstraint();

private:
    void operator=(TimeConstraint const&); 
	TimeConstraint(TimeConstraint const&);

	Timer m_timer;
    TestDetails const& m_details;
	int const m_maxMs;
};

#define SIMPLETEST_TIME_CONSTRAINT(ms) \
	UnitTest::TimeConstraint SIMPLETEST__timeConstraint__(ms, UnitTest::TestDetails(m_details, __LINE__))

#define SIMPLETEST_TIME_CONSTRAINT_EXEMPT() do { m_timeConstraintExempt = true; } while (0)

}

#endif
