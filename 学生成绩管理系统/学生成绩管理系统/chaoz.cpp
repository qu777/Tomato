#include"stdafx.h"
#include"chaoz.h"
#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<ctime>
using namespace std;

chaoz::chaoz()
{
	Readfile();
}

void chaoz::Display()
{
	cout << "********学生成绩管理系统********" << endl;
	cout << "******请选择您需要的操作******" << endl;
	cout << "******0.退出******" << endl;
	cout << "******1.添加******" << endl;
	cout << "******2.查询******" << endl;
	cout << "******3.删除******" << endl;
	cout << "******4.显示******" << endl;
}


void chaoz::Time()    //有毒
{
	clock_t stare, end;
	stare = clock();
	end = clock();
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(6);
	cout << "时间是：" << double((end - stare) / CLOCKS_PER_SEC) << endl;
}


void chaoz::Run()
{
	int a;
	do
	{
		Display();
		cout << "please input your choice.";
		cin >> a;
		switch (a)
		{
		case 0:
			exit(0);
		case 1:
			Insert();
			break;
		case 2:
			Search();
			break;
		case 3:
			Delete();
			break;
		case 4:
			Output();
			break;
		}
	} while (a);
	Save();
}


void chaoz::Output()
{
	set<person>::iterator p = ppp.begin();
	while (p != ppp.end())
	{
		Printone(p);
		p++;
	}
}


void chaoz::Printone(set<person>::iterator p)
{
	cout << p->Getname() << " " << p->Getid() << " " << p->Getage() << " " << p->Getgrade() << " " << p->Getsex() << " " << p->Getscore() << endl;
}


void chaoz::Insert()
{
	char ch;
	do
	{
		cout << "please input your name:" << endl;
		string a;
		cin >> a;
		cout << "please input your id:" << endl;
		int b;
		cin >> b;
		cout << "please input your age:" << endl;
		int c;
		cin >> c;
		cout << "please input your grade:" << endl;
		int d;
		cin >> d;
		cout << "please input your sex(m/f):" << endl;
		char e;
		cin >> e;;
		cout << "please input your score:" << endl;
		int f;
		cin >> f;
		person g(a, b, c, d, e, f);
		ppp.insert(g);
		cout << "继续输入？（y/n）" << endl;
		cin >> ch;
	} while (ch != 'n');
}


void chaoz::Delete()
{
	cout << "please input your need to delete id:";
	int a;
	cin >> a;
	set<person>::iterator p = ppp.begin();
	while (p != ppp.end())
	{
		if (p->Getid() == a)
		{
			ppp.erase(p);
			cout << "删除成功！";
			return;
		}
		else
			p++;
	}
	return;
}


void chaoz::Search()
{
	int number;
	cout << "请输入你要查询的编号：";
	cin >> number;
	set<person>::iterator q = ppp.begin();
	while (q != ppp.end())                          //此处有点玄妙
	{
		if (q->Getid() == number)
			break;
		q++;
	}
	if (q != ppp.end())
		Printone(q);
	else
		cout << "没有这个人" << endl;

}


void chaoz::Readfile()
{
	ifstream in("C:\\Users\\liu77\\Desktop\\文件\\1.txt");
	if (!in)
	{
		cout << "cannot open the file.";
		return;
	}
	string name;
	long id;
	int age;
	int grade;
	char sex;
	int score;
	set<person>::iterator p = ppp.begin();
	in >> name >> id >> age >> grade >> sex >> score;
	while (!in.eof())
	{
		person ob(name, id, age, grade, sex, score);
		ppp.insert(ob);
		in >> name >> id >> age >> grade >> sex >> score;
	}
	in.close();
	return;
}


void chaoz::Save()
{
	ofstream out("C:\\Users\\liu77\\Desktop\\文件\\1.txt", ios_base::app);
	if (!out)
	{
		cout << "can not open file.";
		return;
	}
	set<person>::iterator p = ppp.begin();
	while (p != ppp.end())
	{
		out << p->Getname() << " " << p->Getid() << " " << p->Getage() << " " << p->Getgrade() << " " << p->Getsex() << " " << p->Getscore();
	}
	out.close();
	return;
}