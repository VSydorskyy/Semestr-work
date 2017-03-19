#include<windows.h>
void Create(menu_button **begin,int *amount);
void Input(menu_button **begin,int *amount);
class button
{
public:
	RECT rect;
	HBRUSH Brush;
	char inf[10];
	void draw(HDC Context)
	{
		FillRect(Context, &rect, Brush);
		SetBkMode(Context, TRANSPARENT);
		DrawText(Context, inf, 10, &rect, DT_CENTER | DT_BOTTOM);
	}
	bool CheckClick(int x, int y)
	{
		if (x > rect.left && x<rect.right && y>rect.top && y < rect.bottom)
			return 1;
		return 0;
	}
}m[5]{ { 200,90,300,190,CreateSolidBrush(RGB(0,255,0)),"Play" },{ 200,200,300,300,CreateSolidBrush(RGB(0,255,0)),"Settings" } ,{ 200,310,300,410,CreateSolidBrush(RGB(0,255,0)),"Help" },{200,420,300,520,CreateSolidBrush(RGB(100,20,30)),"About"},{200,530,300,630,CreateSolidBrush(RGB(20,30,40)),"Exit"} };
struct menu_button
{
	button but;
	menu_button* next;
}
LRESULT CALLBACK Menu_Function(HWND Descriptor, UINT massage, WPARAM wparam, LPARAM lparam);
void draw(HWND Descriptor);
int WINAPI	WinMain(HINSTANCE Descriptor_program, HINSTANCE, LPSTR, int)
{
	WNDCLASS wnd_class = { NULL , Menu_Function , NULL , NULL ,Descriptor_program,NULL,NULL,CreateSolidBrush(RGB(255, 255, 255)),NULL,"Window_WNDCLASS" };//create class
	RegisterClass(&wnd_class);//register window
	HWND Descriptor = CreateWindow("Window_WNDCLASS", "Menu", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 100, 100, 530, 750, NULL, NULL, Descriptor_program, NULL);
	ShowWindow(Descriptor, SW_SHOW);
	UpdateWindow(Descriptor);
	int amount=0;
	menu_button* begin=0;
	Create(&begin,&amount);
	Input(&begin,&amount,200,200,300,300,CreateSolidBrush(RGB(0,255,0)),"Settings");
	Input(&begin,&amount,200,310,300,410,CreateSolidBrush(RGB(0,255,0)),"Help");
	Input(&begin,&amount,200,420,300,520,CreateSolidBrush(RGB(100,20,30)),"About");
	Input(&begin,&amount,200,530,300,630,CreateSolidBrush(RGB(20,30,40)),"Exit");
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
	case 0: 
		m[0].Brush = CreateSolidBrush(RGB(100, 100, 50));
		strcpy(m[0].inf,"Hello");
		break;
	case 4:PostQuitMessage(0); return;
	default: return;
	}
	InvalidateRect(NULL, NULL, TRUE);
}
LRESULT CALLBACK Menu_Function(HWND Descriptor, UINT massage, WPARAM wparam, LPARAM lparam)
{
	switch (massage)
	{
	case WM_PAINT:draw(Descriptor); return 0;
	case WM_LBUTTONUP:
		for (int i = 0; i < 5; i++)
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
	for (int i = 0; i < 5; i++)m[i].draw(Context);
	RECT rect = { 1,1,100,100 };
	EndPaint(Descriptor, &Paintstruct);
	ReleaseDC(Descriptor, Context);
}
void Create(menu_button **begin,int *amount)
{
	*begin = new menu_button;
	(*begin)->but.rect.bottom=200;
	(*begin)->but.rect.left=90;
	(*begin)->but.rect.right=300;
	(*begin)->but.rect.top=190;
	(*begin)->but.Brush = CreateSolidBrush(RGB(0,255,0));
	(*begin)->but.inf="Play"
	(*begin)->next=0;
	*amount=*amount+1; 
}
void Input(time **begin,int *amount,int x1, int y1, int x2, int y2, HBRUSH Brush_new,char*inf_new )
{
	menu_button *input= *begin;
	while(input->next) input=input->next;
	input->next= new menu_button;
	input=input->next;
	input->but.rect.bottom=y2;
	input->but.rect.left=x1;
	input->but.rect.right=x2;
	input->but.rect.top=y1;
	input->but.Brush = Brush_new;
	strcpy(input->but.inf, inf_new)
}
