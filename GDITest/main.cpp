#include <Windows.h> 
#include <Windowsx.h> 
#include <time.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	WNDCLASS wc;
	wc.style = 0;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(6);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "GameFrame";
	RegisterClassA(&wc);

	HWND hWnd = CreateWindow("GameFrame", "Paint", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, hInst, NULL);

	if (!hWnd) return FALSE;
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps; static HDC hDC; POINT cp; static bool mouse_hold; static HPEN hPen;

	switch (msg)
	{	
	case WM_CREATE:
		hPen = CreatePen(PS_SOLID, 2,RGB(0,255,0));
		break;
	case WM_PAINT:
		// hDC = BeginPaint(hWnd, &ps);
		// EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		hDC = GetDC(hWnd);
		SelectObject(hDC, hPen);
		MoveToEx(hDC, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), 0);
		mouse_hold = true;
		break;
	case WM_LBUTTONUP:
		DeleteDC(hDC);
		mouse_hold = false;
		break;
	case WM_MOUSEMOVE:
		if (mouse_hold)
		{
			LineTo(hDC, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		}
		break;
	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;
	};
	return DefWindowProc(hWnd, msg, wParam, lParam);
}