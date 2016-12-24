#ifndef _CHAOZ
#define _CHAOZ

#include"person.h"
#include<set>

class chaoz
{
protected:
	set<person> ppp;
public:
	chaoz();
	void Display();
	void Run();
	void Output();
	void Printone(set<person>::iterator p);
	void Insert();
	void Delete();
	void Readfile();
	void Search();
	void Save();
	void Time();
};
#endif