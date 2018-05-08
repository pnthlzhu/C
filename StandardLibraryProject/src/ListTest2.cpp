/*
 * ListTest2.cpp
 *
 *  Created on: May 8, 2018
 *      Author: hlzhu
 */

#include <string.h>
#include <string>
#include <list>
#include <iostream>

using namespace std;

typedef struct stu
{
	char szName[20];
	int iAge;

	bool operator <(struct stu &s)
	{
		return strcmp(szName, s.szName) == 0 ? (iAge < s.iAge) : strcmp(szName, s.szName) < 0;
	}
} Student;

int main()
{
	list<Student> stuList;
	list<Student>::iterator stuListIterator;

	Student stu1 = {"pnt", 10};
	Student stu2 = {"psh", 20};
	Student stu3 = {"pfu", 30};
	Student stu4 = {"psh", 40};

	stuList.push_back(stu1);
	stuList.push_back(stu2);
	stuList.push_back(stu3);
	stuList.push_back(stu4);

	for (stuListIterator = stuList.begin();stuListIterator != stuList.end();stuListIterator++)
	{
		cout<<"name is "<<((Student)*stuListIterator).szName<<", age is "<<((Student)*stuListIterator).iAge<<endl;
	}

	stuList.sort();

	cout<<"after sort..."<<endl;

	for (stuListIterator = stuList.begin();stuListIterator != stuList.end();stuListIterator++)
	{
		cout<<"name is "<<((Student)*stuListIterator).szName<<", age is "<<((Student)*stuListIterator).iAge<<endl;
	}

	return 0;
}
