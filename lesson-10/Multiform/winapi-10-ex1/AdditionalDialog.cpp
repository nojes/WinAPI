#include "AdditionalDialog.h"


AdditionalDialog::AdditionalDialog() : Controller()
{}
AdditionalDialog::~AdditionalDialog()
{}
AdditionalDialog::AdditionalDialog(TCHAR *text)
{
	ptr = this;
	this->text = text;
}

BOOL AdditionalDialog::Cls_OnInitDialog(HWND hDlg, HWND hDlgFocus, LPARAM lParam)
{
	hEdit = GetDlgItem(hDlg, IDC_EDIT1);
	SetWindowText(hEdit, this->text);

	return TRUE;
}
void AdditionalDialog::Cls_OnCommand(HWND hDlg, int ctl_ID, HWND ctl_Handle, UINT codeNotify)
{
	switch (ctl_ID)
	{
	
	}
}