#pragma once

//Specify the minimum operating system version the code supports
//In that case Windows 7 or later
#include <winsdkver.h>

#define WINVER 0x0601
#define _WIN32_WINNT 0x0601

#include <sdkddkver.h>

//Use Unicode strings
#define _UNICODE
#define UNICODE

//Disabling unused windows macro functions
#define NOMINMAX

//Lastly including windows
#include <Windows.h>