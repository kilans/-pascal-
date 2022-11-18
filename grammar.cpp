#include"syntax.h"

syntax::syntax(Symbol_Table*T)//开始时指向第一个token
{

    if (T->Token.empty())
        return;
   this->state = 0;
   this->trans = new Translate;
   t=T->Token.front();
   T->Token.pop();
   
   //sign=1;
}

void syntax::nexttoken(Symbol_Table* T)
{
    if (this->error.size())
        this->Error(T);
    if (T->Token.empty() && T->A_R.empty())
        return;

    t = T->Token.front();
    T->Token.pop();  

    //cout << "now:  " << t.type << " " << t.code << endl;
}
void syntax::Main(Symbol_Table* T)
{
    this->program(T);
    this->Error(T);
    T->ReFun();
    this->Print(T);
    
}
void syntax::program(Symbol_Table* T)//主程序产生式
{

    if (t.type == 'K' && t.code == 1)//关键字program
    {
        nexttoken(T);//字符判断后读入下一个token
        while(trans->state.size())trans->state.pop();
        if (t.type == 'I')//标识符
        {
            trans->In_TableF(T, t);      //填写函数符号表
            trans->Get_Quartion_Fun(t); //函数声明四元式
            nexttoken(T);//读入下一个token
             this->pralist(T);//参数列表
            subprogram(T);//转入子程序处理函数
            if (t.type == 'P' && t.code == 9)//整个程序以一个'.'结束
            {
                T->A_R.pop();
                nexttoken(T);//整个token队列的最后一个token出队，此时队列应该为空，可以用token.empty()判断              
                return;
            }
            else if (t.type == 'P' && t.code == 13)//左括号
            {
                nexttoken(T);
                if (t == T->A_R.top()->token_code)
                {
                    T->A_R.pop();       //活动记录弹出  
                    nexttoken(T);
                    if (t.type == 'P' && t.code == 14)
                        nexttoken(T);
                }
                
            }
            else             
            {
                this->error.push(1);
                
            }
            //this->sign=0;
        }
        

        else
              this->error.push(5);
        //this->sign=0;
    }
    return;
       //this->sign=0;
}
void syntax::subprogram(Symbol_Table* T)//三个子程序，先进行结构体声明，再进行变量声明，最后是语句合集
{
    conststatement(T);
    this->state = 2;
    typestatement(T);
    this->state = 0;
    varstatement(T);
    contipro(T); //连续函数声明
    sentencecom(T);

}
void syntax::contipro(Symbol_Table* T)
{
    this->program(T);
    while (this->t.code == 1 && this->t.type == 'K')
    {
        this->program(T);
    }
    return;
}
void syntax::conststatement(Symbol_Table* T)
{
    if (t.type == 'K' && t.code == 11)              //const
    {
        this->state = 1;
        nexttoken(T);
        varid(T);           //进入变量连续声明
        if (t.type == 'P' && t.code == 12)//变量表后面接一个冒号
        {
            nexttoken(T);
            vartype(T);//变量类型
            varstatementsub(T);//处理多种变量

        }
                    
    }

    return;
}
void syntax::typestatement(Symbol_Table* T)//结构体声明
{
    if(t.type=='K'&&t.code==9)//关键字type
    {   
        this->state = 2;
        nexttoken(T);
        if(t.type=='I')//type的后面是一个标识符
        {
            trans->Rec_Struct(T, t);    //结构体定义
            nexttoken(T);
            if(t.type=='P'&&t.code==12)//这里应该是一个等号
            {
                nexttoken(T);
                if(t.type=='K'&&t.code==8)//关键字record
                {
                    nexttoken(T);
                    fieldid(T);//转进域名表
                    if(t.type=='K'&&t.code==7)//end
                        {
                            trans->In_TableT(T,trans->Token.top());
                            nexttoken(T);
                            if (t.type == 'P' && t.code == 3)//声明结束，end后面加了一个分号
                            {
                                nexttoken(T);
                            }
                            else
                                this->error.push(6);
                        }
                        else
                            cout<<"error";
                }
                else
                    cout<<"error";
            }
            else
                cout<<"error";
        }
        else
            cout<<"error";
    }

    return;
}
void syntax::fieldid(Symbol_Table *T)//域名表
{
    varid(T);//变量表
    if(t.type=='P'&&t.code==2)//变量表后面接一个冒号
    {
        nexttoken(T);
        vartype(T);//变量种类
        while(t.type=='P'&&t.code==3)//这个循环用于读入多个域名，分号表示域名未结束
        {
            nexttoken(T);
            if (t.type == 'I')
                varid(T);//下一组变量表
            else
                break;
            if(t.type=='P'&&t.code==2)//冒号
            {
                nexttoken(T);
                vartype(T);//种类
            }
            else
                cout<<"error";
        }
    }
    else
        cout<<"error";

}
void syntax::varstatement(Symbol_Table* T)//变量声明区
{
    if(t.type=='K'&&t.code==2)//变量声明区以var开头
    {
        
        nexttoken(T);
        varid(T);//读完var要进到变量表里
        if(t.type=='P' && t.code==2)//变量表后面接一个冒号
        {
            nexttoken(T);
            vartype(T);//变量类型
            varstatementsub(T);//处理多种变量

        }
        else
            cout<<"error";
    }
    else
        cout<<"error";
    return;
}
void syntax::varstatementsub(Symbol_Table* T)//处理花括号中内容的函数
{
    if(t.type=='P'&&t.code==3)//这里需要一个分号，表示可能有下一个变量类型
    {
        nexttoken(T);
        if (t.type == 'I')
            varid(T);//进到标识符表
        else
            return;
        if(t.type=='P'&&t.code==2)//标识符表后的冒号
        {
            nexttoken(T);
            vartype(T);//类型
            varstatementsub(T);//递归处理
        }
        else
            cout<<"error";//有标识符表没有冒号要报错
    }
    //else
    //    return;//只有一种变量声明就直接退出这个函数
}
void syntax::varid(Symbol_Table* T)//标识符表，形如  a,b,c,d
{
    if (t.type == 'I')
    {
        trans->Var_Statement(T, t); //进入队列
        nexttoken(T);
        while (t.type == 'P' && t.code == 1)//这个循环用于多个变量名，读到逗号表示后面还有变量，即每执行一次循环读入 ,a
        {
            nexttoken(T);
            if (t.type == 'I')
            {
                trans->Var_Statement(T, t); //进入队列
                nexttoken(T);
            }
            else
                this->error.push(7);
        }
    }
    else
        error.push(2);
    return;
}
void syntax::vartype(Symbol_Table* T)
{
    if (t.type == 'K')//标识符
    {
        if ((t.code >= 3 && t.code <= 5) || t.code == 12)
        {
            switch (state)
            {
            case 0:trans->In_TableV(T, t); break;//变量
            case 2:trans->In_TableN(T, t); break;//域名
            case 3:trans->In_TableP(T,t ,fstate); break;//参数
            }
        }//填标识符主表
        else
            cout << "error";
    }
    else if (t.type == 'I')    //结构体类
    {
        if (T->I_List[t.code - 1].second->cat == "T")
        {
            switch (state)
            {
            case 0:trans->In_TableV(T, t); break;
            case 2:trans->In_TableN(T, t); break;
            case 3:trans->In_TableP(T, t, fstate); break;//参数
            }
        }
        else if (T->I_List[t.code - 1].second->cat == "const")
        {
            switch (state)
            {
            case 0:trans->In_TableV(T, t); break;
            case 2:trans->In_TableN(T, t); break;
            case 3:trans->In_TableP(T, t, fstate); break;//参数
            }
        }
        else
            this->error.push(7);
    }
    else if (t.type == 'C')     //常量类型
    {
        trans->In_TableC(T, t); 
    }
    else
    {
        error.push(4);
        return;
    }
    nexttoken(T);
    return;
}
void syntax::sentencecom(Symbol_Table* T)//这里是语句区
{
    if(t.type=='K'&&t.code==6)//需要读入关键字begin
    {
        if (T->A_R.size() == 1)
            trans->Get_Quartion_Start();//设置入口
        nexttoken(T);
        sentences(T);//begin和end间的语句
        if(t.type=='K'&&t.code==7)//语句区要以end结束
        {       
            trans->Get_Quartion_Fun_End(T->A_R.top()->token_code);  //栈顶函数
 
            nexttoken(T);
        }
        else
            cout<<"error";
    }
    else
        cout<<"error";
}
void syntax::sentences(Symbol_Table* T)//这里是中间的语句，暂时只有赋值语句
{
   
   value(T);
   while((t.type=='P'&&t.code==3)||(t.type=='K'&&t.code==1))//当遇到分号时标志着后面还有赋值语句
   {
       nexttoken(T);
           value(T);
    
   }
       //函数嵌套
}
void syntax::value(Symbol_Table* T)//赋值语句
{
    if (t.type == 'I')//赋值语句要以标识符开头
    {
        if (!T->SearchV(t))
        {
            error.push(3);
            return;
        }
        if (T->I_List[t.code - 1].second->type.second == 0)   //不是结构体赋值和函数
        {
            trans->Push_Factor(t);
            nexttoken(T);
        }
        else if (T->I_List[t.code - 1].second->cat == "const")//常量也不可以赋值
        {
               error.push(5);
               return;
        }
        else if (T->I_List[t.code - 1].second->cat =="F")//函数
        {                                                     
              this->Func(T,t);
              nexttoken(T);
              return;
        }
        
        if (t.type == 'P' && t.code == 4)//赋值符号:=
        {
            nexttoken(T);
            cauculatesub1(T);//:=后为算数表达式
            trans->Get_Quartion_Equ();  //算术表达式分析完毕，生成赋值四元式
        }
        else
            cout << "error";
    }
    return;
}
void syntax::cauculatesub1(Symbol_Table* T)         //加减号处理机
{
   
  
   cauculatesub2(T);//转到进行乘除运算的子程序
   Token_Code cal = t; //保留运算符
   while((t.type=='P'&&t.code==7) ||(t.type=='P'&&t.code==8))//该循环处理花括号内,循环进行的条件是遇到加号或减号
   {      
       nexttoken(T);
       cauculatesub2(T);
       trans->Get_Quartion(T, cal);
   }
   return;
}
void syntax::cauculatesub2(Symbol_Table* T)
{
    cauculatesub3(T);//运算元，在括号内的算数表达式或者i，即常数或标识符
    Token_Code cal = t; //保留运算符
    while((t.type=='P'&&t.code==5) ||(t.type=='P'&&t.code==6))//该循环处理花括号内,循环进行的条件是遇到乘号或除号
    {
       nexttoken(T);
       cauculatesub3(T);
       trans->Get_Quartion(T, cal);
    }
    return;
}
void syntax::cauculatesub3(Symbol_Table* T)
{
    if((t.type=='I')||(t.type=='C') || (t.type == 'S'))//这里表示读到i可以继续读
    {
        //预处置
        if (!T->SearchV(t) && t.type=='I')
        {
            error.push(3);
            return;
        }
        trans->Push_Factor(t);
        nexttoken(T);
    }
    else if(t.type=='P'&&t.code==10)//这里表示遇到括号，转回表达式处理
    {
        nexttoken(T);
        cauculatesub1(T);
        if(t.type=='P'&&t.code==11)//处理完表达式后要有右括号
        {
            nexttoken(T);
        }
        else
            cout<<"error";
    }
    else
        cout<<"error";
    return;
}

void syntax::pralist(Symbol_Table* T)
{
    if (t.type == 'P' && t.code == 10)
    {
        state = 3;
        this->nexttoken(T);
        if (t.type == 'P' && t.code == 11)
        {
            this->nexttoken(T);
            return;
        }
        this->fstate = 1;
        varid(T);   
        if (t.type == 'P' && t.code == 2)//变量表后面接一个冒号
        {
            nexttoken(T);
            vartype(T);//变量类型
            varstatementsub(T);//处理多种变量
        }
        //以上为形参列表
        this->fstate = 0;
        this->varstatement(T);            //此处为换名形参
        if ((t.type == 'P' && t.code == 11))    //空列表
        {
            this->nexttoken(T);
            return;
        }
        else
            this->error.push(8);
    }
    return;
}
void syntax::Func(Symbol_Table* T, Token_Code token)
{
    
    int order = 0;
    I_Table* it = T->I_List[token.code - 1].second;         //函数标识符表
    //cout << it->code << endl;
    Cat_Table* ft = (it->other);
    Activity_Record* A = T->Activity[it->type.second-1];        //找到该函数的活动记录
    Token_Code tar;
    
    nexttoken(T);
    if (!(t.type == 'P' && t.code == 10))
    {
        error.push(9);
        return;
    }
    nexttoken(T);
    while (t.type == 'I')
    {
        if (order == ft->num)           //传入参数多于参数列表
        {
            error.push(9);
            return;
        }
        tar = Token_Code('I', (*ft->paralist)[order]->code);
        trans->Get_Quartion_Trans(T,t,tar);
        nexttoken(T);
        if((t.type == 'P' && t.code == 1))
        {
            nexttoken(T);
        }
        order++;
    }
    if (order < ft->num)        //传参
    {
        error.push(9);
        return;
    }
    if (!(t.type == 'P' && t.code == 11))
    {
        error.push(9);
        return;
    }
    trans->Get_Quartion_CalFfun(token);
    return;
}
void syntax::Error(Symbol_Table *T)
{
    if (this->error.empty())
    {
        //cout << "语法无误！" << endl;
        return;
    }    
    int E;
    string tip;
    while (!this->error.empty())
    {
        E = this->error.front();
        switch (E)
        {
        case 1:tip = "函数未设终结标识"; break;
        case 2:tip = "声明语句对象错误"; break;
        case 3:tip = "未声明变量"; break;
        case 4:tip = "声明对象类型错误"; break;
        case 5:tip = "未明函数过程声明"; break;
        case 6:tip = "变量声明未设终结符"; break;
        case 7:tip = "变量定义错误"; break;
        case 8:tip = "参数列表定义错误"; break;
        case 9:tip = "函数调用错误"; break;
        case 10:tip = "参数引用错误"; break;
        }
        this->error.pop();
        int count = 0;
        cout << T->I_List[T->A_R.top()->token_code.code - 1].first << " ";
        while (!trans->state.empty() && !trans->Token.empty())
        {
            string temp;
            if (!trans->state.empty())
            {
                t = trans->state.front();
                trans->state.pop();
                switch (t.type)
                {
                case 'K':temp = T->K_List[t.code - 1].first; break;
                case 'I':temp = T->I_List[t.code - 1].first; break;
                case 'C':temp = T->C_List[t.code - 1].first; break;
                }
                cout << temp << " ";
            }
            if (!trans->Token.empty())
            {
                t = trans->Token.top();
                trans->Token.pop();

                switch (t.type)
                {
                case 'K':temp = T->K_List[t.code - 1].first; break;
                case 'I':temp = T->I_List[t.code - 1].first; break;
                case 'C':temp = T->C_List[t.code - 1].first; break;
                }
                cout << temp << " ";
            }
        }
        cout << tip << endl;
    }
    exit(-1);
}
void syntax::Print(Symbol_Table* T)
{
    system("pause");
    cout << "name" << "\t" << "type" << "\t" << "cat" << "\t" << "other"<<"\t";
    cout << endl;
    for (int i = 0; i < T->I_List.size(); i++)
    {
        cout << T->I_List[i].second->name << "\t" << T->I_List[i].second->type.first << "\t" << T->I_List[i].second->cat << "\t";
        if (T->I_List[i].second->cat == "F")
        {
            
            cout << T->I_List[i].second->other->ptr.first << endl;
            cout << "入口地址:" << T->Activity[T->I_List[i].second->type.second - 1]->old_sp << "  参数个数:" << T->I_List[i].second->other ->parameter<<endl;
            cout << "参数表：" << endl;
            vector<I_Table*> *list = T->I_List[i].second->other->paralist;
            for (int j = 0; j < T->I_List[i].second->other->paralist->size(); j++)
            {
                cout << (*list)[j]->name << "\t" << (*list)[j]->type.first << "\t" << (*list)[j]->cat << "\t" << (*list)[j]->other->ptr.first << "," << (*list)[j]->other->ptr.second << endl;
                
            }
        }
        if (T->I_List[i].second->other->ptr.second != 0)
            cout << T->I_List[i].second->other->ptr.first << "," << T->I_List[i].second->other->ptr.second << "\t";
        else if (T->I_List[i].second->other->length != 0)
            cout << T->I_List[i].second->other->length << "\t";
        cout << endl;
    }
}