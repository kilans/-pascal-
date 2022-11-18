#pragma once
#include"扫描器.h"
#include<fstream>
class Fun_Lau
{
public:
	Fun_Lau(Symbol_Table* T, deque<Quartion*>*);		//初始化
	ofstream* file;					//目标文件
	Quartion* funq;					//当前分析四元式
	Activity_Record* nowf;			//活动记录信息
	Symbol_Table* Table;			//符号表
	deque<Quartion*> funque;		//四元式队列
	void Main();					//主流程
	void To_X8086();				//生成目标代码
	void Fun_State();				//函数声明目标代码
	void Call_Fun();				//函数跳转目标代码		
	void TransVal();				//形式参数传入目标代码
	void TransPtr();				//换名形参传入目标代码
	void Fun_End();					//函数结束，返回目标代码
	void Fun_Start();				//程序入口生成目标代码
	void ActivInfo();				//划分基本块，活跃信息填写
	void obj();						//运算目标代码

};
