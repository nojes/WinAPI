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
	const int EDIT_BUFF_SIZE = 16;
	TCHAR tEdit[EDIT_BUFF_SIZE] = { 0 };
	TCHAR tRes[EDIT_BUFF_SIZE] = { 0 };
	double num = 0.0;
	double sum = 0.0;
	double res = 0.0;
	int str_index = 0;
	int str_count = 0;

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
			SetWindowText(hEditAdd, L"");
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
			str_count = SendMessage(hList, LB_GETCOUNT, 0, 0);
			if (str_count == 0) {
				MessageBox(hDlg, TEXT("List is empty!"), TEXT("Error"), MB_OK | MB_ICONERROR);
			}
			else
			{
				for (size_t i = 0; i < str_count; i++)
				{
					SendMessage(hList, LB_GETTEXT, i, (LPARAM)tRes);
					sum += _wtof(tRes);
				}
				res = sum / str_count;
				swprintf_s(tRes, L"%.3f", res);
				SetWindowText(hEditResult, tRes);
			}
			
			break;

		// BUTTON clear
		case IDC_BTN_CLEAR:
			SendMessage(hList, LB_RESETCONTENT, 0, 0);
			SetWindowText(hEditResult, L"");
			break;
		}
		break;

	case WM_CLOSE:
		EndDialog(hDlg, 0);
		return TRUE;
	}
	return FALSE;
}