#pragma once
#include<string>
using namespace std;


class person
{
protected:
	string name;
	long id;
	int age;
	int grade;
	char sex;
	long score;
public:
	person() { }
	person(string na, long i, int a, int g, char s, int sco);
	bool operator<(person ob) const;
	string Getname() const;
	long Getid() const;
	int Getage() const;
	int Getgrade() const;
	char Getsex() const;
	long Getscore() const;
};
