#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include <string.h>

typedef int HeapDataType;

typedef struct Heap
{
    HeapDataType* arr;
    int size;
    int capacity;
}Heap;

void Swap(HeapDataType* p1,HeapDataType* p2){
    HeapDataType tmp = *p1;
    *p1 = *p2; 
    *p2 = tmp;
}

void AdjustDown(HeapDataType* arr,int n,int root){ //向下调整-->实现小根堆
    assert(arr);
    int parent = root;
    int Child  = 2*root+1;
    while (Child<n)//最后一个叶节点是我们循环终止条件。
    {   
        if(Child+1<n && arr[Child]>arr[Child+1]){
            Child++;
        }

        if(arr[Child]<arr[parent]){
            Swap(&arr[parent],&arr[Child]);
            parent = Child;
            Child = 2*parent+1;
        }
        else{
            break;
        }
    }
}

Heap* Heap_Init(HeapDataType* arr,size_t n){
    assert(arr);
    Heap* pheap =(Heap*)malloc(sizeof(Heap));
     pheap->arr = (HeapDataType*)malloc(sizeof(HeapDataType) * n);
    memcpy(pheap->arr,arr,sizeof(HeapDataType)*n);
    // pheap->arr = arr;
    pheap->capacity = n;
    pheap->size = n;
    // 构建堆；大根堆，小根堆；
    int root = ((n-1-1)/2);
    while (root>=0)
    {
        AdjustDown(pheap->arr,pheap->size,root);
        root--;
    }
    return pheap;
}

void Heap_Sort(Heap* pheap){
    assert(pheap); 
    // 初始化之后已经是小根堆了
    // 降序排序 // 排降序建小堆，升序要建大堆。
    for (size_t end = pheap->size - 1; end > 0; end--) {
        Swap(&pheap->arr[0], &pheap->arr[end]);       // 最小值放末尾
        AdjustDown(pheap->arr, end, 0);               // 重新堆化（注意 end 是新长度）
    }
}

void AdjustUp(HeapDataType* arr,int leaf){
    int Child = leaf;
    int parent = (Child-1)/2;
    //新加入元素，需要重新构建堆
    while (Child>0)
    {
        if(arr[Child]<arr[parent]){
            Swap(&arr[Child],&arr[parent]);
            Child = parent;
            parent = (Child-1)/2;
        }
        else{
            break;
        }
    }
    
}

void HeapPush(Heap* pheap,HeapDataType Val){
    assert(pheap);
    if(pheap->size == pheap->capacity){
        pheap->capacity *=2;
        HeapDataType* tmp = (HeapDataType*) realloc(pheap->arr,sizeof(HeapDataType)*pheap->capacity);
        pheap->arr = tmp; 
    }
    pheap->arr[pheap->size++] = Val;
    //向上调整
    AdjustUp(pheap->arr,pheap->size-1);
}

void HeapPop (Heap* pheap){ //删除堆顶的数据
    assert(pheap);
    //交换堆顶和堆底的元素，再进行删除
    Swap(&pheap->arr[0],&pheap->arr[pheap->size-1]);\
    pheap->size--;
    //再重新向下调整
    AdjustDown(pheap->arr,pheap->size,0);
}
//取出前k个堆顶的元素
HeapDataType HeapTop(){

}


void HeapDestroy(Heap* pheap){
    assert(pheap);
    free(pheap->arr);
    pheap->arr = NULL;
    free(pheap);
    pheap = NULL;
}

int main(){
    int arr[] = {66, 96, 88, 78, 45, 100, 62, 34, 28, 19, 83};
    Heap* my_heap = Heap_Init(arr,11);
    for(int i = 0;i<11;i++){
        printf("%d ",my_heap->arr[i]);
    }
    printf("\n");
    // Heap_Sort(my_heap);
    // for(int i = 0;i<my_heap->size;i++){
    //     printf("%d ",my_heap->arr[i]);
    // }
    //注意排序和堆插入元素无法共同使用，你只能做其中一部分
    //因为排序后的可能不再是堆结构了
    HeapPush(my_heap,55);
    printf("\n");
    for(int i = 0;i<my_heap->size;i++){
        printf("%d ",my_heap->arr[i]);
    }
}



