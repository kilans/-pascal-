#include"扫描器.h"
void Symbol_Table::Table_Main()
{
    this->Scan("test.pas");
    this->Print();
    //this->Init_Token();
}
Symbol_Table::Symbol_Table()
{
    this->error = 0;
    this->t_code = 0;
    this->K_List.push_back(make_pair("program", 1));
    this->K_List.push_back(make_pair("var", 2));
    this->K_List.push_back(make_pair("integer", 3));
    this->K_List.push_back(make_pair("real", 4));
    this->K_List.push_back(make_pair("char", 5));
    this->K_List.push_back(make_pair("begin", 6));
    this->K_List.push_back(make_pair("end", 7));
    this->K_List.push_back(make_pair("record", 8));
    this->K_List.push_back(make_pair("type", 9));
    this->K_List.push_back(make_pair("boolean", 10));
    this->K_List.push_back(make_pair("const", 11));

    this->P_List.push_back(make_pair(",", 1));
    this->P_List.push_back(make_pair(":", 2));
    this->P_List.push_back(make_pair(";", 3));
    this->P_List.push_back(make_pair(":=", 4));
    this->P_List.push_back(make_pair("*", 5));
    this->P_List.push_back(make_pair("/", 6));
    this->P_List.push_back(make_pair("+", 7));
    this->P_List.push_back(make_pair("-", 8));
    this->P_List.push_back(make_pair(".", 9));
    this->P_List.push_back(make_pair("(", 10));
    this->P_List.push_back(make_pair(")", 11));
    this->P_List.push_back(make_pair("=", 12));
    this->P_List.push_back(make_pair("{", 13));
    this->P_List.push_back(make_pair("}", 14));;
    
    
    //this->P_List.insert(make_pair("'", 12));        //扩充的单引号用于定义字符

    return;
}
bool Symbol_Table::Is_Word(char c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        return 1;
    else
        return 0;
}
bool Symbol_Table::Is_Num(char c)
{
    if (c >= '0' && c <= '9')
        return 1;
    else
        return 0;
}
bool Symbol_Table::Is_P(char c)
{
    string S;
    S.push_back(c);
    vector<pair<string,int>>::iterator it = find_if(this->P_List.begin(), this->P_List.end(), [S](pair<string, int> temp) {return temp.first == S; });
    if (it != this->P_List.end())   //找到
        return 1;
    else
        return 0;
}

void Symbol_Table::Scan(string filename)
{
    ifstream file;
    char c;
    int state = 0;
    
    string errors;
    file.open(filename, ios::in);

    if (!file.is_open())
    {
        cout << "请编辑\"test.pas\"文本" << endl;
        system("pause");
        exit(-1);
    }


    while ((c = file.get()) != EOF)
    {
        string temp;
        if (error) break;
        if (c == '\n' || c == ' ') continue;            //空格换行符

        if (this->Is_Word(c))           //是字母
        {
            while (!(this->Is_P(c) || c == ' ' || c == '\n'))        //不是界符则持续读入
            {
                if (!(this->Is_Num(c) || this->Is_Word(c)))     //读入字符不是数字或字母
                {
                    error = 1;
                    break;
                }
                temp.push_back(c);
                c = file.get();
            }
            if (error)
            {
                errors = temp + c;
                break;
            }
            file.putback(c);
            vector<pair<string, int>>::iterator it = find_if(this->K_List.begin(), this->K_List.end(), [temp](pair<string, int> tar) {return tar.first == temp; });
            if (it != this->K_List.end())  //关键字
            {
                this->Token.push(Token_Code('K', it->second));
            }
            else                                                //标识符
            {
                vector<pair<string,I_Table*>>::iterator it = find_if(this->I_List.begin(), this->I_List.end(), [temp](pair<string,I_Table*> tar) {return tar.first == temp; });
                if (it == this->I_List.end())       //没找到就插入
                {
                    I_Table* i_table = new I_Table(this->I_List.size() + 1,temp);
                    this->I_List.push_back(make_pair(temp, i_table));
                    this->Token.push(Token_Code('I', i_table->code));
                }
                else
                {
                    this->Token.push(Token_Code('I', it->second->code));
                }                
            }
        }
        else if (this->Is_P(c))          //是界符
        {
                temp.push_back(c);
                if (c == ':' || c == '<' || c == '>' || c == '=') //
                {
                    c = file.get();
                    if (c == '=')
                        temp.push_back(c);
                    else
                        file.putback(c);
                }
                vector<pair<string, int>>::iterator it = find_if(this->P_List.begin(), this->P_List.end(), [temp](pair<string, int> tar) {return tar.first == temp; });
                this->Token.push(Token_Code('P', it->second));
        }
        else if (this->Is_Num(c))        //首位是数字    
        {
            while (c == '.' || !(this->Is_P(c) || c == '\n' || c == ' '))       //不是界符
            {
                if (!this->Is_Num(c) && state)                   //且不是数字
                {
                    cout << c << endl;
                    system("pause");
                    error = 2;
                    errors = temp+c;
                    break;
                }
                if (c == '.')
                    state = 1;
                temp.push_back(c);
                c = file.get();
            }
            if (error)
            {
                break;
            }
            if (temp.back() == '.')
            {
                error = 2;
                errors = temp;
                break;
            }           
            file.putback(c);
            vector<pair<string, int>>::iterator it = find_if(this->C_List.begin(), this->C_List.end(), [temp](pair<string, int> tar) {return tar.first == temp; });
            if (it == this->C_List.end())
            {
                this->C_List.push_back(make_pair(temp, this->C_List.size() + 1));
                this->Token.push(Token_Code('C', this->C_List.back().second));
            }
            else
            {
                this->Token.push(Token_Code('C', it->second));
            }
            state = 0;
        }
        else                                     //除数字，界符，字母以外的数，在不考虑字符型赋值情况下，均判错
        {                                        //字符
            error = 3;
            errors = c;
            break;
        }
        cout << "("<<this->Token.back().type << "  "<<this->Token.back().code <<")" << " \t";
        
    }
    if (error)
    {
        cout << "词法错误：" << endl;
        switch (error)
        {
        case 1:cout << "标识符定义非法:" << errors<<endl; break;
        case 2:cout << "实数定义非法:" << errors << endl; break;
        case 3:cout << "不明定义:" << errors << endl; break;
        default:break;
        }
        exit(-1);
    }
    file.close();
    return;
}
void Symbol_Table::Print()
{
    system("pause");
    cout << "K:" << endl;
    for (int i = 0; i < this->K_List.size(); i++)
    {
        cout << "K"<<i+1<<":"<<this->K_List[i].first << " \t";
    }
    cout << endl; cout << endl;
    cout << "P:" << endl;
    for (int i = 0; i < this->P_List.size(); i++)
    {
        cout << "P" << i + 1 << ":" << this->P_List[i].first << " \t";
    }
    cout << endl; cout << endl;
    cout << "I:" << endl;
    for (int i = 0; i < this->I_List.size(); i++)
    {
        cout << "I"<<i+1<<":"<<this->I_List[i].first << " \t";
    }
    cout << endl; cout << endl;
    cout << "C:" << endl;
    for (int i = 0; i < this->C_List.size(); i++)
    {
        cout << "C" << i + 1 << ":" << this->C_List[i].first << " \t";
    }
    cout << endl; cout << endl;
    return;
}
