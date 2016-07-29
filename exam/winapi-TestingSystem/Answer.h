#pragma once
#include "Header.h"

class Answer
{
	static int static_id;

	int id;
	TCHAR text[128];
public:
	Answer();
	Answer(TCHAR *text);
	~Answer();

	int getId() { return this->id; }
	TCHAR* getText() { return this->text; }
};

