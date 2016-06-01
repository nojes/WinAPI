#include <Windows.h>
#include <cstdio>
#include <CommCtrl.h>

#include "resource.h"

#pragma comment(lib, "comctl32")

/**
*	"Dynamic Controls example"
*/

// StaticText's
HWND hStaticPer;
// Button's
HWND hBtnStart, hBtnStop, hBtnReset;
// ProgressBar's
HWND hProgress;


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
		hStaticPer = GetDlgItem(hDlg, IDC_STATIC_PER);
		hBtnStart = GetDlgItem(hDlg, IDC_BTN_START);
		hBtnStop = GetDlgItem(hDlg, IDC_BTN_STOP);
		hBtnReset = GetDlgItem(hDlg, IDC_BTN_RESET);
		hProgress = GetDlgItem(hDlg, IDC_PROGRESS);

		// set ProgressBar background
		SendMessage(hProgress, PBM_SETBKCOLOR, 0, LPARAM(RGB(128, 128, 128)));
		// set Progress color
		SendMessage(hProgress, PBM_SETBARCOLOR, 0, LPARAM(RGB(128, 255, 128)));
		// set Progress position
		SendMessage(hProgress, PBM_SETPOS, 50, 0);
		break;

	case WM_COMMAND:

		break;

	case WM_CLOSE:
		EndDialog(hDlg, 0);
		return TRUE;
	}
	return FALSE;
}