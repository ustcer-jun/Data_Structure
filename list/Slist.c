#include "Slist.h"


void SListPrint(SListNode* Phead){
    SListNode* Cur = Phead;
    while (Cur != NULL)
    {
        printf("%d ->",Cur->data);
        Cur = Cur->next;
    }
    printf("NULL\n");
}

//新增链表的节点
SListNode* BuySListNode(SLDataType Val){
    SListNode* newNode = (SListNode*) malloc(sizeof(SListNode));
    newNode->data = Val;
    newNode->next = NULL;
    return newNode;
}

 //尾插
void SListPushBack(SListNode** Pphead,SLDataType Val){
    SListNode* Cur = *Pphead;
    if(*Pphead ==NULL){  //注意当链表为空时你需要对头指针修改指向下一个链表，这个时候头指针没有下一个链表的地址
        SListNode* newNode = BuySListNode(Val);
        *Pphead = newNode;
    }
    // 
    else{                //当链表不为空时，头指针不需要改变内容。
        while (Cur->next!= NULL)
        {
            Cur = Cur->next;
        }
        SListNode* newNode = BuySListNode(Val);

        Cur->next =  newNode;
    }
    return;
} 
// 头插
void SListPushFront(SListNode** Pphead,SLDataType Val){
    SListNode* Cur = *Pphead;
    SListNode* newNode = BuySListNode(Val);
    if(*Pphead  == NULL){
        *Pphead = newNode;
    }
    else{
        newNode->next = Cur;
        *Pphead = newNode;
    }
    return;
}


//尾删
void SListPopBack(SListNode** Pphead){
    SListNode* Cur = *Pphead;
    if(*Pphead == NULL){
        printf("空链表！");
        return;
    }
    else if((Cur->next) == NULL)
    {
        free(* Pphead);
        *Pphead = NULL;
        return;
    }
    else{
        SListNode* Prev = NULL;
        while ((Cur->next) != NULL)
        {
            Prev = Cur;
            Cur = Cur->next;
        }
        free(Cur);
        Prev->next = NULL;     
    }   
    return;
} 
// 头删
void SListPopFront(SListNode** Pphead){
    if(*Pphead == NULL){
        printf("链表为空");
    }
    SListNode* Cur = *Pphead;
    *Pphead = Cur->next;
    free(Cur);
}

// 任意位置插入
void SListInsert(SListNode** Pphead, int pos, SLDataType Val) {
    assert(Pphead && pos > 0);
    
    SListNode* newNode = BuySListNode(Val);

    // 插入到头部
    if (pos == 1) {
        newNode->next = *Pphead;
        *Pphead = newNode;
        return;
    }

    SListNode* Cur = *Pphead;
    int count = 1;

    // 找到插入位置前一个节点
    while (Cur != NULL && count < pos - 1) {
        Cur = Cur->next;
        count++;
    }

    // 如果位置超出链表长度
    if (Cur == NULL) {
        printf("插入位置无效！\n");
        free(newNode);
        return;
    }

    newNode->next = Cur->next;
    Cur->next = newNode;
}

// 任意位置的删除
void SListDelete(SListNode** Pphead, int pos) {
    assert(Pphead && pos > 0);
    if (*Pphead == NULL) {
        printf("链表为空\n");
        return;
    }

    if (pos == 1) {
        SListNode* Cur = *Pphead;
        *Pphead = (*Pphead)->next; //先改变指针指向，再进行内存释放
        free(Cur);
        return;
    }

    SListNode* Prev = *Pphead;
    int count = 1;
    while (Prev != NULL && count < pos - 1) {
        Prev = Prev->next;
        count++;
    }

    if (Prev == NULL || Prev->next == NULL) {
        printf("无效输入！\n");
        return;
    }

    SListNode* Del = Prev->next;
    Prev->next = Del->next;
    free(Del);
}

//链表的元素访问
// void SListFind(SListNode** Pphead,int pos){
//     assert(Pphead && pos);
//     int num = pos-1;
//     SListNode* Cur = *Pphead;
//     while (num-- && Cur != NULL)
//     {
//         Cur = Cur->next;
//     }
//     if(Cur == NULL){
//         printf("无效输入！\n");
//         return;
//     }
//     printf("第%d个元素是 %d\n",pos,Cur->data);
// }
// SListNode* SListFind(SListNode** Pphead,SLDataType Val){
//     assert(Pphead);
//     SListNode* Cur = *Pphead;
//     if(*Pphead == NULL){
//         printf("空链表\n");
//         return NULL;
//     }
//     while (Cur!=NULL)
//     {
//         if(Cur->data == Val){
//             return Cur;
//         }
//         Cur = Cur->next;
//     }
//     return NULL;
// }