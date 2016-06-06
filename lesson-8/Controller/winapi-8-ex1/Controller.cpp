#include "Controller.h"

// init controller pointer
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
	hSpin = GetDlgItem(hWnd, IDC_SPIN1);
	hEdit = GetDlgItem(hWnd, IDC_EDIT1);
	
	// set Spin range
	SendMessage(hSpin, UDM_SETRANGE32, -50, 50);
	// set Spin buddy
	SendMessage(hSpin, UDM_SETBUDDY, WPARAM(hEdit), 0);

	// set
	SetWindowText(hEdit, L"0");
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