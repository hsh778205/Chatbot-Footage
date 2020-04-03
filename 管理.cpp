#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<map>
#include<set>
#include<queue>
#include<sstream>
#include<fstream>
#include<vector>
#define IL inline
#define re register
#define LL long long
using namespace std;

const char stop='=';

string now_name;

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

bool judge()
{
	string t;
	cin>>t;
	return t=="y"||t=="yes"; 
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
	for(unsigned int i=0;i<lib.size();i++)
	{
		cout<<i+100000<<"\t"<<lib[i].a<<endl<<"\t"<<lib[i].b<<endl<<endl;
	}
} 

void ready()
{
	ofstream rout("C:\\Users\\USER\\Downloads\\Compressed\\CQA-tuling\\酷Q Air\\词库\\now.wds",ios::out);
}

vector<string>table;
int turn(string str){
	for(unsigned int i=0;i<table.size();i++) if(table[i]==str) return i;
	return -1;
}

vector<string>stack;
void dfs_non_empty(string,unsigned int);
void dfs_empty(string str,unsigned int post)
{
	if(post==str.size()) return;
	if(str[post]==' '||str[post]=='\t') dfs_empty(str,post+1);
	else{
		string t;
		t.push_back(str[post]);
		stack.push_back(t);
		dfs_non_empty(str,post+1);
	}
}

void dfs_non_empty(string str,unsigned int post)
{
	if(post==str.size()) return;
	if(str[post]!=' '&&str[post]!='\t'){
		stack[stack.size()-1].push_back(str[post]);
		dfs_non_empty(str,post+1);
	}
	else{
		dfs_empty(str,post+1);
	}
} 

string sep(string p,unsigned int num){
	stack.clear();
	dfs_empty(p,0);
	if(stack.size()<=num) return "EOF";
	return stack[num];
}

int main()
{
	string str;
	table={"help","load","open","cls","add","show","ready","save"};
	while(true){
		cout<<"User:";
		getline(cin,str);
		if(str==""){
			cout<<"\b\b\b\b\b";
			continue;
		}
		if(sep(str,0)=="EOF") continue;
		switch(turn(sep(str,0))){
			case -1:{
				cout<<"Can't understand that\""<<str<<"\"\nYou can input \"help\" to check order\n";
				break;
			}
			case 0:{
				for(unsigned int i=0;i<table.size();i++) cout<<table[i]<<"  ";
				cout<<"\n";
				break;
			}
			case 1:{
				now_name=sep(str,1);
				int res=read(sep(str,1));
				if(res==-1) cout<<"读取失败\n";
				else{
					cout<<"读取到了"<<res<<"条语句，是否展示？(y/n)";
					if(judge()) show();
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
			case 5:{
				show();
				break;
			} 
			case 6:{
				ready();
				break;
			}
		}
	}
	
	return 0;
}

