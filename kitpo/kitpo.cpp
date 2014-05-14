// kitpo.cpp: ���������� ����� ����� ��� ����������.
//

#include "stdafx.h"
#include "kitpo.h"

#define MAX_LOADSTRING 100
#define MAX_WORD_LENGTH 256
#define MAX_WORD_COUNT	256

// ���������� ����������:
HINSTANCE hInst;								// ������� ���������
TCHAR szWindowClass[MAX_LOADSTRING];			// ��� ������ �������� ����
HWND EditIntput, EditOutput, EditK, EditL, hWnd1;

// ��������� ���������� �������, ���������� � ���� ������ ����:
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

 	// TODO: ���������� ��� �����.
	MSG msg;
	HACCEL hAccelTable;

	// ������������� ���������� �����
	LoadString(hInstance, IDC_KITPO, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ��������� ������������� ����������:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KITPO));

	// ���� ��������� ���������:
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
//  �������: MyRegisterClass()
//
//  ����������: ������������ ����� ����.
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
//   �������: InitInstance(HINSTANCE, int)
//
//   ����������: ��������� ��������� ���������� � ������� ������� ����.
//
//   �����������:
//
//        � ������ ������� ���������� ���������� ����������� � ���������� ����������, � �����
//        ��������� � ��������� �� ����� ������� ���� ���������.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��������� ���������� ���������� � ���������� ����������

   hWnd = CreateWindow(szWindowClass, _T("���������"), WS_OVERLAPPEDWINDOW,
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
//  �������: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����������:  ������������ ��������� � ������� ����.
//
//  WM_COMMAND	- ��������� ���� ����������
//  WM_PAINT	-��������� ������� ����
//  WM_DESTROY	 - ������ ��������� � ������ � ���������.
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

		CreateWindow(_T("STATIC"), _T("������� ������:"), WS_CHILD | WS_VISIBLE,
			20, 15, 120, 15, hWnd, (HMENU)ID_Text, NULL, NULL);
		CreateWindow(_T("STATIC"), _T("������� �:"), WS_CHILD | WS_VISIBLE,
			270, 45, 85, 15, hWnd, (HMENU)ID_Text1, NULL, NULL);
		CreateWindow(_T("STATIC"), _T("������� L:"), WS_CHILD | WS_VISIBLE,
			270, 110, 85, 15, hWnd, (HMENU)ID_Text2, NULL, NULL);
		CreateWindow(_T("STATIC"), _T("��������� ��������:"), WS_CHILD | WS_VISIBLE,
			390, 15, 140, 15, hWnd, (HMENU)ID_Text3, NULL, NULL);

		EditIntput = CreateWindow(_T("EDIT"), NULL, WS_BORDER | WS_VISIBLE | WS_CHILD | ES_LEFT | ES_MULTILINE | WS_VSCROLL,
			20, 45, 220, 200, hWnd, (HMENU)ID_TEXTBOX2, NULL, NULL);
		EditK = CreateWindow(_T("EDIT"), NULL, WS_BORDER | WS_VISIBLE | WS_CHILD | ES_LEFT,
			270, 70, 85, 25, hWnd, (HMENU)ID_TEXTBOX3, NULL, NULL);
		EditL = CreateWindow(_T("EDIT"), NULL, WS_BORDER | WS_VISIBLE | WS_CHILD | ES_LEFT,
			270, 135, 85, 25, hWnd, (HMENU)ID_TEXTBOX4, NULL, NULL);
		EditOutput = CreateWindow(_T("EDIT"), NULL, WS_BORDER | WS_VISIBLE | WS_CHILD | ES_LEFT | ES_MULTILINE | ES_READONLY | WS_VSCROLL,
			390, 45, 220, 200, hWnd, (HMENU)ID_TEXTBOX4, NULL, NULL);
		
//		CreateWindow(L"button", L"Add", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
//			130, 20, 50, 25, hWnd, (HMENU)ID_BUTTON1, NULL, NULL);
/*		CreateWindow(L"button", L"K", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			230, 100, 50, 25, hWnd, (HMENU)ID_BUTTON2, NULL, NULL);
		CreateWindow(L"button", L"L", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			230, 135, 50, 25, hWnd, (HMENU)ID_BUTTON3, NULL, NULL);*/

		CreateWindow(_T("button"), _T("�����������"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			250, 260, 120, 50, hWnd, (HMENU)Reposition, NULL, NULL);
		CreateWindow(_T("button"), _T("��������� \n�� �����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_MULTILINE,
			60, 260, 120, 50, hWnd, (HMENU)OpenFile, NULL, NULL);
		CreateWindow(_T("button"), _T("��������� \n� ����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_MULTILINE,
			430, 260, 120, 50, hWnd, (HMENU)SaveFile, NULL, NULL);
		break;

	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// ��������� ����� � ����:
		switch (wmId)
		{
		case ID_BUTTON1:	// Add
		{
			size = Edit_GetText(hWnd1, buf2, MAX_WORD_LENGTH);
			buf2[size] = 0;

			if (size == 0) { MessageBox(hWnd, _T("�� ��������� �������� ������ ������."), _T("������ 6"), MB_OK); break; }

			size = Edit_GetText(EditIntput, buf1, MAX_WORD_LENGTH * MAX_WORD_COUNT);
			buf1[size] = 0;

			_tcscat_s(buf1, buf2);
			_tcscat_s(buf1, _T("\r\n"));

			Edit_SetText(hWnd1, _T(""));
			Edit_SetText(EditIntput, buf1);

			break;
		}
		case Reposition:	// Reposition
		{
			
//			buf1 = new TCHAR*[MAX_WORD_COUNT];
//			for (i = 0; i < MAX_WORD_COUNT; i++) buf1[i] = new TCHAR[MAX_WORD_LENGTH];
			
			size = Edit_GetText(EditK, buf2, MAX_WORD_LENGTH);
			buf2[size] = 0;
			if (size == 0) { MessageBox(hWnd, _T("������� K."), _T("������ 7"), MB_OK); break; }
			i = 0;
			while (buf2[i] >= '0' && buf2[i] <= '9') i++;
			if (i != size) { MessageBox(hWnd, _T("� ���� ��� K ������� ���-���� �������� �� ������ �����."), _T("������ 4"), MB_OK); break; }
			k = _ttoi(buf2) - 1;
			
			size = Edit_GetText(EditL, buf2, MAX_WORD_LENGTH);
			buf2[size] = 0;
			if (size == 0) { MessageBox(hWnd, _T("������� L."), _T("������ 8"), MB_OK); break; }
			i = 0;
			while (buf2[i] >= '0' && buf2[i] <= '9') i++;
			if (i != size) { MessageBox(hWnd, _T("� ���� ��� L ������� ���-���� �������� �� ������ �����."), _T("������ 5"), MB_OK); break; }
			l = _ttoi(buf2) - 1;

			n = Edit_GetLineCount(EditIntput) - 1;
			
			if (!n) { MessageBox(hWnd, _T("��� ������� ��� ������������"), _T("������ 1"), MB_OK); break; }
			else if (n < l) { MessageBox(hWnd, _T("L ������, ��� ���������� �����"), _T("������ 2"), MB_OK); break; }
			else if (k > l) { MessageBox(hWnd, _T("K ������ L"), _T("������ 3"), MB_OK); break; }
			else if (k == -1) { MessageBox(hWnd, _T("K = 0"), _T("������ 8"), MB_OK); break; }
//			else if (l == -1) { MessageBox(hWnd, _T("L = 0"), _T("������ 9"), MB_OK); break; }
			else
			{
				buf1[0] = 0;
				for (i = 0; i < k; i++)
				{
					size = Edit_GetLine(EditIntput, i, buf2, MAX_WORD_LENGTH);
					buf2[size] = 0;

					_tcscat_s(buf1, buf2);
					_tcscat_s(buf1, _T("\r\n"));

				}
				for (i = l; i >= k; i--)
				{
					size = Edit_GetLine(EditIntput, i, buf2, MAX_WORD_LENGTH);
					buf2[size] = 0;

					_tcscat_s(buf1, buf2);
					_tcscat_s(buf1, _T("\r\n"));
				}
				for (i = l+1; i < n; i++)
				{
					size = Edit_GetLine(EditIntput, i, buf2, MAX_WORD_LENGTH);
					buf2[size] = 0;

					_tcscat_s(buf1, buf2);
					_tcscat_s(buf1, _T("\r\n"));
				}

				Edit_SetText(EditOutput, buf1);
			}
			
			
//			for (i = 0; i < MAX_WORD_COUNT; i++) delete[]buf1[i];
//			delete[]buf1;

			break;
		}
		case OpenFile:
			_tfopen_s(&file,_T("input.txt"), _T("r"));
			if (file == 0) { MessageBox(hWnd, _T("�� ������� ������� ����"), _T("������ 10"), MB_OK); break; }
			buf1[0] = 0;
			while (!feof(file))
			{
				_fgetts(buf2, MAX_WORD_LENGTH, file);

				_tcscat_s(buf1, buf2);
				_tcscat_s(buf1, _T("\r\n"));
			}
			fclose(file);

			Edit_SetText(EditIntput, buf1);
			break;
		case SaveFile:
			_tfopen_s(&file, _T("output.txt"), _T("w"));
			if (file == 0) { MessageBox(hWnd, _T("�� ������� ������� ����"), _T("������ 10"), MB_OK); break; }

			size = Edit_GetText(EditOutput, buf1, MAX_WORD_COUNT*MAX_WORD_LENGTH);
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
		// TODO: �������� ����� ��� ���������...
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

// ���������� ��������� ��� ���� "� ���������".
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
