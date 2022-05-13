#include "Free_Function.h"

void Delete_User_LinkList(User* &Head)
{
    User* Previous = Head;
    User* Instance = Head->next;
    delete Previous;
    while(Instance != NULL){
        Previous = Instance;
        Instance = Instance->next;
        delete Previous;
    }
}

void Delete_Book_LinkList(Book* &Head)
{
    Book* Previous = Head;
    Book* Instance = Head->next;
    delete Previous;
    while(Instance != NULL){
        Previous = Instance;
        Instance = Instance->next;
        delete Previous;
    }
}
