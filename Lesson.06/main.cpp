#include <Windows.h>
#include <cstdio>

#include "resource.h"

/**
 *	"Simple Gallery"
 */

// bitmap's
const int BMP_COUNT = 5;
HBITMAP hBmp[BMP_COUNT];
// list's
HWND hList;
// static's
HWND hStaticBmp;
// button's
HWND hBtnPrev, hBtnNext, hBtnStart, hBtnEnd;

// images titles
TCHAR *img_titles[BMP_COUNT] {
	L"Kiev - Botanichesky sad",
	L"Kiev - Night",
	L"Kiev - Dnepr, Bridge",
	L"Kiev - Dnepr",
	L"Kiev - Sunset"
};

BOOL CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), nullptr, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		hList = GetDlgItem(hDlg, IDC_LIST);
		hStaticBmp = GetDlgItem(hDlg, IDC_STATIC_BMP);
		hBtnPrev = GetDlgItem(hDlg, IDC_BTN_PREV);
		hBtnNext = GetDlgItem(hDlg, IDC_BTN_NEXT);
		hBtnStart = GetDlgItem(hDlg, IDC_BTN_START);
		hBtnEnd = GetDlgItem(hDlg, IDC_BTN_END);

		// get bitmap's
		for (size_t i = 0; i < BMP_COUNT; i++) {
			hBmp[i] = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDR_JPG1+i));
		}

		// send images titles to list
		for (size_t i = 0; i < BMP_COUNT; i++) {
			SendMessage(hList, LB_ADDSTRING, 0, LPARAM(img_titles[i]));
		}
		break;

	case WM_COMMAND:

		break;

	case WM_CLOSE:
		EndDialog(hDlg, 0);
		return TRUE;
	}
	return FALSE;
}