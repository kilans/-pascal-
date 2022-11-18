
#include"º¯ÊýÓïÑÔ.h"
string rdl = "0";
bool other_a = 1;
#define sec to_string(Table->I_List[(*funq).two.code - 1].second->other->ptr.second + Table->Activity[Table->I_List[(*funq).two.code - 1].second->other->ptr.first-1]->old_sp)
#define thi to_string(Table->I_List[(*funq).three.code - 1].second->other->ptr.second + Table->Activity[Table->I_List[(*funq).three.code - 1].second->other->ptr.first-1]->old_sp)
#define fou to_string(Table->I_List[(*funq).four.code - 1].second->other->ptr.second + Table->Activity[Table->I_List[(*funq).four.code - 1].second->other->ptr.first-1]->old_sp)


void Fun_Lau::obj()
{
	this->funq = this->funque.front();
	//Quartion (*funq) = *this->funque.front();
	/*Table->I_List[(*funq).two.code - 1].second->yn == 1;
	Table->I_List[*funq.three.code - 1].second->yn == 1;
	Table->I_List[*funq.four.code - 1].second->yn == 1;*/
	cout << *funq << endl;
	system("pause");
	
	int state = 1;
	if ((*funq).one == "+")
	{
		if (rdl == "0")
		{
			*file << "MOV" << " ";
			*file << "AX";
			*file << ",";
			if ((*funq).two.type != 'I')
				*file << Table->FindVal((*funq).two);
			else
			{
				*file << "[" << sec << "]";
			}
			*file << endl;

			*file << "ADD" << " "; 
			*file << "AX";
			*file << ",";
			if ((*funq).three.type != 'I')
				*file << Table->FindVal((*funq).three);
			else
			{
				*file << "[" << thi << "]";
			}
			*file << endl;
			state = 0;
		}
		else if ((*funq).two.type == 'I')
		{
			if (rdl == sec)
			{
				if (Table->I_List[(*funq).two.code - 1].second->yn == 1)
				{
					*file << "MOV" << " ";
					if ((*funq).two.type != 'I')
						*file << Table->FindVal((*funq).two);
					else
						*file << "[" << sec << "]";
					*file << ",";
					*file << "AX";
					*file << endl;
				}
				*file << "ADD" << " ";
				*file << "AX";
				*file << ",";
				if ((*funq).three.type != 'I')
					*file << Table->FindVal((*funq).three);
				else
					*file << "[" << thi << "]";
				*file << endl;
				state = 0;
			}

		}
		else if ((*funq).three.type == 'I' && !state)
		{
			if (rdl == thi)
			{
				if (Table->I_List[(*funq).three.code - 1].second->yn == 1)
				{
					*file << "MOV" << " ";
					if ((*funq).three.type != 'I')
						*file << Table->FindVal((*funq).three);
					else
						*file << "[" << thi << "]";
					*file << ",";
					*file << "AX";
					*file << endl;
				}
				*file << "ADD" << " ";
				*file << "AX";
				*file << ",";
				if ((*funq).two.type != 'I')
					*file << Table->FindVal((*funq).two);
				else
					*file << "[" << sec << "]";
				*file << endl;
				state = 0;
			}
		}
		if (state)
		{
			if (other_a == 1)
			{
				*file << "MOV" << " ";
				*file << "[" << rdl << "]";
				*file << ",";
				*file << "AX";
				*file << endl;
			}
			*file << "MOV" << " ";
			*file << "AX";
			*file << ",";
			if ((*funq).two.type != 'I') *file << Table->FindVal((*funq).two);
			else *file << "[" << sec << "]";

			*file << endl;
			*file << "ADD" << " ";
			*file << "AX";
			*file << ",";
			if ((*funq).three.type != 'I')
				*file << Table->FindVal((*funq).three);
			else
				*file << "[" << thi << "]";
			*file << endl;
		}
		rdl = fou;
		other_a = Table->I_List[(*funq).four.code - 1].second->yn;
	}
	else if ((*funq).one == "*")
	{
		if (rdl.compare("0"))
		{
			*file << "MOV" << " ";
			*file << "AX";
			*file << ",";
			if ((*funq).two.type != 'I') *file << Table->FindVal((*funq).two);
			else *file << "[" << sec << "]";
			*file << endl;
			*file << "MOV" << " ";
			*file << "DX";
			*file << ",";
			if ((*funq).three.type != 'I')
				*file << Table->FindVal((*funq).three);
			else
				*file << "[" << thi << "]";
			*file << endl;
			*file << "MUL" << " ";
			*file << "DX";
			*file << endl;
			state = 0;
		}
		else if ((*funq).two.type == 'I')
		{
			if (rdl == sec)
			{
				if (Table->I_List[(*funq).two.code - 1].second->yn == 1)
				{
					*file << "MOV" << " ";
					if ((*funq).two.type != 'I') *file << Table->FindVal((*funq).two);
					else *file << "[" << sec << "]";
					*file << ",";
					*file << "AX";
					*file << endl;
				}
				*file << "MOV" << " ";
				*file << "DX";
				*file << ",";
				if ((*funq).three.type != 'I')
					*file << Table->FindVal((*funq).three);
				else
					*file << "[" << thi << "]";
				*file << endl;
				*file << "MUL" << " ";
				*file << "DX";
				*file << endl;
				state = 0;
			}
		}
		else if ((*funq).three.type == 'I')
		{
			if (rdl == thi)
			{
				if (Table->I_List[(*funq).three.code - 1].second->yn == 1)
				{
					*file << "MOV" << " ";
					if ((*funq).three.type != 'I')
						*file << Table->FindVal((*funq).three);
					else
						*file << "[" << thi << "]";
					*file << ",";
					*file << "AX";
					*file << endl;
				}
				*file << "MOV" << " ";
				*file << "DX";
				*file << ",";
				if ((*funq).two.type != 'I') *file << Table->FindVal((*funq).two);
				else *file << "[" << sec << "]";
				*file << endl;
				*file << "MUL" << " ";
				*file << "DX";
				*file << endl;
				state = 0;
			}
		}
		if (state)
		{
			if (other_a == 1)//
			{
				*file << "MOV" << " ";
				*file << "[" << rdl << "]";
				*file << ",";
				*file << "AX";
				*file << endl;
			}
			*file << "MOV" << " ";
			*file << "AX";
			*file << ",";
			if ((*funq).two.type != 'I') *file << Table->FindVal((*funq).two);
			else *file << "[" << sec << "]";
			*file << endl;
			*file << "MOV" << " ";
			*file << "DX";
			*file << ",";
			if ((*funq).three.type != 'I')
				*file << Table->FindVal((*funq).three);
			else
				*file << "[" << thi << "]";
			*file << endl;
			*file << "MUL" << " ";
			*file << "DX";
			*file << endl;
		}
		rdl = fou;
		other_a = Table->I_List[(*funq).four.code - 1].second->yn;
	}
	else if ((*funq).one == "-")
	{
		if (rdl == "0")
		{
			*file << "MOV" << " ";
			*file << "AX";
			*file << ",";
			if ((*funq).two.type != 'I') *file << Table->FindVal((*funq).two);
			else *file << "[" << sec << "]";
			*file << endl;
			*file << "SUB" << " ";
			*file << "AX";
			*file << ",";
			if ((*funq).three.type != 'I')
				*file << Table->FindVal((*funq).three);
			else
				*file << "[" << thi << "]";
			*file << endl;
			state = 0;
		}
		else if ((*funq).two.type == 'I')
		{
			if (rdl == sec)
			{
				if (Table->I_List[(*funq).two.code - 1].second->yn == 1)
				{
					*file << "MOV" << " ";
					if ((*funq).two.type != 'I') *file << Table->FindVal((*funq).two);
					else *file << "[" << sec << "]";
					*file << ",";
					*file << "AX";
					*file << endl;
				}
				*file << "SUB" << " ";
				*file << "AX";
				*file << ",";
				if ((*funq).three.type != 'I')
					*file << Table->FindVal((*funq).three);
				else
					*file << "[" << thi << "]";
				*file << endl;
				state = 0;
			}
		}
		if (state)
		{
			if (other_a == 1)//
			{
				*file << "MOV" << " ";
				*file << "[" << rdl << "]";
				*file << ",";
				*file << "AX";
				*file << endl;
			}
			*file << "MOV" << " ";
			*file << "AX";
			*file << ",";
			if ((*funq).two.type != 'I') *file << Table->FindVal((*funq).two);
			else *file << "[" << sec << "]";
			*file << endl;
			*file << "SUB" << " ";
			*file << "AX";
			*file << ",";
			if ((*funq).three.type != 'I')
				*file << Table->FindVal((*funq).three);
			else
				*file << "[" << thi << "]";
			*file << endl;
		}
		rdl = fou;
		other_a = Table->I_List[(*funq).four.code - 1].second->yn;
	}
	else if ((*funq).one == "/")
	{
		*file << "XOR" << " ";
		*file << "DX";
		*file << ",";
		*file << "DX";
		*file << endl;
		if (rdl == "0")
		{
			*file << "MOV" << " ";
			*file << "AX";
			*file << ",";
			if ((*funq).two.type != 'I') *file << Table->FindVal((*funq).two);
			else *file << "[" << sec << "]";
			*file << endl;
			*file << "MOV" << " ";
			*file << "CX";
			*file << ",";
			if ((*funq).three.type != 'I')
				*file << Table->FindVal((*funq).three);
			else
				*file << "[" << thi << "]";
			*file << endl;
			*file << "DIV" << " ";
			*file << "CX";
			*file << endl;
			state = 0;
		}
		else if ((*funq).two.type == 'I')
		{
			if (rdl == sec)
			{
				if (Table->I_List[(*funq).two.code - 1].second->yn == 1)
				{
					*file << "MOV" << " ";
					if ((*funq).two.type != 'I') *file << Table->FindVal((*funq).two);
					else *file << "[" << sec << "]";
					*file << ",";
					*file << "AX";
					*file << endl;
				}
				*file << "MOV" << " ";
				*file << "CX";
				*file << ",";
				if ((*funq).three.type != 'I')
					*file << Table->FindVal((*funq).three);
				else
					*file << "[" << thi << "]";
				*file << endl;
				*file << "DIV" << " ";
				*file << "CX";
				*file << endl;
				state = 0;
			}
		}
		if (state)
		{
			if (other_a == 1)//
			{
				*file << "MOV" << " ";
				*file << "[" << rdl << "]";
				*file << ",";
				*file << "AX";
				*file << endl;
			}
			*file << "MOV" << " ";
			*file << "AX";
			*file << ",";
			if ((*funq).two.type != 'I') *file << Table->FindVal((*funq).two);
			else *file << "[" << sec << "]";
			*file << endl;
			*file << "MOV";
			*file << "CX";
			*file << ",";
			if ((*funq).three.type != 'I')
				*file << Table->FindVal((*funq).three);
			else
				*file << "[" << thi << "]";
			*file << endl;
			*file << "DIV" << " ";
			*file << "CX";
			*file << endl;
		}
		rdl = fou;
		other_a = Table->I_List[(*funq).four.code - 1].second->yn;
	}
	else if ((*funq).one == ":=")
	{
		if (rdl=="0")
		{
			*file << "MOV" << " ";
			*file << "AX";
			*file << ",";
			if ((*funq).two.type != 'I') *file << Table->FindVal((*funq).two);
			else *file << "[" << sec << "]";
			*file << endl;
			state = 0;
		}
		else if ((*funq).two.type == 'I')
		{
			if (rdl == sec)
			{
				if (Table->I_List[(*funq).two.code - 1].second->yn == 1)
				{
					*file << "MOV" << " ";
					if ((*funq).two.type != 'I') *file << Table->FindVal((*funq).two);
					else *file << "[" << sec << "]";
					*file << ",";
					*file << "AX";
					*file << endl;
				}
				state = 0;
			}
		}
		if (state)
		{
			if (other_a == 1)//
			{
				*file << "MOV" << " ";
				*file << "[" << rdl << "]";
				*file << ",";
				*file << "AX";
				*file << endl;
			}
			*file << "MOV" << " ";
			*file << "AX";
			*file << ",";
			if ((*funq).two.type != 'I') *file << Table->FindVal((*funq).two);
			else *file << "[" << sec << "]";

			*file << endl;
		}
		rdl = fou;
		other_a = Table->I_List[(*funq).four.code - 1].second->yn;
	}


	this->funque.pop_front();
	if (!(this->funque.front()->one == "+" || this->funque.front()->one == "*" || this->funque.front()->one == "/" || this->funque.front()->one == "-" || this->funque.front()->one == ":="))
	{
		*file << "MOV" << " ";
		if ((*funq).four.type != 'I') *file << Table->FindVal((*funq).two);
		else *file << "[" << fou << "]";
		*file << ",";
		*file << "AX";
		*file << endl;
		rdl = "0";
		other_a = 1;
		this->funq = this->funque.front();
		return;
	}

	this->obj();
}
