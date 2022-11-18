#pragma once
#include"���ű�.h"
class Activity_Record
{
public:
	Activity_Record() { return; }
	Activity_Record(Token_Code code)				//����㻥����¼����
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
	Activity_Record(int level,Token_Code token, vector<int> the_display,Activity_Record * back)//�»��¼����
	{
		this->old_sp = back->top + 1;
		this->return_ptr = old_sp + 1;
		this->display = back->old_sp+back->prama_num + 4;	
		this->prama_num = 0;				//�βθ���
		this->the_display = the_display;
		this->the_display.push_back(old_sp);
		this->poff = 4;
		this->voff = 4 + this->the_display.size();
		this->top = voff-1;						//��ʱֻ����old_sp,return_ptr,display,the_display
		this->token_code = token;			//�ú�����token
		this->level = level;		
	}

	int old_sp;							//��ڵ�ַ
	int return_ptr;						//���ص�ַ
	int level;							//��κ�
	int prama_num;						//��������
	int voff;							//�����׵�ַ
	int poff;							//�β��׵�ַ
	Token_Code token_code;							//�ú�����Token
	vector<pair<Token_Code, Offset>> prama;			//����
	vector<int> the_display;						//ȫ��display��Ϣ
	int display;									//display��Ϣ
	vector<pair<Token_Code,Offset>> K_var;			//�ֲ���������˳���ʵ��
	int top;										//������
	void InsertV(Token_Code,int);					//�������
	void InsertP(Token_Code,int);					//�������
	
	
};

class Symbol_Table
{
public:
	//friend In_Table;
	int error;									//����������
	Symbol_Table();								//��ʼ��
	vector<pair<string, int>>K_List;			//�ؼ��ʱ�
	vector<pair<string, int>>P_List;			//�����
	vector<pair<string, int>>C_List;			//������
	vector<pair<string, I_Table*>>I_List;			//������
	vector<pair<string, int>>S_List;		//�ַ�����
	vector<pair<string,Struct_Table*>>Type_List;//���ͱ�
	queue<Token_Code>Token;						//token���У��Զ���ʵ��
	stack<Activity_Record*> A_R;				//����Ƕ�׷���ջ
	vector<Activity_Record*> Activity;			//���¼˳���

	int t_code;						//��ʱ��������
	bool Is_Word(char);				//�ж��Ƿ�Ϊ��ĸ
	bool Is_Num(char);				//�ж��Ƿ�Ϊ����
	bool Is_P(char);				//�ж��Ƿ�Ϊ���
	void Table_Main();				//������
	void Scan(string);				//ɨ��pascal�ı�
	bool SearchV(Token_Code);		//��ѯToken
	void Print();					//��ӡ���ű�
	void ReFun();					//���꺯��Ƕ����Ϣ
	string FindVal(Token_Code);		//��ѯToken��Ӧ��	
};
class Translate				//�����Ƶ�
{
public:
	stack<Token_Code> Token;						//��Ԫʽ����ջ
	deque<Quartion*> quartion;						//��Ԫʽ����
	//stack<Token_Code>equ;
	queue<Token_Code>state;							//������������


	void Get_Quartion(Symbol_Table*, Token_Code );	//��Ԫ������Ԫʽ
	void Get_Quartion_Equ();						//��ֵ��Ԫʽ
	void Get_Quartion_Fun(Token_Code fun);			//����������Ԫʽ
	void Get_Quartion_Fun_End(Token_Code fun);		//����������
	void Get_Quartion_Trans(Symbol_Table*, Token_Code,Token_Code);//����������Ԫʽ
	void Get_Quartion_CalFfun( Token_Code);		  //������ת��Ԫʽ
	void Get_Quartion_Start();					  //���������Ԫʽ
	void Push_Factor(Token_Code);				  //��Ԫʽ����ѹջ
	void Var_Statement(Symbol_Table*, Token_Code);//��������
	void In_TableV(Symbol_Table*, Token_Code);		  //�����������
	void In_TableF(Symbol_Table*, Token_Code);	  //�������
	void Rec_Struct(Symbol_Table*, Token_Code);	  //�ṹ������
	void In_TableT(Symbol_Table*, Token_Code);	  //�ṹ���������
	void In_TableN(Symbol_Table*, Token_Code);	  //�����������
	void In_TableC(Symbol_Table*, Token_Code);	  //�����������.
	void In_TableP(Symbol_Table*, Token_Code,int);	  //�����б����
	
};