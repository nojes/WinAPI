#include "Controller.h"

Controller* Controller::ptr = NULL;

Controller::Controller()
{
	ptr = this;
}

void Controller::Cls_OnClose(HWND hWnd)
{
	EndDialog(hWnd, 0);
}

BOOL Controller::Cls_OnInitDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam)
{
	this->hCheck1 = GetDlgItem(hWnd, IDC_CHECK1);
	this->hCheck2 = GetDlgItem(hWnd, IDC_CHECK2);
	this->hEdit1 = GetDlgItem(hWnd, IDC_EDIT1);
	this->hSpin1 = GetDlgItem(hWnd, IDC_SPIN1);

	SendMessage(hSpin1, UDM_SETRANGE32, -50, 50);
	SendMessage(hSpin1, UDM_SETBUDDY, WPARAM(hEdit1), 0);
	SetWindowText(hEdit1, L"0");
	hStatus = CreateStatusWindow(
		WS_CHILD | WS_VISIBLE | CCS_BOTTOM | SBARS_TOOLTIPS | SBARS_SIZEGRIP,
		nullptr, 
		hWnd, 
		WM_USER
	);

	int parts[4] = {
		0, 100, 200, -1
	};
	SendMessage(hStatus, SB_SETPARTS, 4, LPARAM(parts));
	SendMessage(hStatus, SB_SETTEXT, 1, LPARAM(L"Count: 0"));
	SendMessage(hStatus, SB_SETTEXT, 2, LPARAM(L"Check1: OFF"));
	SendMessage(hStatus, SB_SETTEXT, 3, LPARAM(L"Check2: OFF"));

	hIcon = LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON1));
	SendMessage(hStatus, SB_SETICON, 1, LPARAM(hIcon));

	SendMessage(hStatus, SB_SETBKCOLOR, 0, LPARAM(RGB(200, 221, 242)));

	return TRUE;
}

void Controller::Cls_OnCommand(HWND hWnd, int id, HWND hCtl, UINT codeNotify)
{
	LRESULT res;
	switch (id)
	{
	case IDC_CHECK1:
		res = SendMessage(hCheck1, BM_GETCHECK, 0, 0);
		if (res == BST_CHECKED)
		{
			SendMessage(hStatus, SB_SETTEXT, 2, LPARAM(L"Check1: ON"));
		}
		else {
			SendMessage(hStatus, SB_SETTEXT, 2, LPARAM(L"Check1: OFF"));
		}
		break;

	case IDC_CHECK2:
		res = SendMessage(hCheck2, BM_GETCHECK, 0, 0);
		if (res == BST_CHECKED)
		{
			SendMessage(hStatus, SB_SETTEXT, 3, LPARAM(L"Check2: ON"));
		}
		else {
			SendMessage(hStatus, SB_SETTEXT, 3, LPARAM(L"Check2: OFF"));
		}
		break;
	}
}

void Controller::Cls_OnVScroll(HWND hWnd, HWND hCtrl, UINT code, int pos)
{
	TCHAR tBuff[100];
	swprintf_s(tBuff, L"Count: %d", pos);
	SendMessage(hStatus, SB_SETTEXT, 1, LPARAM(tBuff));
}

BOOL CALLBACK Controller::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hWnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hWnd, WM_COMMAND, ptr->Cls_OnCommand);
		HANDLE_MSG(hWnd, WM_VSCROLL, ptr->Cls_OnVScroll);
	}
	return FALSE;
}