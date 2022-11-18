#pragma once
#include<iostream>
#include<map>
#include<fstream>
#include<string>
#include<queue>
#include<algorithm>
#include<vector>
#include<list>
#include<stack>
using namespace std;
class Cat_Table;
class I_Table;
class Token_Code			//Token序列
{
public:
	Token_Code()
	{
		this->type = ' ';
		this->code = 0;
		return;
	}
	Token_Code(char type, int code)
	{

		this->code = code;
		this->type = type;
	}
	bool operator == (Token_Code k_var)
	{
		if (k_var.code == this->code && k_var.type == this->type)
			return 1;
		else
			return 0;
	}
	char type;	//类型
	int code;	//编码
};
class Quartion		//四元式
{
	friend ostream& operator<< (ostream& cout, Quartion Q);
public:
	Quartion() { return; } 
	Quartion(string A, Token_Code B, Token_Code C, Token_Code D)
	{
		this->one = A;
		this->two = B;
		this->three = C;
		this->four = D;
	}
	
	string one;			//第一元
	Token_Code two;		//第二元
	Token_Code three;	//第三元
	Token_Code four;	//第四元
};
class Offset			//地址
{
public:
	Offset()
	{
		this->high = 0;
		this->length = 0;
		this->low = 0;
	}
	Offset(int low, int high)
	{
		this->low = low;
		this->high = high;
		this->length = high - low + 1;
	}
	int low;	//地址起始
	int high;	//地址末
	int length;	//长度
};
class Cat_Table					//变量类型的表各种类指向的表
{
public:
	Cat_Table()
	{
		this->paralist = NULL;
		this->type = 'V';
		this->ptr = make_pair(0, 0);
	}
	Cat_Table(char type)
	{
		switch (type)
		{
		case 'F': {
			this->paralist = new vector<I_Table*>;
			this->ptr = make_pair(0, 0);
		}break;

		}
	}
	char type;				//类型
	pair<int, int> ptr;		//层次号与偏移地址
	int length;				//长度
	string con_val;			//常数值
	int parameter;				//参数个数
	int enter;					//入口地址
	int num;					//函数编号
	vector< I_Table*>* paralist;		//参数列表
};
class I_Table						//标识符表栏
{
public:
	I_Table() { return; }
	I_Table(int code,string name)
	{
		this->code = code;
		this->name = name;
		this->other = new Cat_Table;
		temp = 0;
		this->yn = 1;
	}
	string name;					//名字
	pair<char,int> type;			//类型
	string cat;						//种类
	int code;						//编码
	bool yn;	//活跃信息
	Cat_Table* other;				//其余信息
	bool temp;						//是否临时变量
};

class Domain						//域名类
{
public:
	Domain(I_Table* T)
	{
		this->name = T->name;
		this->type = T->type;
	}
	string name;					//名字
	pair<string,int> type;			//类型
	Offset ptr;						//地址中包含了长度
};
class Struct_Table
{
public:
	Struct_Table()
	{
		this->length = 0;
	}
	vector<Domain> Domain_List;					//域名表
	string name;								//名字
	int length;									//结构体长度
};

