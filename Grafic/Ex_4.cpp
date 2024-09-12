#define _CRT_SECURE_NO_WARNINGS
#include <windows.h> 
#include <tchar.h> /// вызов файлов вклюний
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");
int APIENTRY _tWinMain(HINSTANCE This, /// This — дескриптор
	HINSTANCE Prev, /// Prev — параметр
	LPTSTR cmd, /// cmd — указатель командной строки
	int mode) /// mode — режим отображения окна
{
	setlocale(LC_ALL, "Ru");
	HWND hWnd; /// hWnd — предназначена для хранения дескриптора главного окна программы
	MSG msg; /// msg — это структура, в которой хранится информация о сообщении, передаваемом операционной системой окну приложения
	WNDCLASS wc; /// Класс окна
	wc.hInstance = This;
	wc.lpszClassName = WinName; /// имя
	wc.lpfnWndProc = WndProc; /// функция
	wc.style = CS_HREDRAW | CS_VREDRAW; /// стиль
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); /// иконка
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); /// курсор
	wc.lpszMenuName = NULL; /// меню
	wc.cbClsExtra = 0; /// доп данные класса
	wc.cbWndExtra = 0; /// доп данные окна
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);  /// цвет фона
	if (!RegisterClass(&wc)) return 0; /// регистрация класса окна

	hWnd = CreateWindow(WinName, /// имя
		_T("Student Taranov 305"), /// заголовок
		WS_OVERLAPPEDWINDOW, /// стиль
		CW_USEDEFAULT, /// x
		CW_USEDEFAULT, /// y
		CW_USEDEFAULT, /// Ширина
		CW_USEDEFAULT, /// высота
		HWND_DESKTOP, /// дескриптор родитля
		NULL, /// меню
		This, /// дескрипт приложения
		NULL); /// доп инфа
	ShowWindow(hWnd, mode);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); /// трансляция нажатой клавиши
		DispatchMessage(&msg); /// сообщение для WndProc
	}
}
/// LRESULT вызов от ОС, CALLBACK получение сообщения из очериди
/// Оконная функция также является функцией обратного вызова, что связано с  некоторыми особенностями организации вызовов операционной системы.
/// Эта функция регистрируется в системе, а ее вызов осуществляет операционная система, когда требуется обработать сообщение
LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam) /// Тип WPARAM — "короткий параметр" был предназначен для передачи 16-разрядного значения в 16-разрядной операционной системе, в Win32 это такое же 32-разрядное значение, что и LPARAM
{
	PAINTSTRUCT ps;
	HDC hdc;
	int M_ = 1;
	static HPEN hpen1, hpen2;
	int a, b, x_scr = 0, y_scr = 0;
	static int sx, sy;
	double x, h;

	switch (message) /// обработка сообщений
	{
	case WM_CREATE:
		hpen1 = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
		hpen2 = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		break;

	case WM_SIZE:
		sx = LOWORD(lParam); //ширина окна
		sy = HIWORD(lParam); //высота окна 
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);;
		a = sx / 2;
		b = sy / 2;
		SelectObject(hdc, hpen1);
		MoveToEx(hdc, 0, b, NULL);
		LineTo(hdc, sx, b);
		MoveToEx(hdc, a, 0, NULL);
		LineTo(hdc, a, sy);
		MoveToEx(hdc, 0, b, NULL);
		SelectObject(hdc, hpen2);
		h = 3 * M_ + 3,14 / a;

		for (x = M_ +- 3,14, x_scr = 0; x < M_ + 3,14; x += h)
		{
			x_scr = (x + M_ + 3,14) * a / M_ + 3,14;
			y_scr == b - b * sin(x);
			LineTo(hdc, x_scr, y_scr);
		}

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		DeleteObject(hpen1);
		DeleteObject(hpen2);
		PostQuitMessage(0);
		break;
		/// обработка завершения
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}