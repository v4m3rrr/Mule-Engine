#include "MuleException.h"

#include <sstream>
#include <algorithm>

MuleException::MuleException(int line, std::wstring path) noexcept
	:line(line),path(path)
{
}

std::wstring MuleException::GetType() const
{
	return std::wstring(L"Mule Exception");
}

const wchar_t* MuleException::what() const noexcept
{
	std::wostringstream oss;
	oss << L"[EXCEPTION TYPE]\n" << GetType();
	oss << L"\n[ON LINE]\n" << line;
	oss << L"\n[IN FILE]\n" << path;
	whatbuffer = oss.str();
	return whatbuffer.c_str();
}

std::wstring MuleException::ToWide(const std::string& str)
{
	std::wstring wStr;
	std::transform(str.begin(), str.end(), std::back_inserter(wStr),
		[](char c) { return (wchar_t)c; }
	);

	return wStr;
}



