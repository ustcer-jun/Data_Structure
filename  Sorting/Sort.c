#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

void Swap(int* p,int* q){
    assert(p&&q);
    int tmp = *p;
    *p = *q;
    *q = tmp;
    return;
}

void Bubble_sort(int* arr,int size){
    assert(arr);
    int end = size-1;
    int flag = 0;
    for (int i = 0;i<end;i++){
        for(int j = 0;j<end-i;j++){
            if(arr[j]>arr[j+1]){
            Swap(&arr[j],&arr[j+1]);
            flag = 1;
            }
        }
        if(flag == 0){
            break;
        }
        
    }
    return;
}
void Insert_Sort(int* arr,int size){
    assert(arr);
    for (int end = 1;end<size;end++){
        for(int j = end-1;j>=0;j--){
            if(arr[j+1]<arr[j]){
                Swap(&arr[j],&arr[j+1]);
            }
            else{
                break;
            }
        }
    }
}
// void Insert_Sort(int* arr, int size) {
//     assert(arr);
//     for (int i = 1; i < size; i++) {
//         int key = arr[i];         // 记录待插入元素
//         int j = i - 1;

//         // 向前寻找插入位置，同时右移元素
//         while (j >= 0 && arr[j] > key) {
//             arr[j + 1] = arr[j];  // 后移元素
//             j--;
//         }

//         arr[j + 1] = key;         // 插入元素
//     }
// }

void Shell_Sort(int* arr,int size){
    assert(arr);
    int gap = size;
    while(gap > 1)
    {
        gap = gap/3+1;
        for (int end = gap;end<size;end++){
            int j = end-gap;
            int tmp = arr[end];
            while (j>=0 && arr[j]>tmp)
            {
                arr[j+gap] = arr[j];
                j -= gap;
            }
            arr[j+gap] = tmp;
        }  
    }
}

// void Shell_Sort(int* arr, int size){
//     assert(arr);
//     int gap = size;
//     while (gap > 1){
//         gap = gap / 3 + 1;
//         for (int i = gap; i < size; ++i){
//             int temp = arr[i];
//             int j = i;
//             while (j >= gap && arr[j - gap] > temp){
//                 arr[j] = arr[j - gap];
//                 j -= gap;
//             }
//             arr[j] = temp;
//         }
//     }
// }

//选择排序
void Select_Sort(int* arr,int size){
    assert(arr);
    int min = 0;int max = 0;
    int index_min =0; int index_max = 0;
    for(int i = 0;i<size/2;i++)
    {
        min = arr[i];
        max = arr[size-i-1];
        index_min = i;index_max = size-i-1;
        for(int j= i;j<size-i;j++){
            if(arr[j]<min){
                min = arr[j];
                index_min = j;
            }
            if(arr[j]>max){
                max = arr[j];
                index_max = j;
            }

        }
        // 判断最大值的位置是否为所选位置
        if(index_max != size-i-1){
            arr[index_max] = arr[size-i-1]; //index_min == size-i-1
            arr[size-i-1] = max;
            //防止交换最大值时，把最小的值位置换走了
            if(index_min == size-i-1){
                index_min = index_max;
            }
        }
        if(index_min!=i){
            arr[index_min] = arr[i];
            arr[i] = min;
        }
    }
}

void AdjustDown(int* arr,int n,int root){
    assert(arr);
    int parent = root;
    int child = 2*parent+1;
    int tmp = 0;
    while (child<n)
    {
        if(child+1<n && arr[child+1]>arr[child]){
            child++;
        }
        if(arr[child]>arr[parent]){
            tmp = arr[child];
            arr[child] = arr[parent];
            arr[parent] = tmp;
            parent = child;
            child = 2*parent+1;
        }
        else{
            break;
        }
    }
    return;
}

//堆排序 --> 升序排大根堆，降序排小根堆
void Heap_sort(int* arr,int size){
    assert(arr);
    for(int i = (size-1-1)/2;i>=0;i--){
        AdjustDown(arr,size,i);
    }
    int end = size;
    while (end>1)
    {
        int tmp = arr[0];
        arr[0] =arr[end-1];
        arr[end-1] = tmp;
        AdjustDown(arr,end-1,0);
    }

}

//三数取中优化
int get_midindex(int*arr,int left,int right){
    assert(arr);
    int mid = left+(right-left)/2;
    if(arr[left]>= arr[mid] && arr[left]<=arr[right] || arr[left]<= arr[mid] && arr[left]>=arr[right]){
        return left;
    }
    else if(arr[mid]>= arr[left] && arr[mid]<=arr[right] || arr[mid]<= arr[left] && arr[mid]>=arr[right]){
        return mid;
    }
    else{
        return right;
    }

}


int PartSort(int* arr,int left,int right){
    assert(arr);
    int mid_index = get_midindex(arr,left,right);
    Swap(&arr[mid_index],&arr[right]);
    int key_index = right;
    int begin = left;
    int end = right;
    while (begin< end)
    { 
        while(begin < end && arr[begin] <= arr[key_index]){
            begin++;
        }
        while(begin < end && arr[end] >= arr[key_index]){
            end--;
        }

          Swap(&arr[begin],&arr[end]);
    }
    Swap(&arr[key_index],&arr[begin]);
    return begin;
}

int PartSort2(int* arr,int left,int right){
    assert(arr);
    int mid_index = get_midindex(arr,left,right);
    Swap(&arr[mid_index],&arr[right]);
    int key = arr[right];
    int begin = left;
    int end = right;
    while (begin< end)
    { 
        while(begin < end && arr[begin] <= key){
            begin++;
        }
        arr[end] = arr[begin];
        while(begin < end && arr[end] >= key){
            end--;
        }
        arr[begin]= arr[end];
    }
    arr[begin] = key;
    return begin;
}

int PartSort3(int* arr,int left,int right){
    assert(arr);
    int mid_index = get_midindex(arr,left,right);
    Swap(&arr[mid_index],&arr[right]);
    int key = arr[right];
    int prev = left-1;
    for(int cur = left;cur<right;++cur){
        if(arr[cur]<key){
            prev++;
            Swap(&arr[cur],&arr[prev]);
        }
    }
    // while (cur< right){
    //     if(arr[cur]<key)
    //     {
    //         prev++;
    //         Swap(&arr[cur],&arr[prev]);
    //     }
    //     cur++;
    // }
    prev++;
    Swap(&arr[right],&arr[prev]);
    return prev;
}


void QuickSort(int* arr,int left,int right){
    assert(arr);
    if(left>=right){
        return;
    }

    ///小序列优化，当小序列我们不需要开辟栈，不使用快排。
    //小序列可以使用插入排序
    if((right-left+1)>15){
        int div = PartSort3(arr,left,right);
        QuickSort(arr,left,div-1);
        QuickSort(arr,div+1,right);
    }
    else{
        Insert_Sort(arr+left,right-left+1);
    }
}
void QuickSort_stack(int* arr,int left,int right){
    assert(arr);
    if(left>=right){
        return;
    }
    int size = right+1;
    int* stack  = (int*)malloc(2*size*sizeof(int));//建立栈
    int top = 0;
    //先入左边，再入右边
    stack[top++] = left;
    stack[top++] = right;
    while (top>0)
    {
        // 先进后出，所以先出右边
        int right  = stack[--top]; //注意 -- 的用法
        int left  = stack[--top];
        if(left<right){
            int div = PartSort2(arr,left,right); //利用分而治之的思想
            if(left<div-1){
                stack[top++] = left;
                stack[top++] = div-1;
            }
            if(div+1<right){
                stack[top++] = div+1;
                stack[top++] = right;
            }
        }
    }
}
void Merge_Arr(int* arr,int begin1,int end1,int begin2,int end2,int* tmp){
    int index = begin1;
    int left = begin1;
    int right = end2;
    while (begin1 <= end1 && begin2 <= end2)
    {
        if(arr[begin1]<arr[begin2]){
            tmp[index++] = arr[begin1++];
        }
        else{
            tmp[index++] = arr[begin2++];
        }
    }
    while (begin1 <= end1 )
    {
        tmp[index++] = arr[begin1++];
    }
    while (begin2 <= end2 )
    {
        tmp[index++] = arr[begin2++];
    }
    for(int i = left;i<=right;i++){
        arr[i] = tmp[i];
    }
}


//利用递归归并排序，时间复杂度为o(nlogn),空间复杂度为o(N);
void _Merge_Sort(int* arr,int left,int right,int* tmp){
    if(left>=right){
        return;
    }
    //分解
    assert(arr && tmp);
    int mid  = (left+right)/2;
    _Merge_Sort(arr,left,mid,tmp);
    _Merge_Sort(arr,mid+1,right,tmp);
    //递归分解序列直到无法分解。

    //归并
    Merge_Arr(arr,left,mid,mid+1,right,tmp);
}


void Merge_Sort(int* arr,int size){
    //用于存储归并之后的数据
    int* tmp = (int*)malloc(size*sizeof(arr));
    int left = 0;int right = size-1;
    //用于归并排序，参数包括，数组的左右节点
    _Merge_Sort(arr,left,right,tmp);
}

void Merge_Sort_NonR(int* arr,int size){
    assert(arr);
    //用于存储归并之后的数据
    int* tmp = (int*)malloc(size*sizeof(arr));
    int gap = 1;
    while (gap<size)
    {
        for(int i =0;i<size;i+=2*gap){
            int begin1 = i; int end1 = i+gap-1;
            int begin2 = i+gap; int end2 = i+2*gap-1;
            if(begin2>=size){
                break;
            }
            if(end2>=size){
                end2 = size-1;
            }
            Merge_Arr(arr,begin1,end1,begin2,end2,tmp);
        }
        gap*=2;
    }
    
}

// void Merge_arr(int*arr,int begin1,int end1,int begin2,int end2,int* tmp){
//     int index = begin1; 
//     int left = begin1;
//     int right = end2;
//     while (begin1 <= end1 && begin2 <= end2)
//     {    
//         if(arr[begin1]<=arr[begin2]){
//             tmp[index++] = arr[begin1++];
//         }
//         else{
//             tmp[index++] = arr[begin2++];
//         }
//     }
//     while (begin1 <= end1)
//     {
//         tmp[index++] = arr[begin1++];
//     }
//     while (begin2 <= end2)
//     {
//         tmp[index++] = arr[begin2++];
//     }
//     //把排好序的元素放回arr
//     for(int j =left;j<=right;j++){
//         arr[j] = tmp[j];
//     }
// }

// void _Merge_Sort(int*arr,int left,int right,int* tmp){
//     assert(tmp);
//     if(left>=right){
//         return;
//     }

//     int mid = (left+right)/2;
//     int begin1= left; int end1 = mid;
//     int begin2= mid+1; int end2 = right;
//     int index = left;
//     _Merge_Sort(arr,left,mid,tmp); //递归分解，归并
//     _Merge_Sort(arr,mid+1,right,tmp);
//     Merge_arr(arr,begin1,end1,begin2,end2,tmp);
// }

// void Merge_Sort(int* arr,int size){
//     assert(arr);
//     int* tmp = (int*)malloc(size*sizeof(int));
//     int left = 0;
//     int right = size-1;
//     _Merge_Sort(arr,left,right,tmp);
//     free(tmp);
// }

// void Merge_SortNonR(int* arr,int size){
//     assert(arr);
//     int* tmp = (int*)malloc(size*sizeof(int));
//     int left = 0;
//     int right = size-1;
//     int gap = 1;
//     while (gap<size)
//     {
//         for(int i = 0;i<=right;i+=2*gap){
//             int begin1 = i;
//             int end1 = i+gap-1;
//             int begin2 = i+gap;
//             int end2 = i+2*gap-1;
//             if(begin2>right){
//                 break;
//             }
//             if(end2>right){
//                 end2 = right;
//             }
//             Merge_arr(arr,begin1,end1,begin2,end2,tmp);
//         }
//         gap*=2;
//     }
//     free(tmp);
// }

void Count_Sort(int* arr,int size){
    assert(arr);
    int min = arr[0];
    int max = arr[0];
    for(int i = 1;i<size;i++){
        if(arr[i]<min){
            min = arr[i];
        }
        if(arr[i]>max){
            max = arr[i];
        }
    }
    int Range = max-min+1;int index = 0;
    int* Count_Arr = (int*)calloc(Range,sizeof(int));
    for(int i = 0;i<size;i++){
        Count_Arr[arr[i]-min]++;
    };
    for(int j = 0;j<Range;j++){
        while (Count_Arr[j]--)
        {
            arr[index++] = min+j;
        }
        
    }
    return;
}


int main(){
    int arr[]= {6,2,8,10,1,3,5,5,5,5,12,4};
    //int arr[] = {10,6,7,1,3,9,4,2};
    // Bubble_sort(arr,9);
    // Shell_Sort(arr,9);
    // Select_Sort(arr,9);
    // Merge_Sort_NonR(arr,12);
    Count_Sort(arr,12);
    for(int i = 0;i<12;i++){
        printf("%d ",arr[i]);
    }
}