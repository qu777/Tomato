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
	cout << "********ѧ���ɼ�����ϵͳ********" << endl;
	cout << "******��ѡ������Ҫ�Ĳ���******" << endl;
	cout << "******0.�˳�******" << endl;
	cout << "******1.���******" << endl;
	cout << "******2.��ѯ******" << endl;
	cout << "******3.ɾ��******" << endl;
	cout << "******4.��ʾ******" << endl;
}


void chaoz::Time()    //�ж�
{
	clock_t stare, end;
	stare = clock();
	end = clock();
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(6);
	cout << "ʱ���ǣ�" << double((end - stare) / CLOCKS_PER_SEC) << endl;
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
		cout << "�������룿��y/n��" << endl;
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
			cout << "ɾ���ɹ���";
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
	cout << "��������Ҫ��ѯ�ı�ţ�";
	cin >> number;
	set<person>::iterator q = ppp.begin();
	while (q != ppp.end())                          //�˴��е�����
	{
		if (q->Getid() == number)
			break;
		q++;
	}
	if (q != ppp.end())
		Printone(q);
	else
		cout << "û�������" << endl;

}


void chaoz::Readfile()
{
	ifstream in("C:\\Users\\liu77\\Desktop\\�ļ�\\1.txt");
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
	ofstream out("C:\\Users\\liu77\\Desktop\\�ļ�\\1.txt", ios_base::app);
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