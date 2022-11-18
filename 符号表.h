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
class Token_Code			//Token����
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
	char type;	//����
	int code;	//����
};
class Quartion		//��Ԫʽ
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
	
	string one;			//��һԪ
	Token_Code two;		//�ڶ�Ԫ
	Token_Code three;	//����Ԫ
	Token_Code four;	//����Ԫ
};
class Offset			//��ַ
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
	int low;	//��ַ��ʼ
	int high;	//��ַĩ
	int length;	//����
};
class Cat_Table					//�������͵ı������ָ��ı�
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
	char type;				//����
	pair<int, int> ptr;		//��κ���ƫ�Ƶ�ַ
	int length;				//����
	string con_val;			//����ֵ
	int parameter;				//��������
	int enter;					//��ڵ�ַ
	int num;					//�������
	vector< I_Table*>* paralist;		//�����б�
};
class I_Table						//��ʶ������
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
	string name;					//����
	pair<char,int> type;			//����
	string cat;						//����
	int code;						//����
	bool yn;	//��Ծ��Ϣ
	Cat_Table* other;				//������Ϣ
	bool temp;						//�Ƿ���ʱ����
};

class Domain						//������
{
public:
	Domain(I_Table* T)
	{
		this->name = T->name;
		this->type = T->type;
	}
	string name;					//����
	pair<string,int> type;			//����
	Offset ptr;						//��ַ�а����˳���
};
class Struct_Table
{
public:
	Struct_Table()
	{
		this->length = 0;
	}
	vector<Domain> Domain_List;					//������
	string name;								//����
	int length;									//�ṹ�峤��
};

