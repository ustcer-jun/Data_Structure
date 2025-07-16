#include "stack.h"


void StackInit(Stack* pst){
    assert(pst);
    // pst->_val = NULL;
    // pst->_capacity = 0;
    // pst->_size = 0;
    pst->_val = (STDataType*) malloc(Ini_capacity*sizeof(STDataType));
    if(pst->_val == NULL){
        perror("malloc");
        exit(-1);
    }
    pst->_size = 0;
    pst->_capacity =Ini_capacity;

}
void StackDestroy(Stack* pst){
    assert(pst);
    free(pst->_val);
    pst->_val = NULL;
    pst->_size =pst->_capacity = 0;
}
// 入栈
void StackPush(Stack* pst,STDataType Val){
    assert(pst);
    if(pst->_size == pst->_capacity){
        //增容
        pst->_capacity = 2*pst->_capacity;
        STDataType* tmp = realloc(pst->_val,pst->_capacity*sizeof(STDataType));
        pst->_val = tmp;
        tmp = NULL;
    }
    pst->_val[pst->_size] = Val;
    pst->_size++; 
}
// 出栈
void StackPop(Stack* pst){
    assert(pst && pst->_size > 0);
    --pst->_size;
}
//获取数据个数
int StackSize(Stack* pst){
    assert(pst);
    return(pst->_size);
}
//返回1 是空，返回0是非空
int StackEmpty(Stack* pst){
    assert(pst);
    // return pst->_size == 0 ? 1 : 0;
    return !pst->_size;
}
//获取栈顶数据 
STDataType StackTop(Stack* pst){
    assert(pst && pst->_size>0);
    return pst->_val[pst->_size-1];
}