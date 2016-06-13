#include "MainDialog.h"
#include "AdditionalDialog.h"

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
	{
		MessageBox(hDlg, L"BUTTON1", L"MainDialog", MB_OK);

		TCHAR buff[100];
		GetWindowText(hEdit1, buff, 100);

		AdditionalDialog ad(buff);
		DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG2), hDlg, AdditionalDialog::DlgProc);

		//EndDialog(hDlg, 0);
		break;
	}
	}
}