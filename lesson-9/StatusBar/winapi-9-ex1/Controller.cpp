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