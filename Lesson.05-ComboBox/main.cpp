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
	SPORT,
	PHONE,
	COMPUTERS
};
const int CAT_SIZE = 3;
TCHAR *categories[CAT_SIZE] = {
	L"sports goods",
	L"phones",
	L"computers & notebooks"
};

// GOODS - sport
const int SPORT_GOODS_SIZE = 4;
TCHAR *sport_goods[SPORT_GOODS_SIZE] = {
	L"Sport Bike >> 3850 UAN",
	L"Sport Clocks >> 2086 UAN",
	L"Sport Backpack >> 1103 UAN",
	L"Soccer Ball >> 150 UAN"
};
// GOODS - computers
const int COMPUTER_GOODS_SIZE = 3;
TCHAR *computers_goods[COMPUTER_GOODS_SIZE] = {
	L"ARTLINE Gaming X97 / i7-6700K / RAM 32GB DDR4 / GTX 980 Ti 6GB >> 57999 UAN",
	L"Everest Game 9050 / i5-4570 / RAM 8GB / GTX960 2GB >> 20599 UAN",
	L"ARTLINE Gaming X45 v01 / Athlon II X4 860K / RAM 8GB / GeForce GT 740 2GB >> 11299 UAN",
};
// GOODS - phones
const int PHONE_GOODS_SIZE = 3;
TCHAR *phone_goods[PHONE_GOODS_SIZE] = {
	L"Samsung Galaxy J3 >> 4399 UAN",
	L"Lenovo A7000 >> 3499 UAN",
	L"Apple iPhone 6 >> 13999 UAN",
};

BOOL CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), nullptr, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	TCHAR tBuff[512] = { 0 };
	
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
	{
		// Get category selection
		int cat = SendMessage(hComboCategory, CB_GETCURSEL, 0, 0);

		switch (wParam)
		{
		case IDC_BTN_ADD_ITEM: // BUTTON add item
		{
			// get count of items
			int items_count = SendMessage(hListGoods, LB_GETCOUNT, 0, 0);
			if (!items_count) {
				MessageBox(hDlg, L"List is empty!", L"Error", MB_OK | MB_ICONERROR);
			}
			else 
			{
				// get current selection
				int index = SendMessage(hListGoods, LB_GETCURSEL, 0, 0);
				// get item text
				SendMessage(hListGoods, LB_GETTEXT, index, LPARAM(tBuff));
				// send item to Basket list
				SendMessage(hListBasket, LB_ADDSTRING, 0, LPARAM(tBuff));
			}
			break;
		}
		case IDC_BTN_EDIT_ITEM: // BUTTON edit item
			break;
		case IDC_BTN_DEL_BASKET_ITEM: // BUTTON delete item from basket
			break;
		case IDC_BTN_CLEAR_BASKET: // BUTTON delete all items from basket
			break;
		case IDC_BTN_SUBMIT: // BUTTON make order (buy)
			break;
		}
		if (LOWORD(wParam) == IDC_COMBO_CATEGORY && HIWORD(wParam) == CBN_SELCHANGE) 
		{
			// Clear goods list
			SendMessage(hListGoods, LB_RESETCONTENT, 0, 0);

			// Send goods to List
			switch (cat)
			{
			case SPORT:
				for (size_t i = 0; i < SPORT_GOODS_SIZE; i++) {
					SendMessage(hListGoods, LB_ADDSTRING, 0, LPARAM(sport_goods[i]));
				}
				break;
			case PHONE:
				for (size_t i = 0; i < PHONE_GOODS_SIZE; i++) {
					SendMessage(hListGoods, LB_ADDSTRING, 0, LPARAM(phone_goods[i]));
				}
				break;
			case COMPUTERS:
				for (size_t i = 0; i < COMPUTER_GOODS_SIZE; i++) {
					SendMessage(hListGoods, LB_ADDSTRING, 0, LPARAM(computers_goods[i]));
				}
				break;
			}
		}
		break;
	}

	case WM_CLOSE:
		EndDialog(hDlg, 0);
		return TRUE;
	}
	return FALSE;
}