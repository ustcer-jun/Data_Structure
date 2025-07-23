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
    if(left<right){
        int div = PartSort3(arr,left,right);
        QuickSort(arr,left,div-1);
        QuickSort(arr,div+1,right);
    }
}


int main(){
    int arr[]= {6,2,8,10,1,3,5,5,5,5,12,4};
    // Bubble_sort(arr,9);
    // Shell_Sort(arr,9);
    // Select_Sort(arr,9);
    QuickSort(arr,0,11);
    for(int i = 0;i<12;i++){
        printf("%d ",arr[i]);
    }
}