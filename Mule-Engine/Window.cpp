#include "Window.h"

#include "resource.h"

#include "WindowMessage.h"
#include "MuleException.h"


// WINDOW CLASS


Window::WindowClass Window::WindowClass::wndClass;

const wchar_t* Window::WindowClass::GetName() noexcept
{
	return wndClassName;	
}

HINSTANCE Window::WindowClass::GetInstance() noexcept
{
	return wndClass.hInstance;
}

Window::WindowClass::WindowClass() noexcept
	:hInstance(GetModuleHandle(nullptr))
{
	WNDCLASSEX wc = { 0 }; //Good practise
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = static_cast<HICON>(
		LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, 0)
		);
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = wndClassName;
	wc.hIconSm = static_cast<HICON>(
		LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0)
		);
	
	RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass() noexcept
{
	UnregisterClass(wndClassName, hInstance);
}


// WINDOW


Window::Window(int width, int height, std::wstring name)
	:width(width), height(height), name(name)
{
	// Calculate windows size based on desired client size
	RECT wr;
	wr.left = 100;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;
	if (AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE) == 0)
		throw Exception(WIN_MULE_EXCEPTION_LAST_WIN_ERROR());

	hWnd = CreateWindowEx(
		0,
		WindowClass::GetName(),
		name.c_str(),
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		wr.right - wr.left, wr.bottom - wr.top,
		nullptr,
		nullptr,
		WindowClass::GetInstance(),
		this //We pass it to use this in HandleMsgSetup
	);

	if (hWnd == nullptr)
	{
		throw Exception(WIN_MULE_EXCEPTION_LAST_WIN_ERROR());
	}

	ShowWindow(hWnd, SW_SHOW);
}

Window::~Window()
{
	DestroyWindow(hWnd);
}

//If you want to know more about this function go to: https://youtu.be/D-PC-huX-l8
LRESULT CALLBACK Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	// use create parameter passed in from CreateWindow() to store window class pointer at WinAPI side
	if (msg == WM_NCCREATE)
	{
		// extract ptr to window class from creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		// set WinAPI-managed user data to store ptr to window instance
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		// set message proc to normal (non-setup) handler now that setup is finished
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
		// forward message to window instance handler
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}
	// if we get a message before the WM_NCCREATE message, handle with default handler
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


LRESULT CALLBACK Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	//Retrive WinAPI-managed user data for window instance
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	//Forward message to window class handler
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	static WindowMessage wm;
	OutputDebugString(wm(msg, wParam, lParam).c_str());

	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(69);
		return 0; //We want call DestroyWindow through our destrctor
				 //So we skip DefWindowProc
	//KEYBOARD EVENTS
	case WM_SYSKEYDOWN: case WM_KEYDOWN:
		if (kbd.IsAutoRepeatEnabled() || !(lParam & 0x40000000))
			kbd.OnKeyPressed(wParam);
		break;
	case WM_SYSKEYUP: case WM_KEYUP:
		kbd.OnKeyReleased(wParam);
		break;
	case WM_CHAR:
		kbd.OnChar(wParam);
		break;
	// MOUSE EVENTS
	case WM_MOUSEMOVE:
	{
		POINTS points = MAKEPOINTS(lParam);
		mouse.OnMoved(points.x, points.y);
		/*static std::wstringstream ss;
		ss.str(std::wstring());
		ss << "(" << points.x << ", " << points.y << ")";
		SetWindowText(hWnd, ss.str().c_str());*/
		break;
	}
	case WM_LBUTTONDOWN:
	{
		//We want track mouse movement outside
		// of the window when LB is pressed
		SetCapture(hWnd);
		POINTS points = MAKEPOINTS(lParam);
		mouse.OnPressed(points.x, points.y, Mouse::Button::Left);
		break;
	}
	case WM_LBUTTONUP:
	{
		// Then we need to 'untrack'
		ReleaseCapture();
		POINTS points = MAKEPOINTS(lParam);
		mouse.OnReleased(points.x, points.y, Mouse::Button::Left);
		break;
	}
	case WM_MBUTTONDOWN:
	{
		POINTS points = MAKEPOINTS(lParam);
		mouse.OnPressed(points.x, points.y, Mouse::Button::Middle);
		break;
	}
	case WM_MBUTTONUP:
	{
		POINTS points = MAKEPOINTS(lParam);
		mouse.OnReleased(points.x, points.y, Mouse::Button::Middle);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		POINTS points = MAKEPOINTS(lParam);
		mouse.OnPressed(points.x, points.y, Mouse::Button::Right);
		break;
	}
	case WM_RBUTTONUP:
	{
		POINTS points = MAKEPOINTS(lParam);
		mouse.OnReleased(points.x, points.y, Mouse::Button::Right);
		break;
	}
	case WM_MOUSEWHEEL:
	{
		POINTS points = MAKEPOINTS(lParam);
		mouse.OnWheelMoved(points.x, points.y, true);
		/*static short scrolls;
		scrolls += GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
		SetWindowText(hWnd, std::to_wstring(scrolls).c_str());*/
		break;
	}
	case WM_KILLFOCUS:
		kbd.ClearKeyStates();
		mouse.ClearButtonsStates();
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


// EXCEPTIONS


Window::Exception::Exception(int line, std::wstring path, DWORD errorCode) noexcept
	:errorCode(errorCode),MuleException(line,path)
{}

std::wstring Window::Exception::GetType() const
{
	return L"Window Mule Exception";
}

const wchar_t* Window::Exception::what() const noexcept
{
	//It inserts into whatbuffer
	MuleException::what();

	std::wostringstream oss;
	oss << L"\n[Description] " << TranslateWindowsError(errorCode);
	whatbuffer += oss.str();

	return whatbuffer.c_str();
}

std::wstring Window::Exception::TranslateWindowsError(DWORD errorCode) noexcept
{
	wchar_t* lpMsgBuf = nullptr;
	DWORD bufSize = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr,
		errorCode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPTSTR>(&lpMsgBuf),
		0, nullptr
	);

	if (bufSize == 0)
		return L"Unidentified message";

	std::wstring msg = lpMsgBuf;
	LocalFree(lpMsgBuf);
	return msg;
}
