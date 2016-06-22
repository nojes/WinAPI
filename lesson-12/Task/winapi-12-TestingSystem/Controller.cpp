#include "Controller.h"

Controller* Controller::ptr = NULL;

Controller::Controller()
{
	ptr = this;
}

Controller::~Controller()
{}

void Controller::Cls_OnClose(HWND hDlg)
{
	EndDialog(hDlg, 0);
}

BOOL Controller::Cls_OnInitDialog(HWND hDlg, HWND hDlgFocus, LPARAM lParam)
{
	return TRUE;
}

void Controller::Cls_OnCommand(HWND hDlg, int ctl_ID, HWND ctl_Handle, UINT codeNotify)
{}

BOOL CALLBACK Controller::DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hDlg, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hDlg, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hDlg, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}