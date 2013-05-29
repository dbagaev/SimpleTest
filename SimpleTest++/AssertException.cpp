#include "AssertException.h"
#include <cstring>

namespace UnitTest {

AssertException::AssertException(char const* description, char const* filename, int lineNumber)
    : m_description(description), m_filename(filename), m_lineNumber(lineNumber)
{
}

AssertException::~AssertException() throw()
{
}

char const* AssertException::what() const throw()
{
    return m_description.c_str();
}

char const* AssertException::Filename() const
{
    return m_filename.c_str();
}

int AssertException::LineNumber() const
{
    return m_lineNumber;
}

}
