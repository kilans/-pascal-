#include"扫描器.h"
void Translate::Var_Statement(Symbol_Table* T, Token_Code code)
{
	this->state.push(code);
	//cout << "队列容量元素个数" << state.size() << endl;
	return;
}
void Translate::In_TableF(Symbol_Table* T, Token_Code code)		//函数标识符
{
	Activity_Record* A = NULL;
	if (T->A_R.size())											//有前函数
	{
		A = new Activity_Record(T->A_R.top()->level+1,code,T->A_R.top()->the_display,T->Activity.back());									//栈顶活动记录,
	}
	else
	{								//第一个函数
		A = new Activity_Record(code);	//层次号为1
	}
	T->Activity.push_back(A);
	T->A_R.push(A);											//活动记录压栈
	I_Table* it = T->I_List[code.code-1].second;			//填写函数符号表
	it->other = new Cat_Table('F');							//函数表
	it->cat = 'F';
	it->type = make_pair(' ',T->Activity.size());
	Cat_Table* ft = (it->other);	//子类转换为函数表
	ft->paralist = new vector<I_Table*>;

	ft->ptr.first = A->level;								//函数层次号
	ft->ptr.second = 0;// *A->K_var.back().second.low;			//符号表对应填写,在此之前填入了活动记录
}
void Translate::In_TableV(Symbol_Table* T,Token_Code code)		//变量标识符声明类型
{

	while (!this->state.empty())
	{
		Token_Code var = this->state.front();					//声明元素
		this->state.pop();
		//cout << "var: " << var.type << " " << var.code << endl;
		//cout << T->I_List.size();
		Activity_Record* A = T->A_R.top();						//栈顶活动记录,
		I_Table* it = T->I_List[var.code-1].second;				//声明元素的标识符表
		if (it->other->ptr.first)
		{
			cout << T->I_List[var.code - 1].first;
			cout << "重定义" << endl;
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
			length = T->I_List[code.code-1].second->other->length;	//结构体或常量
			it->type = T->I_List[code.code-1].second->type;
		}
		it->cat = "V";
		it->other = new Cat_Table();
		it->other->ptr.first = A->level;						//栈顶活动记录层次号
		it->other->ptr.second = A->voff;		//符号表对应填写
		A->InsertV(var, length);										//
		T->I_List[A->token_code.code - 1].second->other->paralist->push_back(it);
	}
	return;
	//注意这里还需要加活动记录的区距
}
void Translate::Rec_Struct(Symbol_Table* T, Token_Code code)		//定义结构体
{
	this->Token.push(code);												//结构体token压栈
	I_Table* it = T->I_List[code.code-1].second;
	it->other = new Cat_Table();
	it->cat = 'T';
	T->Type_List.push_back(make_pair(it->name, new Struct_Table()));	//创建结构体表
	it->type = make_pair('t', T->Type_List.size());					//类型定义
	return;
}
void Translate::In_TableT(Symbol_Table* T, Token_Code code)
{
	this->Token.pop();
	I_Table* it = T->I_List[code.code-1].second;		//结构体列表
	
	it->other->length = T->Type_List[it->type.second - 1].second->length;			//长度赋予	
	it->type = make_pair('T', T->Type_List.size());
	return;
}
void Translate::In_TableN(Symbol_Table* T, Token_Code code)		//域名填写
{
	while (!this->state.empty())
	{
		Token_Code var = this->state.front();
		this->state.pop();
		I_Table* it = T->I_List[var.code-1].second;					//在标识符表内
		it->other = new Cat_Table();
		Struct_Table* tt = T->Type_List[T->I_List[this->Token.top().code-1].second->type.second-1].second;				//在结构表内的域名表
		Domain dom(it);
		if (!tt->Domain_List.empty())
			dom.ptr.low = tt->Domain_List.back().ptr.length;
		else
			dom.ptr.low = 0;
		switch (code.code)
		{
		case 11:dom.ptr.high = dom.ptr.low + 4; it->other->length = 4; tt->length += 4; it->type = make_pair('C', 0); break;
		case 5:dom.ptr.high = dom.ptr.low + 1; it->other->length = 1; tt->length += 1; it->type = make_pair('c', 0); break;
		case 4:dom.ptr.high = dom.ptr.low + 4; it->other->length = 4; tt->length += 4; it->type = make_pair('r', 0); break;//域名表，标识符表，标识符结构体对应长度++
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
		I_Table* it = T->I_List[var.code - 1].second;					//在标识符表内
		it->other = new Cat_Table();
		it->other->con_val = T->C_List[code.code-1].first;				//常量表
		it->other->length = 4;
		it->type = make_pair('r',0);
		it->cat = "const";
	}

	return;
}
void Translate::In_TableP(Symbol_Table* T, Token_Code code,int type)	//参数列表填写
{
	while (!this->state.empty())
	{
		Token_Code var = this->state.front();					//声明元素
		this->state.pop();
		//cout << "var: " << var.type << " " << var.code << endl;
		//cout << T->I_List.size();
		Activity_Record* A = T->A_R.top();						//栈顶活动记录,
		I_Table* it = T->I_List[var.code - 1].second;				//声明元素的标识符表
		Cat_Table * ft = T->I_List[A->token_code.code - 1].second->other;
		int length = 0;
		if (it->other->ptr.first)
		{
			cout << T->I_List[var.code - 1].first;
			cout << "重定义" << endl;
			exit(-1);
		}
		if (type)			//变量
			it->cat = "VF";
		else
			it->cat = "VN";//换名形参
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
			length = T->I_List[code.code - 1].second->other->length;	//结构体或常量
			it->type = T->I_List[code.code - 1].second->type;
		}
		//cout << A->token_code.code << endl;
		it->other = new Cat_Table();
		it->other->ptr.first = A->level;						//栈顶活动记录层次号
		it->other->ptr.second = A->poff;
		it->other->length = length;
		ft->num++;
		A->InsertP(var, length);		
		A->prama_num++;						//参数个数
		
		
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