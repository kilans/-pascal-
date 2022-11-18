#include"函数语言.h"
void Fun_Lau::Main()
{
	this->To_X8086();
}
Fun_Lau::Fun_Lau(Symbol_Table* T,deque<Quartion*>* Q)
{
	this->Table = new Symbol_Table;
	this->Table = T;
	this->file = new ofstream();
	this->nowf = new Activity_Record();
	this->funque = *Q;
	return;
}
void Fun_Lau::To_X8086()
{
	system("pause");
	this->file->open("test.asm",ios::out);
	*file << "ASSUME SS:STACK" << endl;
	*file << "STACK SEGMENT STACK" << endl;
	*file << "DB 1024 DUP(0)" << endl;
	*file << "STACK ENDS" << endl;
	int count = 0;
	while (!this->funque.empty())
	{
		this->funq=this->funque.front();	
		
		
		if (funq->one == ":=" || funq->one == "*" || funq->one == "/" || funq->one == "+" || funq->one == "-")
		{
			this->ActivInfo();
			this->obj();
			
		}

		cout << *funq << endl;
		system("pause");
		if (funq->one == "program")
		{
			this->Fun_State();
		}
		else if (funq->one == "transPtr")
		{
			this->TransPtr();
		}
		else if (funq->one == "transVal")
		{
			this->TransVal();
		}
		else if (funq->one == "call")
		{
			this->Call_Fun();
		}
		else if (funq->one == "end")
		{
			
			this->Fun_End();
		}
		else if (funq->one == "start")
		{
			this->Fun_Start();
		}
		this->funque.pop_front();
	}
	return;
}
void Fun_Lau::Fun_State()
{

	this->nowf = Table->Activity[Table->I_List[funq->four.code - 1].second->type.second - 1];
	if (Table->I_List[funq->four.code - 1].second->code == 1)	//首层hanshu
	{
		*file << Table->I_List[funq->four.code - 1].second->name << " " << "SEGMENT" << endl;
	}
	else
	{
		*file << Table->I_List[funq->four.code - 1].second->name <<":" << endl;
	}
	*file << "old_sp " << "DB " << nowf->old_sp<< endl;
	*file << "return_ptr  " << "DB " << nowf->return_ptr << endl;
	*file << "display " << "DB " << nowf->display << endl;

	*file << "prama_num " << "DB " << nowf->prama_num << endl;
	*file << "prama_list:";
	for (vector<pair<Token_Code,Offset>>::iterator it = nowf->prama.begin(); it != nowf->prama.end(); it++)
	{
		*file <<Table->I_List[it->first.code-1].second->name << " "<<"DB "<< it->second.length<<" DUP(0)"<<" ";	//临时变量定义

	}
	*file << endl;
	*file << "the_display " <<"DB ";
	for (vector<int>::iterator it = nowf->the_display.begin(); it != nowf->the_display.end(); it++)
	{
		*file << * it << " ";	//全局display
	}
	*file << endl;
	*file << "V_List:" << endl;
	for (vector<pair<Token_Code, Offset>>::iterator it = nowf->K_var.begin(); it != nowf->K_var.end(); it++)
	{	
		*file << Table->I_List[it->first.code - 1].second->name << " DB " << it->second.length << " DUP(0)" << endl;	//临时变量定义
	}
	*file << endl;
	if (Table->I_List[funq->four.code - 1].second->code == 1)	//首层hanshu
	{
		*file << "ASSUME CS:"<< Table->I_List[funq->four.code - 1].second->name<<",DS:"<< Table->I_List[funq->four.code - 1].second->name << endl;
	}
	return;
}
void Fun_Lau::Call_Fun()
{
	this->nowf = this->Table->Activity[this->Table->I_List[this->funq->four.code - 1].second->type.second - 1];
	*file << "CALL" <<" "<< Table->I_List[funq->four.code - 1].second->name << endl;
	return;
}
void Fun_Lau::TransVal()
{
	string code;
	switch (Table->I_List[funq->four.code - 1].second->other->length)
	{
	case 1:code = "MOV AL,[" + to_string(Table->Activity[Table->I_List[this->funq->two.code - 1].second->other->ptr.first - 1]->old_sp +Table->I_List[this->funq->two.code-1].second->other->ptr.second); code +="]";
		code += "MOV [";code+= to_string(Table->Activity[Table->I_List[this->funq->four.code - 1].second->other->ptr.first - 1]->old_sp + Table->I_List[this->funq->four.code - 1].second->other->ptr.second); code += "],al"; break;
		
	case 2:code = "MOV AX,[" + to_string(Table->Activity[Table->I_List[this->funq->two.code - 1].second->other->ptr.first-1]->old_sp + Table->I_List[this->funq->two.code - 1].second->other->ptr.second); code += "]"; code += "\n";
		code += "MOV ["; code += to_string(Table->Activity[Table->I_List[this->funq->four.code - 1].second->other->ptr.first - 1]->old_sp + Table->I_List[this->funq->four.code - 1].second->other->ptr.second); code += "],ax"; break;
	case 4:code = "MOV AX,[" + to_string(Table->Activity[Table->I_List[this->funq->two.code - 1].second->other->ptr.first - 1]->old_sp + Table->I_List[this->funq->two.code - 1].second->other->ptr.second); code += "]"; code += "\n";
		code += "MOV ["; code += to_string(Table->Activity[Table->I_List[this->funq->four.code - 1].second->other->ptr.first - 1]->old_sp + Table->I_List[this->funq->four.code - 1].second->other->ptr.second); code += "],ax"; code += "\n";
		code = "MOV AX,[" + to_string(Table->Activity[Table->I_List[this->funq->two.code - 1].second->other->ptr.first - 1]->old_sp + Table->I_List[this->funq->two.code - 1].second->other->ptr.second); code += "+2"; code += "]"; code += "\n";
		code += "MOV ["; code += to_string(Table->Activity[Table->I_List[this->funq->four.code - 1].second->other->ptr.first - 1]->old_sp + Table->I_List[this->funq->four.code - 1].second->other->ptr.second); code += "+2"; code += "],ax"; code += "\n"; break;
	}
	*file << code << endl;
}
void Fun_Lau::TransPtr()
{
	string code;
	code = "MOV AX,";
	if (this->funq->two.type == 'I')
	{
		code += "[";
		code += to_string(Table->Activity[Table->I_List[this->funq->two.code - 1].second->other->ptr.first - 1]->old_sp + Table->I_List[this->funq->two.code - 1].second->other->ptr.second);
		code += "]";

	}
	else
		code += Table->FindVal(this->funq->two);
	code += "\n";
	code += "MOV ["; code += to_string(Table->Activity[Table->I_List[this->funq->four.code - 1].second->other->ptr.first - 1]->old_sp + Table->I_List[this->funq->four.code - 1].second->other->ptr.second); code += "],AX";
	*file << code << endl;
}
void Fun_Lau::Fun_End()
{
	if (Table->I_List[funq->four.code - 1].second->code == 1)
	{
		*file << "MOV AX,4C00H" << endl;
		*file << "INT 21H"<<endl;
		*file << Table->I_List[funq->four.code - 1].second->name << " ends" << endl;
		*file << "END START";
	}
	else
	{
		*file << "RET" << endl;
	}
	
	return;
}
void Fun_Lau::Fun_Start()
{
	*file << "START:" << endl;
}
void Fun_Lau::ActivInfo()
{
	Quartion* temp = NULL;
	stack<Quartion*> support;
	bool* YN = new bool[Table->I_List.size()];
	for (int i = 0; i < Table->I_List.size(); i++)
	{
		if (Table->I_List[i].second->temp == 1)         //临时表量不活跃
			YN[i] = 0;
		else
			YN[i] = 1;
	}
	int tag = this->funque.size();
	for (int i = 0; i < tag; i++)
	{
		temp = this->funque.front();
		//if (!(temp->one == "+" || temp->one == "/" || temp->one == "-" || temp->one == "*" || temp->one == ":="))
		//{
		//	cout << "push " << *temp << endl;
		//	this->funque.pop_front();
		//	support.push(temp);		
		//	continue;
		//}
		while (temp->one == "+" || temp->one == "/" || temp->one == "-" || temp->one == "*" || temp->one == ":=")
		{
			
			this->funque.pop_front();
			support.push(temp);
			temp = this->funque.front();
		}
		while (!support.empty())
		{
			temp = support.top();
			this->funque.push_front(support.top());
			//cout  << *temp << endl;
			if (temp->one == "+" || temp->one == "/" || temp->one == "-" || temp->one == "*" || temp->one == ":=")
			{
				if (temp->two.code != 0)
				{
					Table->I_List[temp->two.code - 1].second->yn = YN[temp->two.code - 1];
					YN[temp->two.code - 1] = 1;
					//cout << Table->I_List[temp->two.code - 1].second->yn << " ";
				}
				if (temp->three.code != 0)
				{
					Table->I_List[temp->three.code - 1].second->yn = YN[temp->three.code - 1];
					YN[temp->three.code - 1] = 1;
					//cout << Table->I_List[temp->three.code - 1].second->yn << " ";
				}
				if (temp->four.code != 0)
				{
					Table->I_List[temp->four.code - 1].second->yn = YN[temp->four.code - 1];
					YN[temp->four.code - 1] = 0;
					//cout << Table->I_List[temp->four.code - 1].second->yn << " ";
				}
				
			}
			
			//cout << endl;
			support.pop();
		}
		//system("pause");
		break;
	}
}