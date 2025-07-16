#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

//利用单向链表的形式实现栈
typedef int QeDataType;


typedef struct QueueNode
{
    QeDataType _data;
    struct QueueNode* next;
}QueueNode;
//存储队列的头，尾指针用于插入和删除队列元素
typedef struct Queue
{
    QueueNode* _head;
    QueueNode* _tail;
}Queue;

//队列的初始化
void QueueInit(Queue* pq);
//队列的摧毁
void QueueDestroy(Queue* pq);
//队列插入元素
void QueuePush(Queue* pq, QeDataType x);
//队列删除元素
void QueuePop(Queue* pq);
//取出队头数据
QeDataType QueueFront(Queue* pq);
//取出队尾数据
QeDataType QueueBack(Queue* pq);

int QueueEmpty(Queue* pq);
int QueueSize(Queue* pq);