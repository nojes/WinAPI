#include <Windows.h>
#include <cstdio>
#include <CommCtrl.h>

#include "resource.h"

#pragma comment(lib, "comctl32")

/**
*	"Dynamic Controls example 2"
*/

// StaticText's
HWND hStaticR, hStaticG, hStaticB;
// ProgressBar's
HWND hProgressColor;
// Slider's
HWND hSliderR, hSliderG, hSliderB;



BOOL CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), nullptr, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	const int RANGE_MIN = 0;
	const int RANGE_MAX = 255;
	const int DEF_POS = 127;

	TCHAR tR[8] = { 0 };
	TCHAR tG[8] = { 0 };
	TCHAR tB[8] = { 0 };

	static int R = 0;
	static int G = 0;
	static int B = 0;

	switch (message)
	{
	case WM_INITDIALOG:
		// init
		hStaticR = GetDlgItem(hDlg, IDC_STATIC_R);
		hStaticG = GetDlgItem(hDlg, IDC_STATIC_G);
		hStaticB = GetDlgItem(hDlg, IDC_STATIC_B);
		hSliderR = GetDlgItem(hDlg, IDC_SLIDER_R);
		hSliderG = GetDlgItem(hDlg, IDC_SLIDER_G);
		hSliderB = GetDlgItem(hDlg, IDC_SLIDER_B);
		hProgressColor = GetDlgItem(hDlg, IDC_PROGRESS_COLOR);

		// set range
		SendMessage(hSliderR, TBM_SETRANGE, TRUE, MAKELPARAM(RANGE_MIN, RANGE_MAX));
		SendMessage(hSliderG, TBM_SETRANGE, TRUE, MAKELPARAM(RANGE_MIN, RANGE_MAX));
		SendMessage(hSliderB, TBM_SETRANGE, TRUE, MAKELPARAM(RANGE_MIN, RANGE_MAX));
		// set position
		SendMessage(hSliderR, TBM_SETPOS, TRUE, DEF_POS);
		SendMessage(hSliderG, TBM_SETPOS, TRUE, DEF_POS);
		SendMessage(hSliderB, TBM_SETPOS, TRUE, DEF_POS);
		// set tick
		SendMessage(hSliderR, TBM_SETTICFREQ, 10, 0);
		SendMessage(hSliderG, TBM_SETTICFREQ, 10, 0);
		SendMessage(hSliderB, TBM_SETTICFREQ, 10, 0);
		// set line size
		SendMessage(hSliderR, TBM_SETLINESIZE, 0, 1);
		SendMessage(hSliderG, TBM_SETLINESIZE, 0, 1);
		SendMessage(hSliderB, TBM_SETLINESIZE, 0, 1);
		break;

	case WM_COMMAND:
	
		break;

	case WM_CLOSE:
		EndDialog(hDlg, 0);
		return TRUE;

	case WM_HSCROLL:
		// get position
		R = SendMessage(hSliderR, TBM_GETPOS, 0, 0);
		G = SendMessage(hSliderG, TBM_GETPOS, 0, 0);
		B = SendMessage(hSliderB, TBM_GETPOS, 0, 0);
		// format static text's
		swprintf_s(tR, L"R: %d", R);
		swprintf_s(tG, L"G: %d", G);
		swprintf_s(tB, L"B: %d", B);
		// set static text's
		SetWindowText(hStaticR, tR);
		SetWindowText(hStaticG, tG);
		SetWindowText(hStaticB, tB);
		// set color
		SendMessage(hProgressColor, PBM_SETBKCOLOR, 0, LPARAM(RGB(R, G, B)));
		break;
	}
	return FALSE;
}