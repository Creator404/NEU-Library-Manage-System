#include "Function/Check_Functions.h"
#include <QStringList>

int Check_A_To_Z_Input(QString s)
{
    int size = s.size();
    int tag = 1;
    for (int i = 0; i < size; i++)
    {
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= '0' && s[i] <= '9')) {
            continue;
        }
        else {
            tag = 0;
            break;
        }
    }
    return tag;
}

int Check_EmailBox_Input(QString s)
{
    if(s == ""){
        return 1;
    }
    int size = s.size();
    if (!(s[0] >= 'a' && s[0] <= 'z') && !(s[0] >= 'A' && s[0] <= 'Z') && !(s[0] >= '0' && s[0] <= '9')) {
        return 0;
    }
    int position = 0;
    for(int i = 1;i < size;i++)
    {
        if (!(s[i] >= 'a' && s[i] <= 'z') && !(s[i] >= 'A' && s[i] <= 'Z') && !(s[i] >= '0' && s[i] <= '9')) {
            if(s[i] == '@'){
                position = i+1;
                break;
            }
            else{
                return 0;
            }
        }
    }
    if(!position){
        return 0;
    }
    QStringList SS = s.split("@");
    if(SS.size() != 2){
        return 0;
    }
    if(SS[1] != "126.com" && SS[1] != "163.com" && SS[1] != "qq.com"){
        return 0;
    }
    return 1;
}

int Combine_Check_Book_Illegal_Input(QString Name,QString Writer,QString Publisher,QString Memo)
{
    if(!Check_other_symbols(Name) || !Check_other_symbols(Writer) || !Check_other_symbols(Publisher) || !Check_other_symbols(Memo)){
        return 0;
    }
    return 1;
}

int Combine_Check_User_Illegal_Input(QString realname,QString mailbox)
{
    if(!Check_other_symbols(realname) || !Check_other_symbols(mailbox)){
        return 0;
    }
    return 1;
}

int Check_other_symbols(QString s)
{
    if(s.contains("'") || s.contains("\"")){
        return 0;
    }
    return 1;
}
