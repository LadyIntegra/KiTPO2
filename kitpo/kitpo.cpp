// kitpo.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "kitpo.h"

#define MAX_LOADSTRING 100
#define MAX_WORD_LENGTH 256
#define MAX_WORD_COUNT	256

// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна
HWND hWnd1, hWnd2, hWnd3, hWnd4, hWnd5;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: разместите код здесь.
	MSG msg;
	HACCEL hAccelTable;

	// Инициализация глобальных строк
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_KITPO, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KITPO));

	// Цикл основного сообщения:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KITPO));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_KITPO);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	   50, 50, 500, 400, NULL, NULL, hInstance, NULL);
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND	- обработка меню приложения
//  WM_PAINT	-Закрасить главное окно
//  WM_DESTROY	 - ввести сообщение о выходе и вернуться.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	int i, n, k, l;
	TCHAR buf1[MAX_WORD_COUNT * MAX_WORD_LENGTH];
	TCHAR buf2[MAX_WORD_LENGTH];
	int size;
	FILE *file;

	switch (message)
	{
	case WM_CREATE:
		hWnd1 = CreateWindow(_T("EDIT"), NULL, WS_BORDER | WS_VISIBLE | WS_CHILD | ES_LEFT,
			20, 20, 100, 25, hWnd, (HMENU)ID_TEXTBOX1, NULL, NULL);
		hWnd2 = CreateWindow(_T("EDIT"), NULL, WS_BORDER | WS_VISIBLE | WS_CHILD | ES_LEFT | ES_MULTILINE | ES_READONLY | WS_VSCROLL,
			20, 100, 120, 200, hWnd, (HMENU)ID_TEXTBOX2, NULL, NULL);
		hWnd3 = CreateWindow(_T("EDIT"), NULL, WS_BORDER | WS_VISIBLE | WS_CHILD | ES_LEFT,
			170, 100, 50, 25, hWnd, (HMENU)ID_TEXTBOX3, NULL, NULL);
		hWnd4 = CreateWindow(_T("EDIT"), NULL, WS_BORDER | WS_VISIBLE | WS_CHILD | ES_LEFT,
			170, 135, 50, 25, hWnd, (HMENU)ID_TEXTBOX4, NULL, NULL);
		hWnd5 = CreateWindow(_T("EDIT"), NULL, WS_BORDER | WS_VISIBLE | WS_CHILD | ES_LEFT | ES_MULTILINE | ES_READONLY | WS_VSCROLL,
			320, 100, 120, 200, hWnd, (HMENU)ID_TEXTBOX4, NULL, NULL);
		
		CreateWindow(L"button", L"Add", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			130, 20, 50, 25, hWnd, (HMENU)ID_BUTTON1, NULL, NULL);
/*		CreateWindow(L"button", L"K", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			230, 100, 50, 25, hWnd, (HMENU)ID_BUTTON2, NULL, NULL);
		CreateWindow(L"button", L"L", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			230, 135, 50, 25, hWnd, (HMENU)ID_BUTTON3, NULL, NULL);*/
		CreateWindow(L"button", L"Reposition", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			170, 235, 120, 30, hWnd, (HMENU)ID_BUTTON4, NULL, NULL);
		CreateWindow(L"button", L"Open file", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			20, 55, 120, 30, hWnd, (HMENU)ID_BUTTON5, NULL, NULL);
		CreateWindow(L"button", L"Save", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			320, 55, 120, 30, hWnd, (HMENU)ID_BUTTON6, NULL, NULL);
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case ID_BUTTON1:	// Add
		{
			size = Edit_GetText(hWnd1, buf2, MAX_WORD_LENGTH);
			buf2[size] = 0;

			if (size == 0) { MessageBox(hWnd, _T("Вы пытаетесь добавить пустую строку."), _T("Ошибка 6"), MB_OK); break; }

			size = Edit_GetText(hWnd2, buf1, MAX_WORD_LENGTH * MAX_WORD_COUNT);
			buf1[size] = 0;

			_tcscat_s(buf1, buf2);
			_tcscat_s(buf1, _T("\r\n"));

			Edit_SetText(hWnd1, _T(""));
			Edit_SetText(hWnd2, buf1);

			break;
		}
		case ID_BUTTON4:	// Reposition
		{
			
//			buf1 = new TCHAR*[MAX_WORD_COUNT];
//			for (i = 0; i < MAX_WORD_COUNT; i++) buf1[i] = new TCHAR[MAX_WORD_LENGTH];
			
			size = Edit_GetText(hWnd3, buf2, MAX_WORD_LENGTH);
			buf2[size] = 0;
			if (size == 0) { MessageBox(hWnd, _T("Введите K."), _T("Ошибка 7"), MB_OK); break; }
			i = 0;
			while (buf2[i] >= '0' && buf2[i] <= '9') i++;
			if (i != size) { MessageBox(hWnd, _T("В поле для K введено что-либо отличное от целого числа."), _T("Ошибка 4"), MB_OK); break; }
			k = _ttoi(buf2) - 1;
			
			size = Edit_GetText(hWnd4, buf2, MAX_WORD_LENGTH);
			buf2[size] = 0;
			if (size == 0) { MessageBox(hWnd, _T("Введите L."), _T("Ошибка 8"), MB_OK); break; }
			i = 0;
			while (buf2[i] >= '0' && buf2[i] <= '9') i++;
			if (i != size) { MessageBox(hWnd, _T("В поле для L введено что-либо отличное от целого числа."), _T("Ошибка 5"), MB_OK); break; }
			l = _ttoi(buf2) - 1;

			n = Edit_GetLineCount(hWnd2) - 1;
			
			if (!n) { MessageBox(hWnd, _T("Нет массива для перестановки"), _T("Ошибка 1"), MB_OK); break; }
			else if (n < l) { MessageBox(hWnd, _T("L больше, чем количество строк"), _T("Ошибка 2"), MB_OK); break; }
			else if (k > l) { MessageBox(hWnd, _T("K больше L"), _T("Ошибка 3"), MB_OK); break; }
			else if (k == -1) { MessageBox(hWnd, _T("K = 0"), _T("Ошибка 8"), MB_OK); break; }
//			else if (l == -1) { MessageBox(hWnd, _T("L = 0"), _T("Ошибка 9"), MB_OK); break; }
			else
			{
				buf1[0] = 0;
				for (i = 0; i < k; i++)
				{
					size = Edit_GetLine(hWnd2, i, buf2, MAX_WORD_LENGTH);
					buf2[size] = 0;

					_tcscat_s(buf1, buf2);
					_tcscat_s(buf1, _T("\r\n"));

				}
				for (i = l; i >= k; i--)
				{
					size = Edit_GetLine(hWnd2, i, buf2, MAX_WORD_LENGTH);
					buf2[size] = 0;

					_tcscat_s(buf1, buf2);
					_tcscat_s(buf1, _T("\r\n"));
				}
				for (i = l+1; i < n; i++)
				{
					size = Edit_GetLine(hWnd2, i, buf2, MAX_WORD_LENGTH);
					buf2[size] = 0;

					_tcscat_s(buf1, buf2);
					_tcscat_s(buf1, _T("\r\n"));
				}

				Edit_SetText(hWnd5, buf1);
			}
			
			
//			for (i = 0; i < MAX_WORD_COUNT; i++) delete[]buf1[i];
//			delete[]buf1;

			break;
		}
		case ID_BUTTON5:
			_tfopen_s(&file,_T("input.txt"), _T("r"));
			if (file == 0) { MessageBox(hWnd, _T("Не удалось открыть файл"), _T("Ошибка 10"), MB_OK); break; }
			buf1[0] = 0;
			while (!feof(file))
			{
				_fgetts(buf2, MAX_WORD_LENGTH, file);

				_tcscat_s(buf1, buf2);
				_tcscat_s(buf1, _T("\r\n"));
			}
			fclose(file);

			Edit_SetText(hWnd2, buf1);
			break;
		case ID_BUTTON6:
			_tfopen_s(&file, _T("output.txt"), _T("w"));
			if (file == 0) { MessageBox(hWnd, _T("Не удалось открыть файл"), _T("Ошибка 10"), MB_OK); break; }

			size = Edit_GetText(hWnd5, buf1, MAX_WORD_COUNT*MAX_WORD_LENGTH);
			buf1[size] = 0;

			_ftprintf(file, buf1);

			fclose(file);
			break;

		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: добавьте любой код отрисовки...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
