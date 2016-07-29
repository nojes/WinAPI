#pragma once
#include "Header.h"
#include "Record.h"

class ResultController
{
	TCHAR tBuff[256];

	HWND hDlg;
	HWND hEditStudentInfo;
	HWND hEditPersent;
	HWND hEditQuestionsAmount;
	HWND hEditRQuestionsAmount;

	Record r;
	Test t;
	Student s;
	float percent;

	void SetHandlers();
	
	void renderStudentInfoGroup();
	void renderResultsGroup();

public:
	ResultController();
	ResultController(Record r);
	~ResultController();
	static ResultController *ptr;
	void Cls_OnClose(HWND hDlg);
	BOOL Cls_OnInitDialog(HWND hDlg, HWND hDlgFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hDlg, int ctl_ID, HWND ctl_Handle, UINT codeNotify);
	static BOOL CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void setRecord(Record r);
};

