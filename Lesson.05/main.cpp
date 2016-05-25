#include <Windows.h>
#include <cstdio>

#include "resource.h"

/**
 *	"Goods Catalog"
 */

// ComboBoxes
HWND hComboCategory;
// List's
HWND hListGoods, hListBasket;
// Button's
HWND hBtnEditItem, hBtnAddItem, hBtnClearBasket, hBtnDelBasketItem, hBtnSubmit;
// Edit's
HWND hSum;
// Check's
HWND hCheckSaveReport;

// Goods categories
enum GoodsCategory {
	COMPUTERS,
	SPORT,
	PHONE
};
const int CAT_SIZE = 3;
TCHAR *categories[CAT_SIZE] = {
	L"спортивные товары",
	L"телефоны",
	L"компьютеры, ноутбуки"
};

// GOODS - sport
const int SPORT_GOODS_SIZE = 4;
TCHAR *sport_goods[SPORT_GOODS_SIZE] = {
	L"Велосипед > 3850 UAN",
	L"Часы > 2086 UAN",
	L"Рюкзак > 1103 UAN",
	L"Лыжи > 3800 UAN"
};
// GOODS - computers
const int COMPUTER_GOODS_SIZE = 3;
TCHAR *computers_goods[COMPUTER_GOODS_SIZE] = {
	L"comp i7 > 15854 UAN",
	L"comp i5 > 10199 UAN",
	L"comp i3 > 7000 UAN",
};
// GOODS - phones
const int PHONE_GOODS_SIZE = 3;
TCHAR *phone_goods[PHONE_GOODS_SIZE] = {
	L"smartphone 1 > 7154 UAN",
	L"smartphone 2 > 5451 UAN",
	L"smartphone 3 > 10548 UAN",
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
		// ComboBoxes
		hComboCategory = GetDlgItem(hDlg, IDC_COMBO_CATEGORY);
		// List's
		hListBasket = GetDlgItem(hDlg, IDC_LIST_BASKET);
		hListGoods = GetDlgItem(hDlg, IDC_LIST_GOODS);
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
		switch (wParam)
		{
		// BUTTON add item
		case IDC_BTN_ADD_ITEM:
			//int index = SendMessage(hListGoods, LB_GETCURSEL, 0, 0);
			break;
		// BUTTON edit item
		case IDC_BTN_EDIT_ITEM:
			break;
		// BUTTON delete item from basket
		case IDC_BTN_DEL_BASKET_ITEM:
			break;
		// BUTTON clear all items from basket
		case IDC_BTN_CLEAR_BASKET:
			break;
		// BUTTON make order (buy)
		case IDC_BTN_SUBMIT:
			break;
		}
		if (LOWORD(wParam) == IDC_COMBO_CATEGORY && HIWORD(wParam) == CBN_SELCHANGE) {
			// Clear goods list
			SendMessage(hListGoods, LB_RESETCONTENT, 0, 0);

			// Get category selection
			int cat = SendMessage(hComboCategory, CB_GETCURSEL, 0, 0);

			// Send goods to List
			switch (cat)
			{
			case SPORT:
				for (size_t i = 0; i < SPORT_GOODS_SIZE; i++) {
					SendMessage(hListGoods, LB_ADDSTRING, 0, LPARAM(sport_goods[i])); }
				break;
			case PHONE:
				for (size_t i = 0; i < PHONE_GOODS_SIZE; i++) {
					SendMessage(hListGoods, LB_ADDSTRING, 0, LPARAM(phone_goods[i])); }
				break;
			case COMPUTERS:
				for (size_t i = 0; i < COMPUTER_GOODS_SIZE; i++) {
					SendMessage(hListGoods, LB_ADDSTRING, 0, LPARAM(computers_goods[i])); }
				break;
			}
		}
		break;

	case WM_CLOSE:
		EndDialog(hDlg, 0);
		return TRUE;
	}
	return FALSE;
}