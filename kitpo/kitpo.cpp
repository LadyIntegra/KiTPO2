// kitpo.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "kitpo.h"

#define MAX_LOADSTRING 100
#define MAX_WORD_LENGTH 256
#define MAX_WORD_COUNT	256

// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна
HWND EditIntput, EditOutput, EditK, EditL;

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

   hWnd = CreateWindow(szWindowClass, _T("Программа"), WS_OVERLAPPEDWINDOW,
	   300, 50, 660, 430, NULL, NULL, hInstance, NULL);
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
	char print[256];
	int size;
	FILE *file;
	
	switch (message)
	{
	case WM_CREATE:

		CreateWindow(_T("STATIC"), _T("Введите массив:"), WS_CHILD | WS_VISIBLE,
			20, 15, 120, 15, hWnd, (HMENU)ID_Text, NULL, NULL);
		CreateWindow(_T("STATIC"), _T("Введите К:"), WS_CHILD | WS_VISIBLE,
			270, 45, 85, 15, hWnd, (HMENU)ID_Text1, NULL, NULL);
		CreateWindow(_T("STATIC"), _T("Введите L:"), WS_CHILD | WS_VISIBLE,
			270, 110, 85, 15, hWnd, (HMENU)ID_Text2, NULL, NULL);
		CreateWindow(_T("STATIC"), _T("Результат:"), WS_CHILD | WS_VISIBLE,
			390, 15, 80, 15, hWnd, (HMENU)ID_Text3, NULL, NULL);

		EditIntput = CreateWindow(_T("EDIT"), NULL, WS_BORDER | WS_VISIBLE | WS_CHILD | ES_LEFT | ES_MULTILINE | WS_VSCROLL | WS_HSCROLL,
			20, 45, 220, 200, hWnd, (HMENU)ID_TEXTBOX2, NULL, NULL);
		EditK = CreateWindow(_T("EDIT"), NULL, WS_BORDER | WS_VISIBLE | WS_CHILD | ES_LEFT,
			270, 70, 85, 25, hWnd, (HMENU)ID_TEXTBOX3, NULL, NULL);
		EditL = CreateWindow(_T("EDIT"), NULL, WS_BORDER | WS_VISIBLE | WS_CHILD | ES_LEFT,
			270, 135, 85, 25, hWnd, (HMENU)ID_TEXTBOX4, NULL, NULL);
		EditOutput = CreateWindow(_T("EDIT"), NULL, WS_BORDER | WS_VISIBLE | WS_CHILD | ES_LEFT | ES_MULTILINE | ES_READONLY | WS_VSCROLL | WS_HSCROLL,
			390, 45, 220, 200, hWnd, (HMENU)ID_TEXTBOX4, NULL, NULL);

		CreateWindow(_T("button"), _T("Переставить"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			250, 260, 120, 50, hWnd, (HMENU)Reposition, NULL, NULL);
		CreateWindow(_T("button"), _T("Загрузить \nиз файла"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_MULTILINE,
			60, 260, 120, 50, hWnd, (HMENU)OpenFile, NULL, NULL);
		CreateWindow(_T("button"), _T("Сохранить \nв файл"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_MULTILINE,
			430, 260, 120, 50, hWnd, (HMENU)SaveFile, NULL, NULL);
		break;

	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case Reposition:			
//			buf1 = new TCHAR*[MAX_WORD_COUNT];
//			for (i = 0; i < MAX_WORD_COUNT; i++) buf1[i] = new TCHAR[MAX_WORD_LENGTH];
			
			size = Edit_GetText(EditK, buf2, MAX_WORD_LENGTH);
			buf2[size] = 0;
			if (size == 0) { MessageBox(hWnd, _T("Поле ввода значения К не может быть пустым! \nВведите значение K"), _T("Ошибка 1"), MB_OK); break; }
			i = 0;
			while (buf2[i] >= '0' && buf2[i] <= '9') i++;
			if (i != size) { MessageBox(hWnd, _T("Внимание! \nЗначение К должно быть целым положительным числом!"), _T("Ошибка 2"), MB_OK); break; }
			k = _ttoi(buf2) - 1;
			
			size = Edit_GetText(EditL, buf2, MAX_WORD_LENGTH);
			buf2[size] = 0;
			if (size == 0) { MessageBox(hWnd, _T("Поле ввода значения L не может быть пустым! \nВведите значение L"), _T("Ошибка 3"), MB_OK); break; }
			i = 0;
			while (buf2[i] >= '0' && buf2[i] <= '9') i++;
			if (i != size) { MessageBox(hWnd, _T("Внимание! \nЗначение L должно быть целым положительным числом!"), _T("Ошибка 4"), MB_OK); break; }
			l = _ttoi(buf2) - 1;

			n = Edit_GetLineCount(EditIntput);


			
			if (!Edit_GetTextLength(EditIntput)) { MessageBox(hWnd, _T("Нет массива для перестановки! \nПопытайтесь ввести или загрузить массив снова"), _T("Ошибка 5"), MB_OK); break; }
			else if (n == 1) { MessageBox(hWnd, _T("Внимание! \nМассив должен содержать более 1 элемента \nПожалуйста, добавьте элементы массива"), _T("Ошибка 14"), MB_OK); break; }
			else if (n <= l) { MessageBox(hWnd, _T("Внимание! \nЗначение L не может быть больше, \nчем количество строк в массиве"), _T("Ошибка 6"), MB_OK); break; }
			else if (n > MAX_WORD_COUNT) { MessageBox(hWnd, _T("Превышен лимит строк"), _T("Ошибка 12"), MB_OK); break; }
			else if (k >= l) { MessageBox(hWnd, _T("Внимание! \nЗначение K не должно быть больше или равно значению L"), _T("Ошибка 7"), MB_OK); break; }
			else if (k == -1) { MessageBox(hWnd, _T("Внимание! \nЗначение K не может быть равным нулю"), _T("Ошибка 8"), MB_OK); break; }
//			else if (l == -1) { MessageBox(hWnd, _T("L = 0"), _T("Ошибка 9"), MB_OK); break; }
			else
			{
				buf1[0] = 0;
				for (i = 0; i < k; i++)
				{
					size = Edit_GetLine(EditIntput, i, buf2, MAX_WORD_LENGTH);				
					if (size == MAX_WORD_LENGTH)
					{
						sprintf_s(print, "Превышен интервал вводимого значения при вводе массива в %d ой строке", i + 1 );
						MessageBoxA(hWnd, print, "Ошибка 9", MB_OK);
						return 0;
					}
					
					buf2[size] = 0;

					_tcscat_s(buf1, buf2);
					_tcscat_s(buf1, _T("\r\n"));
				}
				for (i = l; i >= k; i--)
				{
					size = Edit_GetLine(EditIntput, i, buf2, MAX_WORD_LENGTH);
					if (size == MAX_WORD_LENGTH)
					{
						sprintf_s(print, "Превышен интервал вводимого значения при вводе массива в %d ой строке", i + 1);
						MessageBoxA(hWnd, print, "Ошибка 9", MB_OK);
						return 0;
					}
						
					buf2[size] = 0;

					_tcscat_s(buf1, buf2);
					_tcscat_s(buf1, _T("\r\n"));
				}
				for (i = l+1; i < n; i++)
				{
					size = Edit_GetLine(EditIntput, i, buf2, MAX_WORD_LENGTH);
					if (size == MAX_WORD_LENGTH)
					{
						sprintf_s(print, "Превышен интервал вводимого значения при вводе массива в %d ой строке", i + 1);
						MessageBoxA(hWnd, print, "Ошибка 9", MB_OK);
						return 0;
					}
					
					buf2[size] = 0;

					_tcscat_s(buf1, buf2);
					_tcscat_s(buf1, _T("\r\n"));
				}

				Edit_SetText(EditOutput, buf1);
			}
			
			
//			for (i = 0; i < MAX_WORD_COUNT; i++) delete[]buf1[i];
//			delete[]buf1;

			break;

		case OpenFile:
			HANDLE hFile;
			hFile = CreateFile(_T("input.txt"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (INVALID_HANDLE_VALUE == hFile)
			{
				MessageBox(hWnd, _T("Внимание! \nНе удалось открыть файл \"input.txt\" "), _T("Ошибка 10"), MB_OK); break; 
			}
			DWORD size;
			size = GetFileSize(hFile, NULL);
			CloseHandle(hFile);
			if (size == 0)	{ MessageBox(hWnd, _T("Файл \"input.txt\" пуст "), _T("Ошибка 13"), MB_OK); break; }
			
			_tfopen_s(&file, _T("input.txt"), _T("r"));
			if (file == 0) { MessageBox(hWnd, _T("Не удалось открыть файл \"input.txt\" "), _T("Ошибка 10"), MB_OK); break; }

			buf1[0] = 0;
			while (!feof(file))
			{
				_fgetts(buf2, MAX_WORD_LENGTH, file);

				if (buf2[_tcslen(buf2) - 1] == '\n') buf2[_tcslen(buf2) - 1] = 0;

				_tcscat_s(buf1, buf2);
				_tcscat_s(buf1, _T("\r\n"));
			}
			fclose(file);
			buf1[_tcslen(buf1) - 2] = 0;
			Edit_SetText(EditIntput, buf1);
			break;

		case SaveFile:
			_tfopen_s(&file, _T("output.txt"), _T("wt"));
			if (file == 0) { MessageBox(hWnd, _T("Не удалось открыть файл \"output.txt\""), _T("Ошибка 11"), MB_OK); break; }

			size = Edit_GetText(EditOutput, buf1, MAX_WORD_COUNT*MAX_WORD_LENGTH);
			buf1[size] = 0;

			for (int i = 0; i < size; i++)
			{
				if (buf1[i] == '\r') buf1[i] = ' ';
			}
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
