#include<windows.h>

class button
{
public:
	RECT rect;
	HBRUSH Brush;
	button(int x1,int y1, int x2,int y2,HBRUSH Brush_new)
	{
		rect = { x1,y1,x2,y2 };
		Brush = Brush_new;
	}
	void draw(HDC Context)
	{
		FillRect(Context, &rect, Brush);
		DrawText(Context,L"LOCH PIDR", 10, &rect, DT_CENTER);
	}
	bool CheckClick(int x, int y)
	{
		if (x > rect.left && x<rect.right && y>rect.top && y < rect.bottom)
			return 1;
		return 0;
	}
}m[3]{ { 0,0,100,100,CreateSolidBrush(RGB(0,0,0)) },{ 0,110,100,210,CreateSolidBrush(RGB(0,0,0)) } ,{ 0,220,100,320,CreateSolidBrush(RGB(0,0,0)) } };
LRESULT CALLBACK Menu_Function(HWND Descriptor, UINT massage, WPARAM wparam, LPARAM lparam);
void draw(HWND Descriptor);
int WINAPI	WinMain(HINSTANCE Descriptor_program, HINSTANCE, LPSTR, int)
{
	WNDCLASS wnd_class = {  NULL , Menu_Function , NULL , NULL ,Descriptor_program,NULL,NULL,CreateSolidBrush(RGB(255, 255, 255)),NULL,L"Window_WNDCLASS"  };//create class
	RegisterClass(&wnd_class);//register window
	HWND Descriptor = CreateWindow(L"Window_WNDCLASS", L"Menu", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 100, 100, 500, 500, NULL, NULL, Descriptor_program, NULL);
	ShowWindow(Descriptor, SW_SHOW);
	UpdateWindow(Descriptor);


	MSG massage_code;
	while (GetMessage(&massage_code, NULL, 0, 0))
	{
		TranslateMessage(&massage_code);				//Преобразует сообщения клавиш в символы
		DispatchMessage(&massage_code);
	}
	return 0;
}
void ButtonFunction(int i)
{
	switch (i)
	{
	case 0: m[0].Brush = CreateSolidBrush(RGB(100, 100, 50));break ;
	case 2:PostQuitMessage(0); return;
	default: return;
	}
	InvalidateRect(NULL,NULL,TRUE);
}
LRESULT CALLBACK Menu_Function(HWND Descriptor, UINT massage, WPARAM wparam, LPARAM lparam)
{
	switch (massage)
	{
	case WM_PAINT:draw(Descriptor); return 0;
	case WM_LBUTTONUP:
		for (int i = 0; i < 3; i++)
			if (m[i].CheckClick(LOWORD(lparam), HIWORD(lparam)))
				ButtonFunction(i);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:break;
	}
	return DefWindowProc(Descriptor, massage, wparam, lparam);
}
void draw(HWND Descriptor)
{
	PAINTSTRUCT Paintstruct;
	HDC Context = BeginPaint(Descriptor, &Paintstruct);
	for (int i = 0; i < 3; i++)m[i].draw(Context);
	RECT rect = { 1,1,100,100 };
	EndPaint(Descriptor, &Paintstruct);
	ReleaseDC(Descriptor,Context);
}

