#pragma once
#include "Header.h"
#include "Test.h"
#include "Student.h"

class Record
{
	static int static_id;

	int id;
	Test test;
	Student student;
	int rigth_questions;
	//TODO std::vector<int> rigth_answers;
	//TODO float grade;
public:
	Record();
	Record(Test test, Student student, int right_questions);
	~Record();

	void addRightQuestion();

	Test getTest() { return this->test; }
	Student getStudent() { return this->student; }
	int getRightQuestionsAmount() { return this->rigth_questions; }

	void setTest(Test test) { this->test = test; }
	void setStudent(Student student) { this->student = student; }
};
