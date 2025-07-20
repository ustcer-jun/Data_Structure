#include "queue.h"

//队列的初始化
void QueueInit(Queue* pq){
    assert(pq);
    pq->_head = pq->_tail = NULL;
}
//队列的摧毁
void QueueDestroy(Queue* pq){
    assert(pq);
    QueueNode* Cur = pq->_head;
    while(Cur) 
    {
        QueueNode* del = Cur;
        Cur = Cur->next;
        free(del);
    }
    pq->_head = pq->_tail = NULL; 
}

//队列插入元素
void QueuePush(Queue* pq, QeDataType x){
    assert(pq);
    QueueNode*NewNode = (QueueNode*)malloc(sizeof(QueueNode));
    if(NewNode == NULL){
        perror("malloc");
        exit(-1);
    }
    NewNode->next=NULL;
    NewNode->_data = x;
    if(pq->_head == NULL){
        pq->_head = pq->_tail = NewNode;
    }
    else{
        pq->_tail->next = NewNode;
        pq->_tail = NewNode;
    }
}
//队列删除元素
void QueuePop(Queue* pq){
    assert(pq);
    if(pq->_head == NULL){
        printf("队列为空\n");
        exit(-1);
    }
    QueueNode* head_next = pq->_head->next;
    free(pq->_head);
    pq->_head = head_next;
    if(pq->_head == NULL){
        pq->_tail = NULL;
    }
}
//取出队头数据
QeDataType QueueFront(Queue* pq){
    assert(pq);
    if(pq->_head ==NULL){
        return NULL;
    }
    return pq->_head->_data;
}
//取出队尾数据
QeDataType QueueBack(Queue* pq){
    assert(pq);
    if(pq->_tail ==NULL){
        return NULL;
    }
    return pq->_tail->_data;
}
//检查队列是否为空，返回队列大小
int QueueEmpty(Queue* pq){
    assert(pq);
    return !pq->_head;
}
int QueueSize(Queue* pq){
    assert(pq);
    if(pq == NULL){
        return 0;
    }
    QueueNode* Cur = pq->_head;
    int count =0;
    while(Cur || Cur != pq->_tail) 
    {
        count++;
        Cur = Cur->next;
    }
    return count;
}