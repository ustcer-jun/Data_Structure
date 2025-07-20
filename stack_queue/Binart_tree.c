#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>



typedef char BTreeDataType;

typedef struct BTreeNode
{
    BTreeDataType _data;
    struct BTreeNode* _left;
    struct BTreeNode* _right;
}BTreeNode;

typedef BTreeNode* QueueDataType;
typedef struct Queue
{
    QueueDataType btnode;
    struct Queue* next;

}Queue;

typedef struct my_Queue{
    Queue* _head;
    Queue* _tail;
}my_Queue;

my_Queue* Queue_Init(){
    my_Queue* pq = (my_Queue*)malloc(sizeof(my_Queue));
    pq->_head = pq->_tail = NULL;
    return pq;
}

void QueueDestroy(my_Queue* pq){
    assert(pq);
    Queue* Cur = pq->_head;
    while (Cur)
    {
        Queue* Del = Cur;
        Cur = Cur->next;
        free(Del);
    }
    pq->_head = pq->_tail = NULL;
    return;
}

void QueuePush(my_Queue* pq,QueueDataType _val){
    assert(pq);
    Queue* NewNode = (Queue*)malloc(sizeof(Queue));
    NewNode->btnode = _val;
    NewNode->next = NULL;
    if(pq->_head == NULL){
        pq->_tail = NewNode;
        pq->_head = NewNode;  
    }
    else{
        pq->_tail->next = NewNode;
        pq->_tail = NewNode;
    }
}

void QueuePop(my_Queue* pq){
    assert(pq);
    if(pq->_head == NULL){
        return;
    }
    else{
        Queue* Cur = pq->_head;
        pq->_head = (pq->_head)->next;
        free(Cur);
    }
    if(pq->_head == NULL){
        pq->_tail = NULL;
    }
    return;
}


QueueDataType QueueFront(my_Queue* pq){
    assert(pq);
    if(pq->_head){
        return pq->_head->btnode;
    }
    return NULL;
}

bool IsQueueEmpty(my_Queue* pq){
    assert(pq);
    return !pq->_head;
}




BTreeNode* CreateTree(BTreeDataType* str,int* pi){
    if(*str == '\0'){
        return NULL;
    }
    if(str[*pi] == '#'){
        (*pi)++;
        return NULL;
    }
    BTreeNode* root = (BTreeNode*)malloc(sizeof(BTreeNode));
    root->_data = str[*pi];
    (*pi)++;
    root->_left = CreateTree(str,pi);
    root->_right = CreateTree(str,pi);
    return root;
}
BTreeNode* BuyNewNode(BTreeDataType val){
    BTreeNode* NewNode = (BTreeNode*)malloc(sizeof(BTreeNode));
    NewNode->_data = val;
    NewNode->_left = NULL;
    NewNode->_right = NULL;
    return NewNode;
}

void BTree_Destroy(BTreeNode* root){
    if(!root){
        return ;
    }
    BTree_Destroy(root->_left);
    BTree_Destroy(root->_right);
    free(root);
    return;
}

int BTreeSize(BTreeNode* root){
    if(!root){
        return 0;
    }
    return 1+ BTreeSize(root->_left)+BTreeSize(root->_right);
}

int BTreeLeafSize(BTreeNode* root){
    if(!root){
        return 0;
    }
    if(!(root->_left) && !(root->_right)){
        return 1;
    }
    return (BTreeLeafSize(root->_left)+BTreeLeafSize(root->_right));
}
int BTreeLevelKSize(BTreeNode* root,int k){
    if(!root){
        return 0;
    }
    k--;
    if(k == 0){
        return 1;
    }
    return (BTreeLevelKSize(root->_left,k)+BTreeLevelKSize(root->_right,k));
}

BTreeNode* BTreeFind(BTreeNode* root,BTreeDataType _val){
    if(!root){
        return NULL;
    }
    if(root->_data == _val){
        return root;
    }
    BTreeNode* node = BTreeFind(root->_left,_val);
    if(node){
        return node;
    }
    node = BTreeFind(root->_right,_val);
    if(node){
        return node;
    }
    return NULL;
}

void PreOrder(BTreeNode* root){
    if(!root){
        printf("NULL");
        return;
    }
    printf("%c ",root->_data);
    PreOrder(root->_left);
    PreOrder(root->_right);
    return;
}

void InOrder(BTreeNode* root){
    if(!root){
        printf("NULL");
        return;
    }
    InOrder(root->_left);
    printf("%c ",root->_data);
    InOrder(root->_right);
    return;
}

void PostOrder(BTreeNode* root){
    if(!root){
        printf("NULL");
        return;
    }
    PostOrder(root->_left);
    PostOrder(root->_right);
    printf("%c ",root->_data);
    return;
}

void BTree_LevelOrder(BTreeNode* root){
    if(!root){
        printf("NULL");
        return;
    }
    my_Queue* BTqueue = Queue_Init();
    QueuePush(BTqueue,root);
    while (!IsQueueEmpty(BTqueue))
    {
        QueueDataType Front = QueueFront(BTqueue);
        printf("%c ",Front->_data);
        QueuePop(BTqueue);
        if(Front->_left){
            QueuePush(BTqueue,Front->_left);
        };
        if(Front->_right){
            QueuePush(BTqueue,Front->_right);
        }
    }
    QueueDestroy(BTqueue);
    BTqueue = NULL;
    return;
}

bool IsCompleteTree(BTreeNode* root){
    if(!root){
        return true;
    }
    my_Queue* BTqueue = Queue_Init();
    QueuePush(BTqueue,root);
    bool null_seen = false;
    while (!IsQueueEmpty(BTqueue))
    {
        QueueDataType Front = QueueFront(BTqueue);
        QueuePop(BTqueue);
        if(Front == NULL){
            null_seen = true;
        }
        else{
            if(null_seen){
                QueueDestroy(BTqueue);
                BTqueue = NULL;
                return false;
            }
            QueuePush(BTqueue,Front->_left);
            QueuePush(BTqueue,Front->_right); 
        }
    }
    QueueDestroy(BTqueue);
    BTqueue = NULL;
    return true;
}

int main(){
    char str[100] = {0};
    scanf("%s",str);
    int i = 0;
    BTreeNode* root = CreateTree(str,&i);
    PreOrder(root);
    printf("\n");
    printf("%d ",BTreeSize(root));
    printf("%d ",BTreeLeafSize(root));
    printf("%d ",BTreeLevelKSize(root,3));
    BTreeNode* target = BTreeFind(root,'D');
    printf("%c ",target->_data);
    BTree_LevelOrder(root);
    if(IsCompleteTree(root)){
        printf("yes\n");
    }
    else{
        printf("No\n");
    }
}

