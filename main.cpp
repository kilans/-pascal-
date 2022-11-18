#include"É¨ÃèÆ÷.h"
#include"syntax.h"
#include"º¯ÊıÓïÑÔ.h"
int main()
{
    Symbol_Table* table = new Symbol_Table();
    table->Table_Main();
    syntax* Lau = new syntax(table);
    Lau->Main(table);
    Fun_Lau* funl = new Fun_Lau(table, &Lau->trans->quartion);
    funl->Main();
    delete table;
    delete Lau;
    delete funl;
    system("pause");
    return 0;
}
