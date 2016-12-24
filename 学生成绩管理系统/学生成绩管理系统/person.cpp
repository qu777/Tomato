#include"stdafx.h"
#include"person.h"
string person::Getname() const
{
	return name;
}
long person::Getid() const
{
	return id;
}
int person::Getage() const
{
	return age;
}
int person::Getgrade() const
{
	return grade;
}
char person::Getsex() const
{
	return sex;
}
long person::Getscore() const
{
	return score;
}
person::person(string na, long i, int a, int g, char s, int sco)
{
	name = na;
	id = i;
	age = a;
	grade = g;
	sex = s;
	score = sco;

}
bool person::operator <(person ob) const
{
	if (id<ob.id)
		return true;
	else
		return false;
}