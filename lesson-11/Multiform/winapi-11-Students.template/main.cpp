// winapi-11-Students.template.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "winapi-11-Students.template.h"

#define MAX_LOADSTRING 100

#define IDC_LIST				2001
#define IDC_EDIT				3001
#define IDC_BTN_ADD				4001
#define IDC_BTN_DEL				4002
#define IDC_BTN_EDIT			4003

const int TCHAR_LEN = 256;
const int STUDENTS = 3;

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
HWND hEdit;
HWND hList;
HWND hBtnAdd, hBtnDel, hBtnEdit;

TCHAR tBuff[1024];
int stud_index;

struct Student
{
	TCHAR name[TCHAR_LEN];
	TCHAR birth[TCHAR_LEN];
	TCHAR phone[TCHAR_LEN];
	TCHAR email[TCHAR_LEN];
	TCHAR address[TCHAR_LEN];
};

Student students[STUDENTS] {
		{ L"Vasya Pupkin", L"01.01.1970", L"111-11-11", L"vasya.pupkin@gmail.com", L"Saksaganskohgo, 10" },
		{ L"Kolya Pupkin", L"12.14.1975", L"222-22-22", L"kolya.pupkin@gmail.com", L"Saksaganskohgo, 15" },
		{ L"Sveta Pupkina", L"27.04.1980", L"333-33-33", L"sveta.pupkina@gmail.com", L"Saksaganskohgo, 10" }
};
std::vector<Student> v(students, students + 3);


// Forward declarations of functions included in this code module:
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

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WINAPI11STUDENTSTEMPLATE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI11STUDENTSTEMPLATE));

	// Main message loop:
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


ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI11STUDENTSTEMPLATE));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WINAPI11STUDENTSTEMPLATE);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
		MoveWindow(hWnd, 750, 350, 500, 400, TRUE);
		SetWindowText(hWnd, L"Students");

		hList = CreateWindowEx(0, L"LISTBOX", 
			L"", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LBS_NOTIFY,
			10, 10, 200, 250,
			hWnd, HMENU(IDC_LIST), hInst, 0
			);

		hEdit = CreateWindowEx(0, L"EDIT",
			L"", WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_READONLY | WS_BORDER,
			230, 10, 200, 242,
			hWnd, (HMENU)IDC_EDIT, hInst, 0
			);

		hBtnAdd = CreateWindowEx(0, L"BUTTON",
			L"+", WS_CHILD | WS_VISIBLE,
			20, 300, 100, 30,
			hWnd, (HMENU)IDC_BTN_ADD, hInst, 0
			);

		hBtnDel = CreateWindowEx(0, L"BUTTON",
			L"-", WS_CHILD | WS_VISIBLE,
			130, 300, 100, 30,
			hWnd, (HMENU)IDC_BTN_ADD, hInst, 0
			);

		hBtnEdit = CreateWindowEx(0, L"BUTTON",
			L"Edit", WS_CHILD | WS_VISIBLE,
			340, 300, 100, 30,
			hWnd, (HMENU)IDC_BTN_ADD, hInst, 0
			);

		for (size_t i = 0; i < v.size(); i++)
		{
			SendMessage(hList, LB_ADDSTRING, 0, LPARAM(v[i].name));
		}
		SendMessage(hList, LB_SETCURSEL, 0, 0);

		break;

	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDC_LIST: {
			stud_index = SendMessage(hList, LB_GETCURSEL, 0, 0);
			
			Student s = v[stud_index];
			lstrcpy(tBuff, L"\r\t Personal data");
			lstrcat(tBuff, L"\r\n Address: \r\n ");
			lstrcat(tBuff, s.address);
			lstrcat(tBuff, L"\r\n Birth: \r\n ");
			lstrcat(tBuff, s.birth);
			lstrcat(tBuff, L"\r\n Email: \r\n ");
			lstrcat(tBuff, s.email);
			lstrcat(tBuff, L"\r\n Phone: \r\n ");
			lstrcat(tBuff, s.phone);

			SetWindowText(hEdit, tBuff);
			break;
		}

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
		// TODO: Add any drawing code here...
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

// Message handler for about box.
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
