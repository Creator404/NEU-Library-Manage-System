#ifndef CHECK_FUNCTIONS_H
#define CHECK_FUNCTIONS_H

#include <QString>

int Check_A_To_Z_Input(QString s);
int Check_EmailBox_Input(QString s);
int Check_other_symbols(QString s);
int Combine_Check_Book_Illegal_Input(QString Name="",QString Writer="",QString Publisher="",QString Memo="");
int Combine_Check_User_Illegal_Input(QString realname,QString mailbox);

#endif // CHECK_FUNCTIONS_H
