#pragma once
#include "Utilities.h"


class BadAllocation : public std::bad_alloc
{
public:
	BadAllocation(const char* str) : m_str(str) {}
	const char* what() const noexcept { return m_str; }

private:
	const char* m_str;
};
//--------------------------------------------
class OutOfRange : public std::exception
{
public:
	OutOfRange(const char* str) : m_str(str) {}
	const char* what() const noexcept { return m_str; }

private:
	const char* m_str;
};
//----------------------------------
class Exception : public std::exception
{
public:
	Exception(const char* str)  : m_str(str) {}
    Exception(string str, int i) : m_string(str + to_string(i) + '\n') 
    {
        m_str = &m_string[0];
    }
	const char* what() const noexcept { return m_str; }

private:
	const char* m_str;
    string m_string;
};
//--------------------------------------------------------------------------