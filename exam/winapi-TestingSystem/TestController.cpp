#include "TestController.h"

TestController* TestController::ptr = NULL;


TestController::TestController(Student s)
{
	ptr = this;
	this->s = s;
	this->curr_q_index = 0;
	lstrcpy(this->data_path, L"Data/");
}

TestController::~TestController()
{
	this->hChecksAnswers.clear();
	this->tests.clear();
	this->ans.clear();
}

void TestController::Cls_OnClose(HWND hDlg)
{
	EndDialog(hDlg, 0);
}

BOOL TestController::Cls_OnInitDialog(HWND hDlg, HWND hDlgFocus, LPARAM lParam)
{
	this->hDlg = hDlg;
	this->SetHandlers();
	
	this->disableQuestionGroup();
	this->renderTestsGroup();

	SendMessage(this->hListTests, LB_SETCURSEL, 0, 0);
	this->loadCurrentTest();

	return TRUE;
}

void TestController::Cls_OnCommand(HWND hDlg, int ctl_ID, HWND ctl_Handle, UINT codeNotify)
{
	switch (LOWORD(ctl_ID))
	{
		case IDC_BTN_START_TEST:
		{
			this->disableTestGroup();
			this->enableQuestionGroup();
			this->renderQuestionGroup();
			Record new_r;
			this->r = new_r;

			break;
		}

		case IDC_BTN_SUBMIT:
		{
			this->CheckAnswer();

			if (this->isEnd())
			{
				this->curr_q_index = 0;
				this->enableTestGroup();
				this->disableQuestionGroup();

				r.setTest(t);
				r.setStudent(s);
				result_c.setRecord(r);
				DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG_RESULTS), NULL, ResultController::DlgProc);
			}
			else {
				this->curr_q_index++;
				this->renderQuestionGroup();
			}
			this->resetAnsCheckBoxes();

			break;
		}

		case IDC_LIST_TESTS:
			if (codeNotify == LBN_SELCHANGE)
			{
				if (!this->loadCurrentTest()) {
					EnableWindow(this->hBtnStartTest, FALSE);
				} else {
					EnableWindow(this->hBtnStartTest, TRUE);
				}
			}
			break;
	}
}

BOOL CALLBACK TestController::DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hDlg, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hDlg, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hDlg, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}

void TestController::renderQuestionGroup()
{
	this->t = this->tests[SendMessage(this->hListTests, LB_GETCURSEL, 0, 0)];
	this->q = this->t.getQuestion(this->curr_q_index);
	this->ans = this->q.getAnswers();

	SetWindowText(this->hEditQuestion, this->q.getText());
	for (size_t i = 0; i < hChecksAnswers.size(); i++)
	{
		SetWindowText(this->hChecksAnswers[i], this->ans[i].getText());
	}
}

bool TestController::renderTestsGroup()
{
	if (this->tests.empty()) { 
		if (!this->loadTestsTitlesFromFile()) {
			MessageBox(hDlg, L"File \"Tests.txt\" not found", L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
	}
	for (size_t i = 0; i < this->tests.size(); i++) {
		SendMessage(this->hListTests, LB_ADDSTRING, 0, LPARAM(tests[i].getTitle()));
	}
	return true;
}


void TestController::resetAnsCheckBoxes()
{
	for (size_t i = 0; i < hChecksAnswers.size(); i++)
	{
		SendMessage(this->hChecksAnswers[i], BM_SETCHECK, BST_UNCHECKED, 0);
	}
}

void TestController::SetHandlers()
{
	this->hBtnStartTest = GetDlgItem(hDlg, IDC_BTN_START_TEST);
	this->hBtnSubmit = GetDlgItem(hDlg, IDC_BTN_SUBMIT);
	this->hListTests = GetDlgItem(hDlg, IDC_LIST_TESTS);
	this->hEditQuestion = GetDlgItem(hDlg, IDC_EDIT_QUESTION);
	for (size_t i = 0; i < Question::ANSWERS_AMOUNT; i++) {
		this->hChecksAnswers.push_back(GetDlgItem(hDlg, IDC_CHECK_ANS_0 + i));
	}
}

void TestController::CheckAnswer()
{
	std::vector<bool> checks;
	std::vector<bool> right_checks = { false, false, false, false };
	std::vector<int> rigth_ans_indexes = this->q.getRightAnswers();

	for (size_t i = 0; i < hChecksAnswers.size(); i++) {
		checks.push_back(SendMessage(this->hChecksAnswers[i], BM_GETCHECK, 0, 0));
	}

	for (size_t i = 0; i < rigth_ans_indexes.size(); i++) {
		right_checks[rigth_ans_indexes[i]] = true;
	}

	if (checks == right_checks) {
		this->r.addRightQuestion();
	}
}

bool TestController::isEnd()
{
	return (this->curr_q_index == this->t.getQuestionsAmount() - 1);
}


void TestController::enableQuestionGroup()
{
	ShowWindow(this->hBtnSubmit, TRUE);
	ShowWindow(this->hEditQuestion, TRUE);
	for (size_t i = 0; i < hChecksAnswers.size(); i++)
	{
		ShowWindow(this->hChecksAnswers[i], TRUE);
	}
}

void TestController::enableTestGroup()
{
	EnableWindow(this->hBtnStartTest, TRUE);
	EnableWindow(this->hListTests, TRUE);
}


void TestController::disableQuestionGroup()
{
	ShowWindow(this->hBtnSubmit, FALSE);
	ShowWindow(this->hEditQuestion, FALSE);
	for (size_t i = 0; i < hChecksAnswers.size(); i++)
	{
		ShowWindow(this->hChecksAnswers[i], FALSE);
	}
}

void TestController::disableTestGroup()
{
	EnableWindow(this->hBtnStartTest, FALSE);
	EnableWindow(this->hListTests, FALSE);
}


bool TestController::loadTestsTitlesFromFile()
{
	std::ifstream fin;
	fin.open("Data/Tests.txt", std::ios_base::in);
	if (!fin.is_open()) {
		return false;
	}
	else {
		while (!fin.eof())
		{
			Test t;
			// parse Test title
			fin.getline(cBuff, 128);
			wsprintf(tBuff, L"%S", cBuff);
			t.setTitle(tBuff);

			// parse Test filename
			fin.getline(cBuff, 128);
			wsprintf(tBuff, L"%S", cBuff);
			t.setFileName(tBuff);

			this->tests.push_back(t);
		}
		fin.close();
	}
	return true;
}

bool TestController::loadCurrentTest()
{
	int t_index = SendMessage(this->hListTests, LB_GETCURSEL, 0, 0);

	if (!this->tests[t_index].loadQuestionsFromFile()) {
		wsprintf(tBuff, L"%s%s%s", L"File \"", tests[t_index].getFileName(), L"\" not found.");
		MessageBox(hDlg, tBuff, L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	return true;
}