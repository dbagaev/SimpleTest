#ifndef SIMPLETEST_EXECUTE_TEST_H
#define SIMPLETEST_EXECUTE_TEST_H

#include "TestDetails.h"
#include "MemoryOutStream.h"
#include "AssertException.h"
#include "CurrentTest.h"

#ifdef SIMPLETEST_POSIX
	#include "Posix/SignalTranslator.h"
#endif

namespace UnitTest {

template< typename T >
void ExecuteTest(T& testObject, TestDetails const& details)
{
	CurrentTest::Details() = &details;

	try
	{
#ifdef SIMPLETEST_POSIX
		SIMPLETEST_THROW_SIGNALS
#endif
		testObject.RunImpl();
	}
	catch (AssertException const& e)
	{
		CurrentTest::Results()->OnTestFailure(
			TestDetails(details.testName, details.suiteName, e.Filename(), e.LineNumber()), e.what());
	}
	catch (std::exception const& e)
	{
		MemoryOutStream stream;
		stream << "Unhandled exception: " << e.what();
		CurrentTest::Results()->OnTestFailure(details, stream.GetText());
	}
	catch (...)
	{
		CurrentTest::Results()->OnTestFailure(details, "Unhandled exception: Crash!");
	}
}

}

#endif
