#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<map>
#include<set>
#include<queue>
#include<conio.h>
#include<sstream>
#include<fstream>
#include<windows.h>
#include<vector>
#define IL inline
#define re register
#define LL long long
using namespace std;

const char stop='=';

struct sen{
	string a,b;
	void clear()
	{
		a.clear();
		b.clear();
	}
	friend istream & operator>> (istream &in,sen &obj);	
	friend ostream & operator<< (ostream &out,sen &obj);
};

vector<sen>lib;

istream & operator>> (istream &in,sen &obj)
{
	obj.clear();
	string a;
	getline(in,a);
	unsigned int div=a.size();
	for(unsigned int i=1;i<a.size();i++)
	{
		if(a[i]==stop&&a[i-1]<=160/*大于160的是中文前缀*/){
			div=i;
			break;
		}
	}
	for(unsigned int i=0;i<div;i++) obj.a.push_back(a[i]);
	for(unsigned int i=div+1;i<a.size();i++) obj.b.push_back(a[i]);
    return in;
}

ostream & operator<< (ostream &out,sen & obj)
{
	
	out<<obj.a<<stop<<obj.b;
    return out;
}

void gotoxy(int x, int y)
{
	COORD pos;
	pos.X =x;
	pos.Y =y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

int read(string name)
{
	ifstream fin(name.c_str(),ios::in);
	sen t;
	lib.clear();
	if(fin.peek()==EOF) return -1;
	while(fin.peek()!=EOF){
		fin>>t;
		lib.push_back(t);
	}
	return lib.size();
}

void show()
{
	
} 

void ready()
{
	ofstream rout("C:\\Users\\USER\\Downloads\\Compressed\\CQA-tuling\\酷Q Air\\词库\\now.wds",ios::out);
}

int find()
{
	
}

vector<string>table;
int turn(string str){
	for(unsigned int i=0;i<table.size();i++) if(table[i]==str) return i;
	return -1;
}

string sep(string p,int num){
	int j=0,post;
	string str;
	for(unsigned int i=1;i<p.size()&&j<num;i++)
	{
		if(p[i-1]!=' '&&p[i]==' ') j++,post=i;
	}
	while(p[post]==' '||p[post]=='\t') ++post;
	
	for(unsigned int i=post+1;i<p.size();i++)
	{
		if(p[i]!=' ') str.push_back(p[i]);
		else break;
	}
	return "EOF";
}

int main()
{
	string str;
	table={"help","load","open","cls","add","show","save"};
	while(true){
		cout<<"User:";
		getline(cin,str);
		switch(turn(sep(str,0))){
			case -1:{
				cout<<"Can't understand that\""<<str<<"\"    You can input \"help\" to check order\n";
				break;
			}
			case 0:{
				for(unsigned int i=0;i<table.size();i++) cout<<table[i]<<"  ";
				cout<<"\n";
				break;
			}
			case 1:{
				int res=read(sep(str,1));
				if(res==-1) cout<<"读取失败\n";
				else{
					cout<<"读取到了"<<res<<"条语句，是否展示？(y/n)";
					if(getch()=='y') show();
				}
				break;
			}
			case 3:{
				system("cls");
				break;
			}
			case 4:{
				sen now;
				if(sep(str,1)!="EOF"){
					int post=0;
					for(unsigned int i=0;i<str.size();i++) if(str[i]==' '){post=i;break;}
					while(str[post]==' ') ++post;
					for(unsigned int i=post;i<str.size();i++){
						if(str[i]==stop){
							post=i+1;
							break;
						}
						now.a.push_back(str[i]);
					}
					for(unsigned int i=post;i<str.size();i++){
						now.b.push_back(str[i]);
					}
				}
				else{
					cout<<"请输入问句\n";
					getline(cin,now.a);
					cout<<"请输入答句\n";
					getline(cin,now.b);
				}
				lib.push_back(now);
				break;
			}
		}
	}
	
	return 0;
}

