#include "Answer.h"

int Answer::static_id = 0;

Answer::Answer()
{
	this->id = 0;
	lstrcpy(this->text, L"-");
}

Answer::Answer(TCHAR *text)
{
	this->static_id++;

	this->id = this->static_id;
	lstrcpy(this->text, text);
}

Answer::~Answer()
{
}