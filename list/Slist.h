#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef int SLDataType; 
typedef struct SListNode
{
    SLDataType data;
    struct SListNode* next;
}SList,SListNode;


void SListPrint(SListNode* Phead);

//增删查改

void SListPushBack(SListNode** Phead,SLDataType Val); //尾插
void SListPushFront(SListNode** Pphead,SLDataType Val); // 头插

void SListPopBack(SListNode** Pphead);
void SListPopFront(SListNode** Pphead);

// 任意位置插入和删除
void SListInsert(SListNode** Pphead,int pos,SLDataType Val);
void SListDelete(SListNode** Pphead,int pos);
//链表的元素访问
// void SListFind(SListNode** Pphead,int pos);
SListNode* SListFind(SListNode** Pphead,SLDataType Val);