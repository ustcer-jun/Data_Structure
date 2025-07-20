#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "queue.h"

typedef char BTDataType;

typedef struct BTNode
{
    BTDataType _data;
    struct BTNode* _left;
    struct BTNode* _right;
}BTNode;


//通过前序遍历的数组构建二叉树
BTNode* CreateBTree(BTDataType* val,int* pi){
    if(val[*pi] == '\0'){
        return  NULL;
    }
    if(val[*pi] =='#'){
        (*pi)++;
        return NULL;
    }
    BTNode* root = (BTNode*)malloc(sizeof(BTNode));
    root->_data = val[*pi];
    (*pi)++;
    root->_left = CreateBTree(val,pi);
    root->_right = CreateBTree(val,pi);
    return root;
    
}
void BTree_Destroy(BTNode** root){
    assert(root);
    if(!*root){
        return;
    }
    else{
        BTree_Destroy(&(*root)->_left);
        BTree_Destroy(&(*root)->_right);
        free(*root);
        *root = NULL;
    }
    return;
}

int BTree_Size(BTNode* root){
    if(!root){
        return 0;
    }
    return 1+(BTree_Size(root->_left)+BTree_Size(root->_right));
}

int BTree_LeafSize(BTNode* root){
    if(!root){
        return 0;
    }
    if(!root->_left && !root->_right){
        return 1;
    }
    return (BTree_LeafSize(root->_left)+BTree_LeafSize(root->_right));
}

int BTree_LevelKSize(BTNode* root,int k){
    if(!root){
        return 0;
    }
    k--;
    if(k == 0 && root){
        return 1;
    }
    return BTree_LevelKSize(root->_left,k) + BTree_LevelKSize(root->_right,k);
}


BTNode* BTreeFind(BTNode* root, BTDataType x){
    if(!root){
        return NULL;
    }
    if(root->_data == x){
        return root;
    }
    BTNode* node = BTreeFind(root->_left,x);
    if(node){
        return node;
    }
    node = BTreeFind(root->_right,x);
    if(node){
        return node;
    }
    return NULL;
}

// 前序遍历？
void BTree_PreOrder(BTNode* root){
    if(!root){
        printf("NULL");
        return;
    }
    printf("%c ",root->_data);
    BTree_PreOrder(root->_left);
    BTree_PreOrder(root->_right);
    return;
}

// 中序遍历？
void BTree_InOrder(BTNode* root){
    if(!root){
        printf("NULL");
        return;
    }
    BTree_InOrder(root->_left);
    printf("%c ",root->_data);
    BTree_InOrder(root->_right);
    return;
}

// 后序遍历？
void BTree_PostOrder(BTNode* root){
    if(!root){
        printf("NULL");
        return;
    }
    BTree_PostOrder(root->_left);
    BTree_PostOrder(root->_right);
    printf("%c ",root->_data);
    return;
}
//层序遍历 利用队列的性质
void BTree_LevelOrder(BTNode* root){
    if(!root){
        printf("NULL");
        return;
    }
    Queue Q;
    QueueInit(&Q);
    QueuePush(&Q,root);
    while (!QueueEmpty(&Q))
    {
       BTNode*Front = QueueFront(&Q);
       QueuePop(&Q);
       printf("%c ",Front->_data);
       if(Front->_left){
            QueuePush(&Q,Front->_left);
       }
       if(Front->_right){
            QueuePush(&Q,Front->_right);
       }
    }
    QueueDestroy(&Q);
    printf("\n");
}

bool BTreeComplete(BTNode* root){
    if(!root){
        return true;
    }
    Queue Q;
    QueueInit(&Q);
    QueuePush(&Q,root);
    bool null_seen = false;
    while (!QueueEmpty(&Q))
    {
       BTNode*Front = QueueFront(&Q);
       QueuePop(&Q);
       if(!Front){
            null_seen = true;
       }
       else{
            if(null_seen){
                QueueDestroy(&Q);
                return false;
            }
            QueuePush(&Q,Front->_left);
            QueuePush(&Q,Front->_right);
       }
    }
    QueueDestroy(&Q);
    return true;
}

int main(){
    char str[100] = {0};
    scanf("%s",str);
    int i =0;
    BTNode* Root = CreateBTree(str,&i);
    // BTree_LevelOrder(Root);
    if(BTreeComplete(Root)){
        printf("Yes\n");
    }
    else{
        printf("No\n");
    }
}