#pragma once
#include <windows.h>

class Win32
{
public:
	Win32();
	~Win32();

private:
	HWND m_hWnd;

public:
	void Initialize();
	void LoopAll();
	bool MessageLoop(bool& isQuitMessage);
	void Finalize();

	static LRESULT CALLBACK WndProc(HWND hWnd,
		UINT message,
		WPARAM wParam,
		LPARAM lParam);

public:
	HWND ReturnWindowHandle() const { return m_hWnd; }
};