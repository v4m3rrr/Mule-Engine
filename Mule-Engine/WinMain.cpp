#include "MuleWin.h"

#include "Window.h"
#include "MuleException.h"
#include "WindowMessage.h"

#include <stdexcept>
#include <sstream>

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	try 
	{
		Window window(640, 480, L"Game Window");

		// Message pump
		MSG msg;
		BOOL gResult;
		while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
		{
			// Generates WM_CHAR message (propably not only)
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (window.kbd.IsKeyPressed(VK_ADD))
				MessageBox(nullptr, L"Message", L"Caption", MB_OK);
		}

		if (gResult == -1)
			return -1;
		else
			return msg.wParam;
	}
	catch (MuleException& e)
	{
		MessageBox(nullptr, e.what(), e.GetType().c_str(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (std::exception& e)
	{
		MessageBox(nullptr, MuleException::ToWide(e.what()).c_str(), L"StandardException", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, L"No additional information", L"Unidentified exception", MB_OK | MB_ICONEXCLAMATION);
	}
	
	return -1;
} 