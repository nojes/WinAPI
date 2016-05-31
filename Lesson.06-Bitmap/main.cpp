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
HWND hBtnPrev, hBtnNext, hBtnStart, hBtnStop;

// images titles
TCHAR *img_titles[BMP_COUNT] {
	L"Kiev - Botanichesky sad",
	L"Kiev - Night",
	L"Kiev - Dnepr, Bridge",
	L"Kiev - Sunset",
	L"Kiev - Motherland"
};

BOOL CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), nullptr, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int img_index = 0;
	TCHAR tBuff[512] = { 0 };

	switch (message)
	{
	case WM_INITDIALOG:
		hList = GetDlgItem(hDlg, IDC_LIST);
		hStaticBmp = GetDlgItem(hDlg, IDC_STATIC_BMP);
		hBtnPrev = GetDlgItem(hDlg, IDC_BTN_PREV);
		hBtnNext = GetDlgItem(hDlg, IDC_BTN_NEXT);
		hBtnStart = GetDlgItem(hDlg, IDC_BTN_START);
		hBtnStop = GetDlgItem(hDlg, IDC_BTN_STOP);

		// get bitmap's
		for (size_t i = 0; i < BMP_COUNT; i++) {
			hBmp[i] = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP1+i));
		}

		// send images titles to list
		for (size_t i = 0; i < BMP_COUNT; i++) {
			SendMessage(hList, LB_ADDSTRING, 0, LPARAM(img_titles[i]));
		}
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BTN_NEXT: // BUTTON next image
			if (img_index < BMP_COUNT - 1) {
				++img_index;
			}
			SendMessage(hStaticBmp, STM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[img_index]));
			break;
		case IDC_BTN_PREV: // BUTTON prev image
			if (img_index != 0) {
				--img_index;
			}
			SendMessage(hStaticBmp, STM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[img_index]));
			break;
		case IDC_BTN_START: // BUTTON start slideshow
			SetTimer(hDlg, 1, 3000, NULL);
			break;
		case IDC_BTN_STOP: // BUTTON stop slideshow
			KillTimer(hDlg, 1);
			break;
		case IDC_LIST: // images LIST
			if (HIWORD(wParam) == LBN_SELCHANGE)
			{
				// get image index
				img_index = SendMessage(hList, LB_GETCURSEL, 0, 0);
				// show image
				SendMessage(hStaticBmp, STM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[img_index]));
			}
			break;
		}
		break;

	case WM_TIMER:
		// next image
		if (img_index == BMP_COUNT - 1) {
			img_index = 0;
		}
		else {
			++img_index;
		}
		// show image
		SendMessage(hStaticBmp, STM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[img_index]));
		break;

	case WM_CLOSE:
		EndDialog(hDlg, 0);
		return TRUE;
	}
	return FALSE;
}