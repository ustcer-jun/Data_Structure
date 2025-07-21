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


int main(){
    int arr[]= {6,2,8,10,1,3,5,12,4};
    // Bubble_sort(arr,9);
    Shell_Sort(arr,9);
    for(int i = 0;i<9;i++){
        printf("%d ",arr[i]);
    }
}