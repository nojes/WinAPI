#include "ResultController.h"

ResultController* ResultController::ptr = NULL;

ResultController::ResultController()
{
	ptr = this;
	this->percent = 0.0;
}

ResultController::ResultController(Record r)
{
	ptr = this;
	this->r = r;
	this->percent = 0.0;
}

ResultController::~ResultController()
{}

void ResultController::Cls_OnClose(HWND hDlg)
{
	EndDialog(hDlg, 0);
}

BOOL ResultController::Cls_OnInitDialog(HWND hDlg, HWND hDlgFocus, LPARAM lParam)
{
	this->hDlg = hDlg;
	this->SetHandlers();

	this->renderStudentInfoGroup();
	this->renderResultsGroup();

	return TRUE;
}

void ResultController::Cls_OnCommand(HWND hDlg, int ctl_ID, HWND ctl_Handle, UINT codeNotify)
{
	switch (ctl_ID)
	{
	case IDOK:
		this->Cls_OnClose(hDlg);
		break;
	}
}

BOOL CALLBACK ResultController::DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hDlg, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hDlg, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hDlg, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}

void ResultController::setRecord(Record r)
{
	this->r = r;
}

void ResultController::SetHandlers()
{
	this->hEditQuestionsAmount = GetDlgItem(hDlg, IDC_EDIT_QUESTIONS_AMOUNT);
	this->hEditRQuestionsAmount = GetDlgItem(hDlg, IDC_EDIT_R_QUESTIONS_AMOUNT);
	this->hEditStudentInfo = GetDlgItem(hDlg, IDC_EDIT_STUDENT_INFO);
	this->hEditPersent = GetDlgItem(hDlg, IDC_EDIT_PERCENT);
}

void ResultController::renderStudentInfoGroup()
{
	this->s = r.getStudent();

	wsprintf(tBuff, L" ÔÈÎ: %s %s %s \r\n Ãðóïïà: %s", s.getLname(), s.getFname(), s.getMname(), s.getGroup());
	SetWindowText(hEditStudentInfo, tBuff);
}

void ResultController::renderResultsGroup()
{
	this->t = r.getTest();
	float questions_amt = t.getQuestionsAmount();
	float rigth_questions_amt = r.getRightQuestionsAmount();
	percent = rigth_questions_amt / questions_amt * 100.0;

	swprintf(tBuff, L"%.2f%%", percent);
	SetWindowText(hEditPersent, tBuff);

	swprintf(tBuff, L"%.f", questions_amt);
	SetWindowText(hEditQuestionsAmount, tBuff);

	swprintf(tBuff, L"%.f", rigth_questions_amt);
	SetWindowText(hEditRQuestionsAmount, tBuff);
}

