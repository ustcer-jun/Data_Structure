#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include <string.h>


#define Init_Capcity 5
typedef char BTDataType;
typedef struct BNTreeNode
{
    BTDataType _data;
    struct BNTreeNode* left_child;
    struct BNTreeNode* right_child;
}BNTreeNode;

BNTreeNode* BNTreeNode_Init(){
    BNTreeNode* pt = (BNTreeNode*)malloc(sizeof(BNTreeNode));
    pt ->left_child =NULL;
    pt->right_child = NULL;
    return pt;
}
BNTreeNode* BuyTreeNode(BTDataType val){
    BNTreeNode* NewNode = (BNTreeNode*)malloc(sizeof(BNTreeNode));
    NewNode->_data = val;
    NewNode->left_child = NULL;
    NewNode->right_child = NULL;
    return NewNode;
}

void PrevOrder(BNTreeNode* root){
    if(root == NULL){
        printf("NULL ");
        return;
    }
    printf("%c  ",root->_data);
    PrevOrder(root->left_child);
    PrevOrder(root->right_child);
}
void InOrder(BNTreeNode* root){
    if(root == NULL){
        printf("NULL ");
        return;
    }
    InOrder(root->left_child);
    printf("%c  ",root->_data);
    InOrder(root->right_child);
}
void PostOrder(BNTreeNode* root){
    if(root == NULL){
        printf("NULL ");
        return;
    }
    PostOrder(root->left_child);
    PostOrder(root->right_child);
    printf("%c  ",root->_data);
}
void TreeSize(BNTreeNode* root,int* psize){
    if(root == NULL){
        return;
    }
    //static int size = 0; //静态变量只有当前文件能使用
    (*psize)++;
    TreeSize(root->left_child,psize);
    TreeSize(root->right_child,psize);
}
int TreeSize(BNTreeNode* root){
    if(root == NULL){
        return 0;
    }
    else{
        return 1+TreeSize(root->left_child)+TreeSize(root->right_child);
    }
}

int TreeLeafSize(BNTreeNode* root){
    if(root == NULL){
        return 0;
    }
    if(root->left_child == NULL && root->right_child == NULL){
        return 1;
    }
    return TreeLeafSize(root->left_child)+TreeLeafSize(root->right_child);
}
int TreeDepth(BNTreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    int left_depth = TreeDepth(root->left_child);
    int right_depth = TreeDepth(root->right_child);
    return 1 + (left_depth > right_depth ? left_depth : right_depth);
}


int main(){
    BNTreeNode* Root = BNTreeNode_Init();
    Root->_data = 'A';
    Root->left_child = BuyTreeNode('B');
    Root->right_child = BuyTreeNode('C');
    (Root->left_child)->left_child = BuyTreeNode('D');
    (Root->left_child)->right_child = BuyTreeNode('E');
    (Root->right_child)->left_child = BuyTreeNode('F');
    // PrevOrder(Root);
    // printf("\n");
    // InOrder(Root);
    // printf("\n");
    // PostOrder(Root);
    // printf("\n");
    int size =0;
    // TreeSize(Root, &size);
    printf("%d\n",TreeSize(Root));
    printf("%d\n",TreeLeafSize(Root));
    printf("%d\n",TreeDepth(Root));
}
