#pragma once
#include"ɨ����.h"
#include<fstream>
class Fun_Lau
{
public:
	Fun_Lau(Symbol_Table* T, deque<Quartion*>*);		//��ʼ��
	ofstream* file;					//Ŀ���ļ�
	Quartion* funq;					//��ǰ������Ԫʽ
	Activity_Record* nowf;			//���¼��Ϣ
	Symbol_Table* Table;			//���ű�
	deque<Quartion*> funque;		//��Ԫʽ����
	void Main();					//������
	void To_X8086();				//����Ŀ�����
	void Fun_State();				//��������Ŀ�����
	void Call_Fun();				//������תĿ�����		
	void TransVal();				//��ʽ��������Ŀ�����
	void TransPtr();				//�����βδ���Ŀ�����
	void Fun_End();					//��������������Ŀ�����
	void Fun_Start();				//�����������Ŀ�����
	void ActivInfo();				//���ֻ����飬��Ծ��Ϣ��д
	void obj();						//����Ŀ�����

};
