#pragma once
#include "Header.h"

class Student
{
	static int static_id;

	int id;
	TCHAR fname[64];
	TCHAR lname[64];
	TCHAR mname[64];
	TCHAR group[16];
public:
	Student();
	Student(TCHAR *fname, TCHAR *lname, TCHAR *mname, TCHAR *group);
	~Student();

	TCHAR* getFname() { return this->fname; }
	TCHAR* getLname() { return this->lname; }
	TCHAR* getMname() { return this->mname; }
	TCHAR* getGroup() { return this->group; }
};

