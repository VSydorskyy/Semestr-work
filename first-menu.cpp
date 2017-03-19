#include<windows.h>
class button
{
public:
	RECT rect;
	HBRUSH Brush;
	char inf[10];
	button(int x1, int y1, int x2, int y2, HBRUSH Brush_new,char*inf_new)
	{
		rect = { x1,y1,x2,y2 };
		Brush = Brush_new;
		strcpy_s(inf, strlen(inf_new)+1, inf_new);
	}
	void draw(HDC Context)
	{
		FillRect(Context, &rect, Brush);
		SetBkMode(Context, TRANSPARENT);
		DrawText(Context, inf, 10, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
	bool CheckClick(int x, int y)
	{
		if (x > rect.left && x<rect.right && y>rect.top && y < rect.bottom)
			return 1;
		return 0;
	}
}m[10]{
{ 195,80,305,190,CreateSolidBrush(RGB(187,96,25)),"Play" },
{ 195,200,305,310,CreateSolidBrush(RGB(187,96,25)),"Settings" },
{ 195,320,305,430,CreateSolidBrush(RGB(187,96,25)),"Help" },
{ 195,440,305,550,CreateSolidBrush(RGB(187,96,25)),"About"},
{ 195,560,305,670,CreateSolidBrush(RGB(187,96,25)),"Exit"},
{ 200,85,300,185,CreateSolidBrush(RGB(255,252,211)),"Play" },
{ 200,205,300,305,CreateSolidBrush(RGB(255,252,211)),"Settings" },
{ 200,325,300,425,CreateSolidBrush(RGB(255,252,211)),"Help" },
{ 200,445,300,545,CreateSolidBrush(RGB(255,252,211)),"About" },
{ 200,565,300,665,CreateSolidBrush(RGB(255,252,211)),"Exit" },
};
LRESULT CALLBACK Menu_Function(HWND Descriptor, UINT massage, WPARAM wparam, LPARAM lparam);
void draw(HWND Descriptor);
int WINAPI	WinMain(HINSTANCE Descriptor_program, HINSTANCE, LPSTR, int)
{
	WNDCLASS wnd_class = { NULL , Menu_Function , NULL , NULL ,Descriptor_program,NULL,NULL,CreateSolidBrush(RGB(255, 255, 255)),NULL,"Window_WNDCLASS" };//create class
	RegisterClass(&wnd_class);//register window
	HWND Descriptor = CreateWindow("Window_WNDCLASS", "Menu", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 100, 100, 530, 750, NULL, NULL, Descriptor_program, NULL);
	ShowWindow(Descriptor, SW_SHOW);
	UpdateWindow(Descriptor);
	MSG massage_code;
	while (GetMessage(&massage_code, NULL, 0, 0))
	{
		TranslateMessage(&massage_code);				
		DispatchMessage(&massage_code);
	}
	return 0;
}
void ButtonFunction(int i)
{
	switch (i)
	{
	case 5: 
		m[5].Brush = CreateSolidBrush(RGB(100, 100, 50));
		strcpy_s(m[5].inf, 6, "Hello");
		break;
	case 9:PostQuitMessage(0); return;
	default: return;
	}
	InvalidateRect(NULL, NULL, TRUE);
}
LRESULT CALLBACK Menu_Function(HWND Descriptor, UINT massage, WPARAM wparam, LPARAM lparam)
{
	switch (massage)
	{
	case WM_PAINT:
		draw(Descriptor); return 0;
	case WM_LBUTTONUP:
		for (int i = 0; i < 10; i++)
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
	for (int i = 0; i < 10; i++)m[i].draw(Context);
	EndPaint(Descriptor, &Paintstruct);
	ReleaseDC(Descriptor, Context);
}

