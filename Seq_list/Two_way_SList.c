// #pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef int SLDataType;

typedef struct SListNode
{
    SLDataType Val;
    struct SListNode* Prev;
    struct SListNode* Next;
}SListNode;

void SList_Print(SListNode** Pphead){
    assert(Pphead);
    SListNode* copy_head = *Pphead;
    while (copy_head)
    {
        printf("%d ->",copy_head->Val);
        copy_head =copy_head->Next;
        if(copy_head == *Pphead){
            break;
        }
    }
    printf("NULL\n");
}

SListNode* BuyNewNode(SLDataType val){
    SListNode* NewNode = (SListNode*)malloc(sizeof(SListNode));
    NewNode->Next = NULL;
    NewNode->Prev = NULL;
    NewNode->Val = val;
    return NewNode;
}

void SList_Init(SListNode** Pphead,SLDataType val){
    assert(Pphead);
    SListNode* NewNode = BuyNewNode(val);
    *Pphead = NewNode;
    (*Pphead)->Next = *Pphead;
    (*Pphead)->Prev = *Pphead;
}

//尾插
void PushBack(SListNode** Pphead,SLDataType val){
    assert(Pphead);
    if(*Pphead == NULL){
        SList_Init(Pphead,val);
    }
    else{
        SListNode* NewNode = BuyNewNode(val);
        SListNode* tail = (*Pphead)->Prev;
        tail->Next = NewNode;
        NewNode->Prev = tail;
        NewNode->Next = (*Pphead);
        (*Pphead)->Prev = NewNode;
    }
    return;
}
//头插
void PushFront(SListNode** Pphead,SLDataType val){
    assert(Pphead);
    if(*Pphead == NULL){
        SList_Init(Pphead,val);
    }
    else{
        SListNode* copy_head = *Pphead;
        SListNode* NewNode = BuyNewNode(val);
        NewNode->Prev = copy_head->Prev;
        (copy_head->Prev)->Next = NewNode;
        copy_head->Prev = NewNode;
        NewNode->Next = copy_head;
        *Pphead = NewNode;
    }
    return;
}

//尾删

void PopBack(SListNode** Pphead){
    assert(Pphead);
    if(*Pphead == NULL || (*Pphead)->Next == *Pphead){
        *Pphead  =NULL;
        return;
    }
    else{
        SListNode* tail = (*Pphead)->Prev;
        (tail->Prev)->Next = *Pphead;
        (*Pphead)->Prev = tail->Prev;
        free(tail );
    }
    return;
}

//头删

void PopFront(SListNode** Pphead){
    assert(Pphead); 
    if(*Pphead == NULL || (*Pphead)->Next == *Pphead){
        *Pphead = NULL;
        return;
    }
    else{
        SListNode* copy_head = *Pphead;
        (copy_head->Prev)->Next = copy_head->Next;
        (copy_head->Next)->Prev = copy_head->Prev;
        *Pphead = copy_head->Next;
        free(copy_head);
    }
    return;
}

//任意位置的插入！

void SListInsert(SListNode** Pphead,SLDataType pos,SLDataType val){
    assert(Pphead); 
    if(*Pphead == NULL){
        PushBack(Pphead,pos);
        return;
    }
    SListNode* copy_head = *Pphead;
    while (copy_head->Val != pos)
    {
        copy_head =copy_head->Next;
        if(copy_head == *Pphead){
            return;
        }
    }
    SListNode* NewNode = BuyNewNode(val);
    (copy_head->Next)->Prev = NewNode;
    NewNode->Next = (copy_head->Next);
    copy_head->Next = NewNode;
    NewNode->Prev = copy_head;
    return;
}


void SListDelete(SListNode** Pphead,SLDataType pos){
    assert(Pphead); 
    if(*Pphead == NULL || (*Pphead)->Val == pos){
        PopFront(Pphead);
        return;
    }
    SListNode* copy_head = *Pphead;
    while (copy_head->Val != pos)
    {
        copy_head =copy_head->Next;
        if(copy_head == *Pphead){
            return;
        }
    }
    (copy_head->Prev)->Next = copy_head->Next;
    (copy_head->Next)->Prev = copy_head->Prev;
    free(copy_head);
    return;
}

SListNode* SListFind(SListNode** Pphead,SLDataType val){
    assert(Pphead); 
    if(*Pphead == NULL){
        printf("空链表\n");
        return NULL;
    }
    SListNode* copy_head = *Pphead;
    while (copy_head->Val != val)
    {
        copy_head =copy_head->Next;
        if(copy_head == *Pphead){
            return NULL;
        }
    }
    return copy_head;
}

void SListDestroy(SListNode** Pphead){
    if (Pphead == NULL || *Pphead == NULL) {
        return;
    }

    SListNode* head = *Pphead;
    SListNode* cur = head->Next;

    // 如果只有一个节点
    if (cur == head) {
        free(head);
        *Pphead = NULL;
        return;
    }

    // 有多个节点，循环释放直到回到 head
    while (cur != head) {
        SListNode* next = cur->Next;
        free(cur);
        cur = next;
    }

    free(head);
    *Pphead = NULL;
}

void SListClear(SListNode** Pphead){
    if (Pphead == NULL || *Pphead == NULL) {
        return;
    }

    SListNode* head = *Pphead;
    SListNode* cur = head->Next;
    // 有多个节点，循环释放直到回到 head
    while (cur != head) {
        SListNode* next = cur->Next;
        free(cur);
        cur = next;
    }
    free(head);
    *Pphead = NULL;
}

int main(){
    SListNode* Phead = NULL;
    PushBack(&Phead,1);
    PushBack(&Phead,2);
    PushBack(&Phead,3);
    PushFront(&Phead,0);
    SListInsert(&Phead,3,4);
    SList_Print(&Phead);
    SListDelete(&Phead,0);
    SList_Print(&Phead);
}
