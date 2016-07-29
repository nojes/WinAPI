#pragma once
#include "Header.h"
#include "Answer.h"

class Question
{
	static int static_id;

	int id;
	TCHAR text[256];
	std::vector<Answer> answers;
	std::vector<int> rigth_answers;
	//TODO float weight;
public:
	static const int ANSWERS_AMOUNT = 4;

	Question();
	Question(TCHAR *text, std::vector<Answer> answers, std::vector<int> rigth_answers);
	~Question();

	TCHAR* getText() { return this->text; }
	std::vector<Answer> getAnswers() { return this->answers; }
	std::vector<int> getRightAnswers() { return this->rigth_answers; }

	void setText(TCHAR *text) { lstrcpy(this->text, text); }

	void pushAnswer(Answer a);
	void pushRightAnswer(int index);
};

