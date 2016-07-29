#include "Record.h"

int Record::static_id = 0;

Record::Record()
{
	this->id = 0;
	this->rigth_questions = 0;
}

Record::Record(Test test, Student student, int right_questions)
{
	this->static_id++;

	this->id = this->static_id;
	this->test = test;
	this->student = student;
	this->rigth_questions = right_questions;
}


Record::~Record()
{
}

void Record::addRightQuestion()
{
	this->rigth_questions++;
}
