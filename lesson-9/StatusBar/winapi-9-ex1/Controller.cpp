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
		0, 70, 150, -1
	};
	SendMessage(hStatus, SB_SETPARTS, 4, LPARAM(parts));
	SendMessage(hStatus, SB_SETTEXT, 1, LPARAM(L"Counter: 0"));
	SendMessage(hStatus, SB_SETTEXT, 2, LPARAM(L"Param1: Off"));
	SendMessage(hStatus, SB_SETTEXT, 3, LPARAM(L"Param2: Off"));

	return TRUE;
}

void Controller::Cls_OnCommand(HWND hWnd, int id, HWND hCtl, UINT codeNotify)
{

}

BOOL CALLBACK Controller::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hWnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hWnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}