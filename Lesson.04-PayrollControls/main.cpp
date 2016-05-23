#include <Windows.h>
#include <cstdio>
#include "resource.h"

// Global Variables

// Edits
HWND hEditAdd, hEditResult;
// Buttons
HWND hBtnAdd, hBtnDel, hBtnClear, hBtnCalc;
// Lists
HWND hList;

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
		hEditAdd = GetDlgItem(hDlg, IDC_EDIT_ADD);
		hEditResult = GetDlgItem(hDlg, IDC_EDIT_RESULT);

		hBtnAdd = GetDlgItem(hDlg, IDC_EDIT_ADD);
		hBtnDel = GetDlgItem(hDlg, IDC_BTN_DEL);
		hBtnClear = GetDlgItem(hDlg, IDC_BTN_CLEAR);
		hBtnCalc = GetDlgItem(hDlg, IDC_BTN_CALC);
		break;

	case WM_COMMAND:

		break;

	case WM_CLOSE:
		EndDialog(hDlg, 0);
		return TRUE;
	}
	return FALSE;
}