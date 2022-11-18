#pragma once
#include"符号表.h"
class Activity_Record
{
public:
	Activity_Record() { return; }
	Activity_Record(Token_Code code)				//最外层互动记录构造
	{
		this->old_sp = 0;
		this->return_ptr = old_sp + 1;
		this->display = 0;
		this->prama_num = 0;
		this->the_display.push_back(0);
		this->voff = 5;
		this->poff = 4;
		this->top = voff - 1;
		this->token_code = code;
		this->level = 1;
	}
	Activity_Record(int level,Token_Code token, vector<int> the_display,Activity_Record * back)//新活动记录构造
	{
		this->old_sp = back->top + 1;
		this->return_ptr = old_sp + 1;
		this->display = back->old_sp+back->prama_num + 4;	
		this->prama_num = 0;				//形参个数
		this->the_display = the_display;
		this->the_display.push_back(old_sp);
		this->poff = 4;
		this->voff = 4 + this->the_display.size();
		this->top = voff-1;						//暂时只考虑old_sp,return_ptr,display,the_display
		this->token_code = token;			//该函数的token
		this->level = level;		
	}

	int old_sp;							//入口地址
	int return_ptr;						//返回地址
	int level;							//层次号
	int prama_num;						//参数个数
	int voff;							//变量首地址
	int poff;							//形参首地址
	Token_Code token_code;							//该函数的Token
	vector<pair<Token_Code, Offset>> prama;			//参数
	vector<int> the_display;						//全局display信息
	int display;									//display信息
	vector<pair<Token_Code,Offset>> K_var;			//局部变量，以顺序表实现
	int top;										//函数顶
	void InsertV(Token_Code,int);					//插入变量
	void InsertP(Token_Code,int);					//插入参数
	
	
};

class Symbol_Table
{
public:
	//friend In_Table;
	int error;									//错误类型码
	Symbol_Table();								//初始化
	vector<pair<string, int>>K_List;			//关键词表
	vector<pair<string, int>>P_List;			//界符表
	vector<pair<string, int>>C_List;			//常数表
	vector<pair<string, I_Table*>>I_List;			//变量表
	vector<pair<string, int>>S_List;		//字符串表
	vector<pair<string,Struct_Table*>>Type_List;//类型表
	queue<Token_Code>Token;						//token序列，以队列实现
	stack<Activity_Record*> A_R;				//函数嵌套分析栈
	vector<Activity_Record*> Activity;			//活动记录顺序表

	int t_code;						//临时变量编码
	bool Is_Word(char);				//判断是否为字母
	bool Is_Num(char);				//判断是否为数字
	bool Is_P(char);				//判断是否为界符
	void Table_Main();				//主流程
	void Scan(string);				//扫描pascal文本
	bool SearchV(Token_Code);		//查询Token
	void Print();					//打印符号表
	void ReFun();					//重申函数嵌套信息
	string FindVal(Token_Code);		//查询Token对应名	
};
class Translate				//翻译制导
{
public:
	stack<Token_Code> Token;						//四元式分析栈
	deque<Quartion*> quartion;						//四元式队列
	//stack<Token_Code>equ;
	queue<Token_Code>state;							//变量声明队列


	void Get_Quartion(Symbol_Table*, Token_Code );	//四元运算四元式
	void Get_Quartion_Equ();						//赋值四元式
	void Get_Quartion_Fun(Token_Code fun);			//函数声明四元式
	void Get_Quartion_Fun_End(Token_Code fun);		//函数结束符
	void Get_Quartion_Trans(Symbol_Table*, Token_Code,Token_Code);//参数传递四元式
	void Get_Quartion_CalFfun( Token_Code);		  //函数跳转四元式
	void Get_Quartion_Start();					  //程序入口四元式
	void Push_Factor(Token_Code);				  //四元式因子压栈
	void Var_Statement(Symbol_Table*, Token_Code);//变量声明
	void In_TableV(Symbol_Table*, Token_Code);		  //变量类型填表
	void In_TableF(Symbol_Table*, Token_Code);	  //函数填表
	void Rec_Struct(Symbol_Table*, Token_Code);	  //结构体声明
	void In_TableT(Symbol_Table*, Token_Code);	  //结构体类型填表
	void In_TableN(Symbol_Table*, Token_Code);	  //域名类型填表
	void In_TableC(Symbol_Table*, Token_Code);	  //常量类型填表.
	void In_TableP(Symbol_Table*, Token_Code,int);	  //参数列表填表
	
};