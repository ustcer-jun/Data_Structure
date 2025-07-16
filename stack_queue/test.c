#include "stack.h"

void TestStack(){
    Stack ST;
    StackInit(&ST);
    StackPush(&ST,0);
    StackPush(&ST,1);
    StackPush(&ST,2);
    printf("%d\n",StackTop(&ST));
    StackPop(&ST);
    printf("%d\n",StackTop(&ST));
    StackDestroy(&ST);
}
int main(){
    TestStack();
}