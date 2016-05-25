#include <Windows.h>
#include <cstdio>
#include <vector>

#include "resource.h"

// ComboBoxes
HWND hComboCategory;
// List's
HWND hListCatalog, hListBasket;
// Button's
HWND hBtnEditItem, hBtnAddItem, hBtnClearBasket, hBtnDelBasketItem, hBtnSubmit;
// Edit's
HWND hSum;
// Check's
HWND hCheckSaveReport;


BOOL CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), nullptr, DlgProc);
}


BOOL CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	const int CAT_SIZE = 5;
	TCHAR *categories[CAT_SIZE] = {
		L"спортивные товары",
		L"товары для дома",
		L"автотовары",
		L"телефоны",
		L"компьютеры, ноутбуки"
	};

	switch (message)
	{
	case WM_INITDIALOG:
		// ComboBoxes
		hComboCategory = GetDlgItem(hDlg, IDC_COMBO_CATEGORY);
		// List's
		hListBasket = GetDlgItem(hDlg, IDC_LIST_BASKET);
		hListCatalog = GetDlgItem(hDlg, IDC_LIST_CATALOG);
		// Button's
		hBtnAddItem = GetDlgItem(hDlg, IDC_BTN_ADD_ITEM);
		hBtnClearBasket = GetDlgItem(hDlg, IDC_BTN_CLEAR_BASKET);
		hBtnDelBasketItem = GetDlgItem(hDlg, IDC_BTN_DEL_BASKET_ITEM);
		hBtnEditItem = GetDlgItem(hDlg, IDC_BTN_EDIT_ITEM);
		hBtnSubmit = GetDlgItem(hDlg, IDC_BTN_SUBMIT);
		// Edit's
		hSum = GetDlgItem(hDlg, IDC_SUM);
		// Check's
		hCheckSaveReport = GetDlgItem(hDlg, IDC_CHECK_SAVE_RERT);

		for (size_t i = 0; i < CAT_SIZE; i++) {
			SendMessage(hComboCategory, CB_ADDSTRING, 0, LPARAM(categories[i]));
		}
		SendMessage(hComboCategory, CB_SETCURSEL, 0, 0);
		break;

	case WM_COMMAND:

		break;

	case WM_CLOSE:
		EndDialog(hDlg, 0);
		return TRUE;
	}
	return FALSE;
}