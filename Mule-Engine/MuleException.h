#pragma once
#include "MuleWin.h"

#include <exception>
#include <string>

class MuleException
{
public:
	MuleException(int line,std::wstring path) noexcept;
	virtual std::wstring GetType() const;
	virtual const wchar_t* what() const noexcept;
	virtual ~MuleException() = default;
public:
	static std::wstring ToWide(const std::string& str);
private:
	int line;
	std::wstring path;
protected:
	mutable std::wstring whatbuffer;
};
