#include"ɨ����.h"
ostream&  operator<< (ostream& cout, Quartion Q) {  

	cout << Q.one << " ";
	if (Q.two.type != ' ')cout << Q.two.type << Q.two.code;
	cout<< " ";
	if (Q.three.type != ' ')cout << Q.three.type << Q.three.code;
	cout<< " ";
	if (Q.four.type != ' ')cout << Q.four.type << Q.four.code;
	return cout;
}
void Translate::Push_Factor(Token_Code token)
{
	this->Token.push(token);
	return;
}
void Translate::Get_Quartion(Symbol_Table* T, Token_Code cal)		//�������
{
	Token_Code token2=this->Token.top();
	this->Token.pop();
	Token_Code token1=this->Token.top();
	this->Token.pop();
	Activity_Record *A = T->A_R.top();
	string temp_code = "t" + to_string(++T->t_code);
	I_Table* t_table = new I_Table(T->I_List.size() + 1,temp_code);
	t_table->type = make_pair(T->I_List[token1.code - 1].second->type.first, 0);
	t_table->cat = "t";
	t_table->other = new Cat_Table();
	t_table->other->length = T->I_List[token1.code - 1].second->other->length;
	t_table->other->ptr.first = A->level;						//ջ�����¼��κ�
	t_table->other->ptr.second = A->voff;		//���ű��Ӧ��д

	T->I_List.push_back(make_pair(temp_code, t_table));							//����ű�
	t_table->temp = true;										//��ʱ����

	t_table->yn = false;

	Token_Code temp_k('I', T->I_List.size());
	//this->state.push(temp_k);								//����ʽִ����Ϻ���ִ������ж�
	this->Push_Factor(temp_k);								//����ջ
	
	A->InsertV(temp_k, t_table->other->length); 								//����¼
	
	Quartion* quar = new Quartion(T->P_List[cal.code-1].first, token1, token2, temp_k);		//������Ԫʽ
	//cout << *quar << endl;
	this->quartion.push_back(quar);
	return;
}
void Translate::Get_Quartion_Equ()
{
	Token_Code val = this->Token.top();
	this->Token.pop();
	Token_Code equ = this->Token.top();
	this->Token.pop();
	
	Quartion* quar = new Quartion(":=", val, Token_Code(), equ);
	//cout << *quar << endl;
	this->quartion.push_back(quar);
	return;
}
void Translate::Get_Quartion_Fun(Token_Code fun)		//����������Ԫʽ
{
	Quartion* quar = new Quartion("program", Token_Code(), Token_Code(), fun);
	//cout << *quar << endl;
	this->quartion.push_back(quar);
	return;
}
void Translate::Get_Quartion_Fun_End(Token_Code fun)		//����������Ԫʽ
{
	Quartion* quar = new Quartion("end", Token_Code(), Token_Code(), fun);
	//cout << *quar << endl;
	this->quartion.push_back(quar);
	return;
}
void Translate::Get_Quartion_Trans(Symbol_Table* T,  Token_Code pra ,Token_Code tar)
{
	Quartion* quar = NULL;
	if(T->I_List[tar.code-1].second->cat=="VF") 
		quar = new Quartion("transVal", pra, Token_Code(), tar);
	else
		quar = new Quartion("transPtr", pra, Token_Code(), tar);
	
	//cout << *quar << endl;
	//cout << T->I_List[tar.code - 1].second->cat ;
	this->quartion.push_back(quar);

	return;
}
void Translate::Get_Quartion_CalFfun( Token_Code fun)
{
	Quartion* quar = NULL;
	quar = new Quartion("call", Token_Code(), Token_Code(), fun);
	this->quartion.push_back(quar);

	return;
}
void Translate::Get_Quartion_Start()
{
	Quartion* quar = NULL;
	quar = new Quartion("start", Token_Code(), Token_Code(), Token_Code());
	this->quartion.push_back(quar);
	return;
}
