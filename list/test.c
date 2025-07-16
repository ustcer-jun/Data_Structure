#include "Slist.h"


int main(){
    SListNode* Start = NULL;
    SListPushBack(&Start,1);
    SListPushBack(&Start,2);
    SListPushBack(&Start,3);
    // SListPushFront(&Start,0);
    //SListPopBack(&Start);
    // SListPopFront(&Start);
    SListInsert(&Start,1,0);
    SListFind(&Start,2);
    SListPrint(Start);
}