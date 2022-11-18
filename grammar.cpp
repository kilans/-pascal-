#include"syntax.h"

syntax::syntax(Symbol_Table*T)//��ʼʱָ���һ��token
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
void syntax::program(Symbol_Table* T)//���������ʽ
{

    if (t.type == 'K' && t.code == 1)//�ؼ���program
    {
        nexttoken(T);//�ַ��жϺ������һ��token
        while(trans->state.size())trans->state.pop();
        if (t.type == 'I')//��ʶ��
        {
            trans->In_TableF(T, t);      //��д�������ű�
            trans->Get_Quartion_Fun(t); //����������Ԫʽ
            nexttoken(T);//������һ��token
             this->pralist(T);//�����б�
            subprogram(T);//ת���ӳ�������
            if (t.type == 'P' && t.code == 9)//����������һ��'.'����
            {
                T->A_R.pop();
                nexttoken(T);//����token���е����һ��token���ӣ���ʱ����Ӧ��Ϊ�գ�������token.empty()�ж�              
                return;
            }
            else if (t.type == 'P' && t.code == 13)//������
            {
                nexttoken(T);
                if (t == T->A_R.top()->token_code)
                {
                    T->A_R.pop();       //���¼����  
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
void syntax::subprogram(Symbol_Table* T)//�����ӳ����Ƚ��нṹ���������ٽ��б�����������������ϼ�
{
    conststatement(T);
    this->state = 2;
    typestatement(T);
    this->state = 0;
    varstatement(T);
    contipro(T); //������������
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
        varid(T);           //���������������
        if (t.type == 'P' && t.code == 12)//����������һ��ð��
        {
            nexttoken(T);
            vartype(T);//��������
            varstatementsub(T);//������ֱ���

        }
                    
    }

    return;
}
void syntax::typestatement(Symbol_Table* T)//�ṹ������
{
    if(t.type=='K'&&t.code==9)//�ؼ���type
    {   
        this->state = 2;
        nexttoken(T);
        if(t.type=='I')//type�ĺ�����һ����ʶ��
        {
            trans->Rec_Struct(T, t);    //�ṹ�嶨��
            nexttoken(T);
            if(t.type=='P'&&t.code==12)//����Ӧ����һ���Ⱥ�
            {
                nexttoken(T);
                if(t.type=='K'&&t.code==8)//�ؼ���record
                {
                    nexttoken(T);
                    fieldid(T);//ת��������
                    if(t.type=='K'&&t.code==7)//end
                        {
                            trans->In_TableT(T,trans->Token.top());
                            nexttoken(T);
                            if (t.type == 'P' && t.code == 3)//����������end�������һ���ֺ�
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
void syntax::fieldid(Symbol_Table *T)//������
{
    varid(T);//������
    if(t.type=='P'&&t.code==2)//����������һ��ð��
    {
        nexttoken(T);
        vartype(T);//��������
        while(t.type=='P'&&t.code==3)//���ѭ�����ڶ������������ֺű�ʾ����δ����
        {
            nexttoken(T);
            if (t.type == 'I')
                varid(T);//��һ�������
            else
                break;
            if(t.type=='P'&&t.code==2)//ð��
            {
                nexttoken(T);
                vartype(T);//����
            }
            else
                cout<<"error";
        }
    }
    else
        cout<<"error";

}
void syntax::varstatement(Symbol_Table* T)//����������
{
    if(t.type=='K'&&t.code==2)//������������var��ͷ
    {
        
        nexttoken(T);
        varid(T);//����varҪ������������
        if(t.type=='P' && t.code==2)//����������һ��ð��
        {
            nexttoken(T);
            vartype(T);//��������
            varstatementsub(T);//������ֱ���

        }
        else
            cout<<"error";
    }
    else
        cout<<"error";
    return;
}
void syntax::varstatementsub(Symbol_Table* T)//�������������ݵĺ���
{
    if(t.type=='P'&&t.code==3)//������Ҫһ���ֺţ���ʾ��������һ����������
    {
        nexttoken(T);
        if (t.type == 'I')
            varid(T);//������ʶ����
        else
            return;
        if(t.type=='P'&&t.code==2)//��ʶ������ð��
        {
            nexttoken(T);
            vartype(T);//����
            varstatementsub(T);//�ݹ鴦��
        }
        else
            cout<<"error";//�б�ʶ����û��ð��Ҫ����
    }
    //else
    //    return;//ֻ��һ�ֱ���������ֱ���˳��������
}
void syntax::varid(Symbol_Table* T)//��ʶ��������  a,b,c,d
{
    if (t.type == 'I')
    {
        trans->Var_Statement(T, t); //�������
        nexttoken(T);
        while (t.type == 'P' && t.code == 1)//���ѭ�����ڶ�����������������ű�ʾ���滹�б�������ÿִ��һ��ѭ������ ,a
        {
            nexttoken(T);
            if (t.type == 'I')
            {
                trans->Var_Statement(T, t); //�������
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
    if (t.type == 'K')//��ʶ��
    {
        if ((t.code >= 3 && t.code <= 5) || t.code == 12)
        {
            switch (state)
            {
            case 0:trans->In_TableV(T, t); break;//����
            case 2:trans->In_TableN(T, t); break;//����
            case 3:trans->In_TableP(T,t ,fstate); break;//����
            }
        }//���ʶ������
        else
            cout << "error";
    }
    else if (t.type == 'I')    //�ṹ����
    {
        if (T->I_List[t.code - 1].second->cat == "T")
        {
            switch (state)
            {
            case 0:trans->In_TableV(T, t); break;
            case 2:trans->In_TableN(T, t); break;
            case 3:trans->In_TableP(T, t, fstate); break;//����
            }
        }
        else if (T->I_List[t.code - 1].second->cat == "const")
        {
            switch (state)
            {
            case 0:trans->In_TableV(T, t); break;
            case 2:trans->In_TableN(T, t); break;
            case 3:trans->In_TableP(T, t, fstate); break;//����
            }
        }
        else
            this->error.push(7);
    }
    else if (t.type == 'C')     //��������
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
void syntax::sentencecom(Symbol_Table* T)//�����������
{
    if(t.type=='K'&&t.code==6)//��Ҫ����ؼ���begin
    {
        if (T->A_R.size() == 1)
            trans->Get_Quartion_Start();//�������
        nexttoken(T);
        sentences(T);//begin��end������
        if(t.type=='K'&&t.code==7)//�����Ҫ��end����
        {       
            trans->Get_Quartion_Fun_End(T->A_R.top()->token_code);  //ջ������
 
            nexttoken(T);
        }
        else
            cout<<"error";
    }
    else
        cout<<"error";
}
void syntax::sentences(Symbol_Table* T)//�������м����䣬��ʱֻ�и�ֵ���
{
   
   value(T);
   while((t.type=='P'&&t.code==3)||(t.type=='K'&&t.code==1))//�������ֺ�ʱ��־�ź��滹�и�ֵ���
   {
       nexttoken(T);
           value(T);
    
   }
       //����Ƕ��
}
void syntax::value(Symbol_Table* T)//��ֵ���
{
    if (t.type == 'I')//��ֵ���Ҫ�Ա�ʶ����ͷ
    {
        if (!T->SearchV(t))
        {
            error.push(3);
            return;
        }
        if (T->I_List[t.code - 1].second->type.second == 0)   //���ǽṹ�帳ֵ�ͺ���
        {
            trans->Push_Factor(t);
            nexttoken(T);
        }
        else if (T->I_List[t.code - 1].second->cat == "const")//����Ҳ�����Ը�ֵ
        {
               error.push(5);
               return;
        }
        else if (T->I_List[t.code - 1].second->cat =="F")//����
        {                                                     
              this->Func(T,t);
              nexttoken(T);
              return;
        }
        
        if (t.type == 'P' && t.code == 4)//��ֵ����:=
        {
            nexttoken(T);
            cauculatesub1(T);//:=��Ϊ�������ʽ
            trans->Get_Quartion_Equ();  //�������ʽ������ϣ����ɸ�ֵ��Ԫʽ
        }
        else
            cout << "error";
    }
    return;
}
void syntax::cauculatesub1(Symbol_Table* T)         //�Ӽ��Ŵ����
{
   
  
   cauculatesub2(T);//ת�����г˳�������ӳ���
   Token_Code cal = t; //���������
   while((t.type=='P'&&t.code==7) ||(t.type=='P'&&t.code==8))//��ѭ������������,ѭ�����е������������ӺŻ����
   {      
       nexttoken(T);
       cauculatesub2(T);
       trans->Get_Quartion(T, cal);
   }
   return;
}
void syntax::cauculatesub2(Symbol_Table* T)
{
    cauculatesub3(T);//����Ԫ���������ڵ��������ʽ����i�����������ʶ��
    Token_Code cal = t; //���������
    while((t.type=='P'&&t.code==5) ||(t.type=='P'&&t.code==6))//��ѭ������������,ѭ�����е������������˺Ż����
    {
       nexttoken(T);
       cauculatesub3(T);
       trans->Get_Quartion(T, cal);
    }
    return;
}
void syntax::cauculatesub3(Symbol_Table* T)
{
    if((t.type=='I')||(t.type=='C') || (t.type == 'S'))//�����ʾ����i���Լ�����
    {
        //Ԥ����
        if (!T->SearchV(t) && t.type=='I')
        {
            error.push(3);
            return;
        }
        trans->Push_Factor(t);
        nexttoken(T);
    }
    else if(t.type=='P'&&t.code==10)//�����ʾ�������ţ�ת�ر��ʽ����
    {
        nexttoken(T);
        cauculatesub1(T);
        if(t.type=='P'&&t.code==11)//��������ʽ��Ҫ��������
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
        if (t.type == 'P' && t.code == 2)//����������һ��ð��
        {
            nexttoken(T);
            vartype(T);//��������
            varstatementsub(T);//������ֱ���
        }
        //����Ϊ�β��б�
        this->fstate = 0;
        this->varstatement(T);            //�˴�Ϊ�����β�
        if ((t.type == 'P' && t.code == 11))    //���б�
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
    I_Table* it = T->I_List[token.code - 1].second;         //������ʶ����
    //cout << it->code << endl;
    Cat_Table* ft = (it->other);
    Activity_Record* A = T->Activity[it->type.second-1];        //�ҵ��ú����Ļ��¼
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
        if (order == ft->num)           //����������ڲ����б�
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
    if (order < ft->num)        //����
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
        //cout << "�﷨����" << endl;
        return;
    }    
    int E;
    string tip;
    while (!this->error.empty())
    {
        E = this->error.front();
        switch (E)
        {
        case 1:tip = "����δ���ս��ʶ"; break;
        case 2:tip = "�������������"; break;
        case 3:tip = "δ��������"; break;
        case 4:tip = "�����������ʹ���"; break;
        case 5:tip = "δ��������������"; break;
        case 6:tip = "��������δ���ս��"; break;
        case 7:tip = "�����������"; break;
        case 8:tip = "�����б������"; break;
        case 9:tip = "�������ô���"; break;
        case 10:tip = "�������ô���"; break;
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
            cout << "��ڵ�ַ:" << T->Activity[T->I_List[i].second->type.second - 1]->old_sp << "  ��������:" << T->I_List[i].second->other ->parameter<<endl;
            cout << "������" << endl;
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