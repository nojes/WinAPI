#pragma once
#include "Header.h"
#include "ResultController.h"
#include "Student.h"
#include "Test.h"
#include "Record.h"

class TestController
{
	const int BUFF_LEN = 1024;
	TCHAR data_path[6];
	TCHAR tBuff[1024];
	char cBuff[256];

	HWND hDlg;
	HWND hListTests;
	HWND hBtnStartTest, hBtnSubmit;
	HWND hEditQuestion;
	std::vector<HWND> hChecksAnswers;

	int curr_q_index;		// current question index
	std::vector<Test> tests;	// Tests
	Test t;						// current Test
	Student s;					// current Student
	Question q;					// current Question
	std::vector<Answer> ans;	// current Answers
	Record r;					// current Record

	ResultController result_c;

	void SetHandlers();
	void CheckAnswer();
	void resetAnsCheckBoxes();

	bool loadTestsTitlesFromFile();
	bool loadCurrentTest();

	void renderQuestionGroup();
	bool renderTestsGroup();

	void enableQuestionGroup();
	void enableTestGroup();

	void disableQuestionGroup();
	void disableTestGroup();

	bool isEnd();
public:
	TestController(Student s);
	~TestController();
	static TestController *ptr;
	void Cls_OnClose(HWND hDlg);
	BOOL Cls_OnInitDialog(HWND hDlg, HWND hDlgFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hDlg, int ctl_ID, HWND ctl_Handle, UINT codeNotify);
	static BOOL CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};