#include "Student.h"

int Student::static_id = 0;

Student::Student()
{
	this->id = 0;
	lstrcpy(this->fname, L"-");
	lstrcpy(this->lname, L"-");
	lstrcpy(this->mname, L"-");
	lstrcpy(this->group, L"-");
}

Student::~Student()
{
}

Student::Student(TCHAR *fname, TCHAR *lname, TCHAR *mname, TCHAR *group)
{
	this->static_id++;

	this->id = this->static_id;
	lstrcpy(this->fname, fname);
	lstrcpy(this->lname, lname);
	lstrcpy(this->mname, mname);
	lstrcpy(this->group, group);
}