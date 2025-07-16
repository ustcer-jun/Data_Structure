#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

//利用数组的形式实现栈

typedef int STDataType;
#define Ini_capacity 5

typedef struct Stack
{
    int* _val;
    int _size;
    int _capacity;
}Stack;

void StackInit(Stack* pst);
void StackDestroy(Stack* pst);
// 入栈
void StackPush(Stack* pst,STDataType Val);
// 出栈
void StackPop(Stack* pst);
//获取数据个数
int StackSize(Stack* pst);
//返回1 是空，返回0是非空
int StackEmpty(Stack* pst);
//获取栈顶数据 
STDataType StackTop(Stack* pst);
