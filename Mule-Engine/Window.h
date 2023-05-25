#pragma once
#include "MuleWin.h"

#include "MuleException.h"
#include "Keyboard.h"

#include <string>

class Window 
{
public:
	class Exception : public MuleException
	{
	public:
		Exception(int line, std::wstring path, DWORD errorCode) noexcept;
		virtual std::wstring GetType() const;
		virtual const wchar_t* what() const noexcept override;
		virtual ~Exception() = default;
	public:
		static std::wstring TranslateWindowsError(DWORD errorCode) noexcept;
	private:
		DWORD errorCode;
	};

	class WindowClass 
	{
	public:
		static const wchar_t* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowClass() noexcept;
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		~WindowClass();
	private:
		static WindowClass wndClass;
		HINSTANCE hInstance;
		static constexpr const wchar_t* wndClassName = L"Mule Game Engine Window";
	};
public:
	Window(int width, int height,std::wstring name);
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	~Window();
private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
public:
	Keyboard kbd;
private:
	int width;
	int height;
	std::wstring name = L"Game Window";

	HWND hWnd;
};

#define WIN_MULE_EXCEPTION_ERROR( hr ) {__LINE__,TEXT(__FILE__), hr }
#define WIN_MULE_EXCEPTION_LAST_WIN_ERROR() {__LINE__,TEXT(__FILE__),GetLastError()}