#include "User.h"
#include <cstdio>
#include <cstdlib>

void Initial_User_LinkList(User* &Head)
{
    Head = new User(QString(""), QString(""),QString(""), 0);
}
