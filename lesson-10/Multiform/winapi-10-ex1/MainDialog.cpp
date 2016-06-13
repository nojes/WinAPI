#include "MainDialog.h"

MainDialog::MainDialog() : Controller()
{}

MainDialog::~MainDialog()
{}

BOOL MainDialog::Cls_OnInitDialog(HWND hDlg, HWND hDlgFocus, LPARAM lParam)
{
	hEdit1 = GetDlgItem(hDlg, IDC_EDIT1);
	hButton1 = GetDlgItem(hDlg, IDC_BUTTON1);
	return TRUE;
}

void MainDialog::Cls_OnCommand(HWND hDlg, int ctl_ID, HWND ctl_Handle, UINT codeNotify)
{
	switch (ctl_ID)
	{
	case IDC_BUTTON1:
		MessageBox(hDlg, L"BUTTON1", L"DEBUG", MB_OK);
		break;

	case IDC_EDIT1:
		MessageBox(hDlg, L"EDIT1", L"DEBUG", MB_OK);
		break;
	}
}