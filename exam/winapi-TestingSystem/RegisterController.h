#pragma once
#include "Header.h"
#include "TestController.h"
#include "Student.h"

class RegisterController
{
	const int BUFF_LEN = 256;
	TCHAR tBuff[256];

	// Edit controls
	HWND hEditFName, hEditLName, hEditMName, hEditGroup;
	// Button controls
	HWND hBtnStart;

	TCHAR tEditFName[128], tEditLName[128], tEditMName[128], tEditGroup[32];

	bool ValidateFields();
	void GetFields();
public:
	RegisterController();
	~RegisterController();
	static RegisterController *ptr;
	void Cls_OnClose(HWND hDlg);
	BOOL Cls_OnInitDialog(HWND hDlg, HWND hDlgFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hDlg, int ctl_ID, HWND ctl_Handle, UINT codeNotify);
	static BOOL CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};