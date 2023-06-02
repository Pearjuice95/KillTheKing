#include "Win32.h"

Win32::Win32()
{

}

Win32::~Win32()
{

}

void Win32::Initialize()
{
	WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = Win32::WndProc;		// 윈도 메시지를 받기 위한 콜백 함수
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = sizeof(LONG_PTR);
	wcex.hInstance = NULL;
	wcex.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.lpszClassName = "D2DDemoApp";

	RegisterClassEx(&wcex);

	// Create the application window.
	/// 응용 프로그램 창을 생성합니다.
	m_hWnd = CreateWindow(
		"D2DDemoApp",
		"Direct2D Demo Application",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1280,
		720,
		NULL,
		NULL,
		NULL,
		NULL
	);

	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	UpdateWindow(m_hWnd);
}

void Win32::LoopAll()
{
	MSG msg;

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}

			DispatchMessage(&msg);
		}
		else
		{

		}
	}
}

bool Win32::MessageLoop(bool& isQuitMessage)
{
	isQuitMessage = false;

	MSG msg;

	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			isQuitMessage = true;
		}

		DispatchMessage(&msg);

		return true;
	}
	else
	{
		return false;
	}
}

void Win32::Finalize()
{

}

LRESULT CALLBACK Win32::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT _result = 0;

	switch (message)
	{
		case WM_CREATE:
		{

		}
		break;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
		}
		break;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		break;

		default:
		{
			_result = DefWindowProc(hWnd, message, wParam, lParam);
		}
	}

	return _result;
}