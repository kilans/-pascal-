#include"ɨ����.h"
void Activity_Record::InsertV(Token_Code var,int ptr)	//�������¼��������
{
	
	Offset offset(this->voff, this->voff + ptr-1);
	//cout << "voff=" << this->voff << endl;
	this->voff += ptr;
	this->top += ptr;
	
	this->K_var.push_back(make_pair(var,offset));
	//cout << "��ʱ������";
	//cout << this->K_var.back().first.type << this->K_var.back().first.code << "  " << this->K_var.back().second.low << endl;

	return;
}
void Activity_Record::InsertP(Token_Code var, int ptr)	//������β��б����
{
	//cout << "poff=" << poff << endl;
	Offset offset(this->poff, this->poff + ptr-1);
	this->poff += ptr;
	this->voff += ptr;
	this->top += ptr;
	
	this->prama.push_back(make_pair(var, offset));
	//cout << "�����б�";
	//cout << this->prama.back().first.type << this->prama.back().first.code << "  " << this->prama.back().second.low <<" "<< this->prama.back().second.high << endl;
	return;
}
bool Symbol_Table::SearchV(Token_Code token)
{
	if (find_if(this->I_List.begin(), this->I_List.end(), [token](pair<string, I_Table*> k_var) {return k_var.second->code == token.code; }) != this->I_List.end())
		return 1;
	else
		return 0;
}
void Symbol_Table::ReFun()
{
	Activity_Record* A = NULL;
	for (int i = 1; i < this->Activity.size(); i++)
	{
		A = this->Activity[i];
		A->old_sp = this->Activity[i - 1]->top + 1;
		A->return_ptr = A->old_sp + 1;
		A->display = this->Activity[i - 1]->old_sp + this->Activity[i - 1]->poff;
		if (A->level - 1 == this->Activity[i - 1]->level)		//˵����Ƕ��
		{	
			A->the_display = this->Activity[i - 1]->the_display;
			A->the_display.push_back(A->old_sp);
		}
		else
		{
			for (i; i >=0; i--)
			{
				if ((A->level - 1 == this->Activity[i - 1]->level))		//����Ƕ����Ƕ��
				{
					A->the_display = this->Activity[i - 1]->the_display;
					A->the_display.push_back(A->old_sp);
				}
			}
		}
	}

}