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
	// Static Variables 
	static const int EDIT_BUFF_SIZE = 16;
	static TCHAR tEdit[EDIT_BUFF_SIZE] = { 0 };
	static TCHAR tRes[EDIT_BUFF_SIZE] = { 0 };
	static double num = 0.0;
	static double res = 0.0;
	static int str_index = 0;

	switch (message)
	{
	case WM_INITDIALOG:
		hEditAdd = GetDlgItem(hDlg, IDC_EDIT_ADD);
		hEditResult = GetDlgItem(hDlg, IDC_EDIT_RESULT);

		hBtnAdd = GetDlgItem(hDlg, IDC_EDIT_ADD);
		hBtnDel = GetDlgItem(hDlg, IDC_BTN_DEL);
		hBtnClear = GetDlgItem(hDlg, IDC_BTN_CLEAR);
		hBtnCalc = GetDlgItem(hDlg, IDC_BTN_CALC);

		hList = GetDlgItem(hDlg, IDC_LIST);
		break;

	case WM_COMMAND:
		switch (wParam)
		{
		// BUTTON add
		case IDC_BTN_ADD: 
			GetWindowText(hEditAdd, tEdit, EDIT_BUFF_SIZE);
			if (lstrlen(tEdit) == 0) {
				MessageBox(hDlg, TEXT("You have not entered data"), TEXT("Error"),MB_OK | MB_ICONEXCLAMATION);
			}
			else {
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)tEdit);
			}
			break;

		// BUTTON del
		case IDC_BTN_DEL:
			str_index = SendMessage(hList, LB_GETCURSEL, 0, 0);
			if (str_index < 0) {
				MessageBox(hDlg, TEXT("Select the line!"), TEXT("Error"), MB_OK | MB_ICONERROR);
			}
			else {
				SendMessage(hList, LB_DELETESTRING, str_index, 0);
			}
			break;

		// BUTTON calc
		case IDC_BTN_CALC:

			break;

		// BUTTON clear
		case IDC_BTN_CLEAR:

			break;
		}
		break;

	case WM_CLOSE:
		EndDialog(hDlg, 0);
		return TRUE;
	}
	return FALSE;
}