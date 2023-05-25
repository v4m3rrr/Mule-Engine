#pragma once
#include "MuleWin.h"

#include <unordered_map>
#include <string>
#include <sstream>
#include <iomanip>
#include <unordered_set>

#define RegisterMsg(msg) {msg,L#msg}

class WindowMessage 
{
public:
	WindowMessage() = default;
	WindowMessage(std::initializer_list<UINT>filters);

	std::wstring operator()(UINT msg, WPARAM wparam, LPARAM lparam) const;
private:
	std::wstring MakeMessage(const std::wstring& strMsg, WPARAM wparam, LPARAM lparam) const;
private:
	static const std::unordered_multimap<unsigned int, std::wstring> msgMap;
	
	std::unordered_set<UINT> filters;
public: //Helper function (only for debugging)
	std::wstring FindDuplicates() const;
};