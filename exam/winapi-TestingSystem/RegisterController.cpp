#include "RegisterController.h"

RegisterController* RegisterController::ptr = NULL;


RegisterController::RegisterController()
{
	ptr = this;
}

RegisterController::~RegisterController()
{}

void RegisterController::Cls_OnClose(HWND hDlg)
{
	EndDialog(hDlg, 0);
}

BOOL RegisterController::Cls_OnInitDialog(HWND hDlg, HWND hDlgFocus, LPARAM lParam)
{
	this->hBtnStart = GetDlgItem(hDlg, IDC_BTN_START);
	this->hEditFName = GetDlgItem(hDlg, IDC_EDIT_FNAME);
	this->hEditLName = GetDlgItem(hDlg, IDC_EDIT_LNAME);
	this->hEditMName = GetDlgItem(hDlg, IDC_EDIT_MNAME);
	this->hEditGroup = GetDlgItem(hDlg, IDC_EDIT_GROUP);

	return TRUE;
}

void RegisterController::Cls_OnCommand(HWND hDlg, int ctl_ID, HWND ctl_Handle, UINT codeNotify)
{
	switch (ctl_ID)
	{
		case IDC_BTN_START:
		{
			this->GetFields();
			if (!this->ValidateFields()) {
				MessageBox(hDlg, L"Заполните все поля", L"Ошибка", MB_OK | MB_ICONERROR);
			}
			else {
				Student s(tEditFName, tEditLName, tEditMName, tEditGroup);

				TestController test_c(s);
				DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG_TESTS), NULL, TestController::DlgProc);
			}
		}
		break;
	}
}

BOOL CALLBACK RegisterController::DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hDlg, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hDlg, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hDlg, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}

bool RegisterController::ValidateFields()
{
	if (!lstrlen(tEditFName) || !lstrlen(tEditLName) || !lstrlen(tEditMName) || !lstrlen(tEditGroup)) {
		return false;
	}
	return true;
}

void RegisterController::GetFields()
{
	GetWindowText(this->hEditFName, this->tEditFName, 128);
	GetWindowText(this->hEditLName, this->tEditLName, 128);
	GetWindowText(this->hEditMName, this->tEditMName, 128);
	GetWindowText(this->hEditGroup, this->tEditGroup, 32);
}