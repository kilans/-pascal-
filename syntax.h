#pragma once
#include"扫描器.h"
class  syntax               //翻译文法类
{
public:
    Token_Code t;           //当前Token
    Translate *trans;       //语义动作集合
    int state;  //变量定义状态机   
     //0:变量定义态，1:常量声明态，2:域名声明态 ,3:参数列表定义态 4.字符串声明，5:常量重定义
    queue<int> error;  //错误类型
    // 2.声明语句对象错误 3:未声明变量 4:声明对象类型错误
    int fstate;             //函数声明状态
   
    syntax(Symbol_Table*);  //初始化
    void Main(Symbol_Table*);   //主流程
    void nexttoken(Symbol_Table*);//读入下一个token
    void program(Symbol_Table*);//主程序
    void contipro(Symbol_Table*);//连续函数声明
    void pralist(Symbol_Table*);    //函数传参
    void subprogram(Symbol_Table*);//除去program的子程序
    void conststatement(Symbol_Table*);//常量声明
    void typestatement(Symbol_Table*);//类型声明区
    void sentencecom(Symbol_Table*);//以begin开始,end结束的语句区
    void varstatement(Symbol_Table*);//变量声明区
    void fieldid(Symbol_Table*);//域名表，即结构体内部元素
    void varid(Symbol_Table*);//变量表
    void vartype(Symbol_Table*);//变量，暂时只有char,integer,real三种
    void varstatementsub(Symbol_Table*);//变量声明的花括号
    void sentences(Symbol_Table*);//语句合集，位于begin,end间的语句
    void value(Symbol_Table*);//赋值语句
    void cauculatesub1(Symbol_Table*);//算数表达式中加减
    void cauculatesub2(Symbol_Table*);//算数表达式中乘除
    void cauculatesub3(Symbol_Table*);//算术表达式基本元素判断
    void Func(Symbol_Table*, Token_Code);   //函数声明
    void Error(Symbol_Table* T);    //错误处理
    void Print(Symbol_Table* T);    //打印符号表
    
}; 
