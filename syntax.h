#pragma once
#include"ɨ����.h"
class  syntax               //�����ķ���
{
public:
    Token_Code t;           //��ǰToken
    Translate *trans;       //���嶯������
    int state;  //��������״̬��   
     //0:��������̬��1:��������̬��2:��������̬ ,3:�����б���̬ 4.�ַ���������5:�����ض���
    queue<int> error;  //��������
    // 2.������������� 3:δ�������� 4:�����������ʹ���
    int fstate;             //��������״̬
   
    syntax(Symbol_Table*);  //��ʼ��
    void Main(Symbol_Table*);   //������
    void nexttoken(Symbol_Table*);//������һ��token
    void program(Symbol_Table*);//������
    void contipro(Symbol_Table*);//������������
    void pralist(Symbol_Table*);    //��������
    void subprogram(Symbol_Table*);//��ȥprogram���ӳ���
    void conststatement(Symbol_Table*);//��������
    void typestatement(Symbol_Table*);//����������
    void sentencecom(Symbol_Table*);//��begin��ʼ,end�����������
    void varstatement(Symbol_Table*);//����������
    void fieldid(Symbol_Table*);//���������ṹ���ڲ�Ԫ��
    void varid(Symbol_Table*);//������
    void vartype(Symbol_Table*);//��������ʱֻ��char,integer,real����
    void varstatementsub(Symbol_Table*);//���������Ļ�����
    void sentences(Symbol_Table*);//���ϼ���λ��begin,end������
    void value(Symbol_Table*);//��ֵ���
    void cauculatesub1(Symbol_Table*);//�������ʽ�мӼ�
    void cauculatesub2(Symbol_Table*);//�������ʽ�г˳�
    void cauculatesub3(Symbol_Table*);//�������ʽ����Ԫ���ж�
    void Func(Symbol_Table*, Token_Code);   //��������
    void Error(Symbol_Table* T);    //������
    void Print(Symbol_Table* T);    //��ӡ���ű�
    
}; 
