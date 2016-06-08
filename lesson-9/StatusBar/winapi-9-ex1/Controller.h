#ifndef TIMER_H
#define TIMER_H

#include "Header.h"

class Controller
{
	HWND hCheck1, hCheck2;
	HWND hEdit1, hSpin1;
	HWND hStatus;
	HICON hIcon;
public:
	Controller();
	static Controller *ptr;
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wPara, LPARAM lParam);
	BOOL Cls_OnInitDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hWnd, int id, HWND hCtl, UINT codeNotify);
	void Cls_OnClose(HWND hWnd);
};

#endif