#ifndef SIMPLETEST_CURRENTTESTRESULTS_H
#define SIMPLETEST_CURRENTTESTRESULTS_H

namespace UnitTest {

class TestResults;
class TestDetails;

namespace CurrentTest
{
	TestResults*& Results();
	const TestDetails*& Details();
}

}

#endif
