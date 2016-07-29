#include "Test.h"

int Test::static_id = 0;

Test::Test()
{
	this->id = 0;
	lstrcpy(this->title, L"-");
	lstrcpy(this->filename, L"test.txt");
	lstrcpy(this->data_path, L"Data/");
}

Test::Test(TCHAR * title, std::vector<Question> questions)
{
	this->static_id++;

	this->id = this->static_id;
	lstrcpy(this->title, title);
	this->questions = questions;
}

Test::Test(TCHAR *title)
{
	this->static_id++;

	this->id = this->static_id;
	lstrcpy(this->title, title);
}

Test::~Test()
{
	this->questions.clear();
}

Question Test::getQuestion(int index)
{
	return this->questions[index];
}

int Test::getQuestionsAmount()
{
	return questions.size();
}

bool Test::loadQuestionsFromFile()
{
	bool isLoad = true;

	if (this->questions.empty()) {
		wsprintf(tBuff, L"%s%s", data_path, filename);

		std::ifstream fin;
		fin.open(tBuff, std::ios_base::in);
		if (!fin.is_open()) {
			isLoad = false;
		}
		else {
			while (!fin.eof())
			{
				Question q;

				// parse Question text (title)
				fin.getline(cBuff, 256);
				wsprintf(tBuff, L"%S", cBuff);
				q.setText(tBuff);

				// parse Question answers
				for (size_t i = 0; i < Question::ANSWERS_AMOUNT; i++) {
					fin.getline(cBuff, 256);
					wsprintf(tBuff, L"%S", cBuff);
					q.pushAnswer(tBuff);
				}

				// parse Question right_answers (answers indexes)
				fin.getline(cBuff, 256);
				wsprintf(tBuff, L"%S", cBuff);
				for (size_t i = 0; i < lstrlen(tBuff); i++) {
					if (isdigit(tBuff[i])) {
						q.pushRightAnswer(_wtoi(tBuff + i));
					}
				}

				this->questions.push_back(q);
			}
		}
		fin.close();
	}
	return isLoad;
}

