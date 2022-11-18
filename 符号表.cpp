#include"ɨ����.h"
void Translate::Var_Statement(Symbol_Table* T, Token_Code code)
{
	this->state.push(code);
	//cout << "��������Ԫ�ظ���" << state.size() << endl;
	return;
}
void Translate::In_TableF(Symbol_Table* T, Token_Code code)		//������ʶ��
{
	Activity_Record* A = NULL;
	if (T->A_R.size())											//��ǰ����
	{
		A = new Activity_Record(T->A_R.top()->level+1,code,T->A_R.top()->the_display,T->Activity.back());									//ջ�����¼,
	}
	else
	{								//��һ������
		A = new Activity_Record(code);	//��κ�Ϊ1
	}
	T->Activity.push_back(A);
	T->A_R.push(A);											//���¼ѹջ
	I_Table* it = T->I_List[code.code-1].second;			//��д�������ű�
	it->other = new Cat_Table('F');							//������
	it->cat = 'F';
	it->type = make_pair(' ',T->Activity.size());
	Cat_Table* ft = (it->other);	//����ת��Ϊ������
	ft->paralist = new vector<I_Table*>;

	ft->ptr.first = A->level;								//������κ�
	ft->ptr.second = 0;// *A->K_var.back().second.low;			//���ű��Ӧ��д,�ڴ�֮ǰ�����˻��¼
}
void Translate::In_TableV(Symbol_Table* T,Token_Code code)		//������ʶ����������
{

	while (!this->state.empty())
	{
		Token_Code var = this->state.front();					//����Ԫ��
		this->state.pop();
		//cout << "var: " << var.type << " " << var.code << endl;
		//cout << T->I_List.size();
		Activity_Record* A = T->A_R.top();						//ջ�����¼,
		I_Table* it = T->I_List[var.code-1].second;				//����Ԫ�صı�ʶ����
		if (it->other->ptr.first)
		{
			cout << T->I_List[var.code - 1].first;
			cout << "�ض���" << endl;
			exit(-1);					
		}
		int length = 0;
		if (code.type == 'K')
		{
			switch (code.code)
			{
			case 3:length = 2; break;
			case 4:length = 4; break;
			case 5:length = 1; break;
			}
			it->type = make_pair(T->K_List[code.code-1].first.front(),0);
		}
		else
		{
			length = T->I_List[code.code-1].second->other->length;	//�ṹ�����
			it->type = T->I_List[code.code-1].second->type;
		}
		it->cat = "V";
		it->other = new Cat_Table();
		it->other->ptr.first = A->level;						//ջ�����¼��κ�
		it->other->ptr.second = A->voff;		//���ű��Ӧ��д
		A->InsertV(var, length);										//
		T->I_List[A->token_code.code - 1].second->other->paralist->push_back(it);
	}
	return;
	//ע�����ﻹ��Ҫ�ӻ��¼������
}
void Translate::Rec_Struct(Symbol_Table* T, Token_Code code)		//����ṹ��
{
	this->Token.push(code);												//�ṹ��tokenѹջ
	I_Table* it = T->I_List[code.code-1].second;
	it->other = new Cat_Table();
	it->cat = 'T';
	T->Type_List.push_back(make_pair(it->name, new Struct_Table()));	//�����ṹ���
	it->type = make_pair('t', T->Type_List.size());					//���Ͷ���
	return;
}
void Translate::In_TableT(Symbol_Table* T, Token_Code code)
{
	this->Token.pop();
	I_Table* it = T->I_List[code.code-1].second;		//�ṹ���б�
	
	it->other->length = T->Type_List[it->type.second - 1].second->length;			//���ȸ���	
	it->type = make_pair('T', T->Type_List.size());
	return;
}
void Translate::In_TableN(Symbol_Table* T, Token_Code code)		//������д
{
	while (!this->state.empty())
	{
		Token_Code var = this->state.front();
		this->state.pop();
		I_Table* it = T->I_List[var.code-1].second;					//�ڱ�ʶ������
		it->other = new Cat_Table();
		Struct_Table* tt = T->Type_List[T->I_List[this->Token.top().code-1].second->type.second-1].second;				//�ڽṹ���ڵ�������
		Domain dom(it);
		if (!tt->Domain_List.empty())
			dom.ptr.low = tt->Domain_List.back().ptr.length;
		else
			dom.ptr.low = 0;
		switch (code.code)
		{
		case 11:dom.ptr.high = dom.ptr.low + 4; it->other->length = 4; tt->length += 4; it->type = make_pair('C', 0); break;
		case 5:dom.ptr.high = dom.ptr.low + 1; it->other->length = 1; tt->length += 1; it->type = make_pair('c', 0); break;
		case 4:dom.ptr.high = dom.ptr.low + 4; it->other->length = 4; tt->length += 4; it->type = make_pair('r', 0); break;//��������ʶ������ʶ���ṹ���Ӧ����++
		case 3:dom.ptr.high = dom.ptr.low + 2; it->other->length = 2; tt->length += 2; it->type = make_pair('i', 0); break;
		}
		tt->Domain_List.push_back(dom);
		it->cat ="D";
	}
	return;
}
void Translate::In_TableC(Symbol_Table* T, Token_Code code)
{
	while (!this->state.empty())
	{

		Token_Code var = this->state.front();
		this->state.pop();
		I_Table* it = T->I_List[var.code - 1].second;					//�ڱ�ʶ������
		it->other = new Cat_Table();
		it->other->con_val = T->C_List[code.code-1].first;				//������
		it->other->length = 4;
		it->type = make_pair('r',0);
		it->cat = "const";
	}

	return;
}
void Translate::In_TableP(Symbol_Table* T, Token_Code code,int type)	//�����б���д
{
	while (!this->state.empty())
	{
		Token_Code var = this->state.front();					//����Ԫ��
		this->state.pop();
		//cout << "var: " << var.type << " " << var.code << endl;
		//cout << T->I_List.size();
		Activity_Record* A = T->A_R.top();						//ջ�����¼,
		I_Table* it = T->I_List[var.code - 1].second;				//����Ԫ�صı�ʶ����
		Cat_Table * ft = T->I_List[A->token_code.code - 1].second->other;
		int length = 0;
		if (it->other->ptr.first)
		{
			cout << T->I_List[var.code - 1].first;
			cout << "�ض���" << endl;
			exit(-1);
		}
		if (type)			//����
			it->cat = "VF";
		else
			it->cat = "VN";//�����β�
		if (it->cat == "VN")
		{
			length = 2;
		}
		if (code.type == 'K')
		{
			switch (code.code)
			{
			case 3:length = 2; break;
			case 4:length = 4; break;
			case 5:length = 1; break;
			}
			it->type = make_pair(T->K_List[code.code - 1].first.front() , 0);
		}
		else
		{
			length = T->I_List[code.code - 1].second->other->length;	//�ṹ�����
			it->type = T->I_List[code.code - 1].second->type;
		}
		//cout << A->token_code.code << endl;
		it->other = new Cat_Table();
		it->other->ptr.first = A->level;						//ջ�����¼��κ�
		it->other->ptr.second = A->poff;
		it->other->length = length;
		ft->num++;
		A->InsertP(var, length);		
		A->prama_num++;						//��������
		
		
		ft->paralist->push_back(it);
		ft->parameter++;
	}
	return;
}
string Symbol_Table::FindVal(Token_Code code)
{
	string tar;
	switch (code.type)
	{
	case 'C':tar = this->C_List[code.code - 1].first; break;
	}
	//cout << tar << endl;
	return tar;
}