#ifndef TIMER_H
#define TIMER_H

#include "Header.h"

class Controller
{

public:
	Controller();
	~Controller();
	static Controller *ptr;
	
	void Cls_OnClose(HWND hDlg);
	
	virtual BOOL Cls_OnInitDialog(
		  HWND hDlg
		, HWND hDlgFocus
		, LPARAM lParam);
	
	virtual void Cls_OnCommand(
		  HWND hDlg
		, int ctl_ID
		, HWND ctl_Handle
		, UINT codeNotify);

	static BOOL CALLBACK DlgProc(
		  HWND hDlg
		, UINT message
		, WPARAM wParam
		, LPARAM lParam);
};

#endif