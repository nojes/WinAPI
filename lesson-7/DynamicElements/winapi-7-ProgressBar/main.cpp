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
HWND hBtnStart, hBtnPause, hBtnReset;
// ProgressBar's
HWND hProgress;


BOOL CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), nullptr, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	TCHAR tProgress[32] = { 0 };
	static int pos = 0;

	switch (message)
	{
	case WM_INITDIALOG:
		hStaticPer = GetDlgItem(hDlg, IDC_STATIC_PER);
		hBtnStart = GetDlgItem(hDlg, IDC_BTN_START);
		hBtnPause = GetDlgItem(hDlg, IDC_BTN_STOP);
		hBtnReset = GetDlgItem(hDlg, IDC_BTN_RESET);
		hProgress = GetDlgItem(hDlg, IDC_PROGRESS);

		// set ProgressBar background
		SendMessage(hProgress, PBM_SETBKCOLOR, 0, LPARAM(RGB(128, 128, 128)));
		// set Progress color
		SendMessage(hProgress, PBM_SETBARCOLOR, 0, LPARAM(RGB(128, 255, 128)));
		// set Progress position
		SendMessage(hProgress, PBM_SETPOS, 0, 0);
		break;

	case WM_COMMAND:
		switch (wParam)
		{
		case IDC_BTN_START:
			SetTimer(hDlg, 1, 100, NULL);
			break;
		case IDC_BTN_STOP:
			KillTimer(hDlg, 1);
			break;
		case IDC_BTN_RESET:
			pos = 0;
			SetWindowText(hStaticPer, L"0%");
			SendMessage(hProgress, PBM_SETPOS, 0, 0);
			break;
		}
		break;

	case WM_TIMER:
		if (pos < 100) {
			++pos;
			SendMessage(hProgress, PBM_SETPOS, WPARAM(pos), 0);

			swprintf_s(tProgress, L"%d%%", pos);
			SetWindowText(hStaticPer, tProgress);
		}
		else {
			KillTimer(hDlg, 1);
			MessageBox(hDlg, L"Finish", L"Yo yo", MB_OK | MB_ICONINFORMATION);
		}
		break;

	case WM_CLOSE:
		EndDialog(hDlg, 0);
		return TRUE;
	}
	return FALSE;
}