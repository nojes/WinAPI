#include "Question.h"

int Question::static_id = 0;

Question::Question()
{
	this->id = 0;
	lstrcpy(this->text, L"-");
}

Question::Question(TCHAR * text, std::vector<Answer> answers, std::vector<int> rigth_answers)
{
	this->static_id++;
	this->id = this->static_id;
	lstrcpy(this->text, text);
	this->answers = answers;
	this->rigth_answers = rigth_answers;
}

Question::~Question()
{
	this->answers.clear();
	this->rigth_answers.clear();
}

void Question::pushAnswer(Answer a)
{
	this->answers.push_back(a);
}

void Question::pushRightAnswer(int index)
{
	this->rigth_answers.push_back(index);
}
