#pragma once
#include "Header.h"
#include "Question.h"

class Test
{
	static int static_id;
	TCHAR data_path[6];
	TCHAR tBuff[256];
	char cBuff[256];

	int id;
	TCHAR filename[16];
	TCHAR title[128];
	std::vector<Question> questions;
public:
	Test();
	Test(TCHAR *title, std::vector<Question> questions);
	Test(TCHAR *title);
	~Test();

	TCHAR* getTitle() { return this->title; }
	TCHAR* getFileName() { return this->filename; }
	std::vector<Question> getQuestions() { return this->questions; }
	Question getQuestion(int index);
	int getQuestionsAmount();

	void setQuestions(std::vector<Question> questions) { this->questions = questions; };
	void setTitle(TCHAR* title) { lstrcpy(this->title, title); };
	void setFileName(TCHAR* filename) { lstrcpy(this->filename, filename); };

	bool loadQuestionsFromFile();
};

