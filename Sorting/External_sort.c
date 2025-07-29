#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

void Swap(int* p,int* q){
    assert(p&&q);
    int tmp = *p;
    *p = *q;
    *q = tmp;
    return;
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

// void External_sort(const char* file){
//     //打开要排序文件
//     FILE* fout = fopen(file,"r");
//     if(!fout){
//         perror("fopen");
//         exit(-1);
//     }
//     int num = 0;
//     int size = 13;
//     int i = 0;
//     int filei = 1;
//     char Subfile[20];
//     int* arr = (int*)malloc(size*sizeof(int));
//     memset(arr,0,size*sizeof(int));
//     while(fscanf(fout,"%d\n",&num )!=EOF)//读取文件里的数据
//     {
//         if(i<size-1){
//             arr[i++] = num;
//         }
//         else{
//             arr[i++] = num;
//             QuickSort_stack(arr,0,size-1);
//             sprintf(Subfile,".//sub_sort%d",filei++); 
//             FILE* fin = fopen(Subfile,"w");
//             for(int k = 0;k<size;k++){
//                 fprintf(fin,"%d\n",arr[k]);
//             }
//             fclose(fin);
//             i=0;
//             memset(arr,0,size);
//         }
//     }
//     if (i > 0) {
//         QuickSort_stack(arr, 0, i - 1);
//         sprintf(Subfile, ".//sub_sort%d", filei);
//         FILE* fin = fopen(Subfile, "w");
//         for (int k = 0; k < i; k++) {
//             fprintf(fin, "%d\n", arr[k]);
//         }
//         fclose(fin);
//     }
//     char mfile[100] = "";
//     char file1[100] = ".//sub_sort1";
//     char file2[100] = "";
//     for(int i = 2;i<file;i++){
//         sprintf(file2,".//sub_sort%d",i);
//         sprintf(mfile,".//sub_sort%s%d",mfile,i);

//         //合并文件
//         Merge_Sort(file1,file2,mfile);
//     }
// }

// void Merge_Sort(const char* file1,const char* file2,const char* mfile){
//     FILE* fout1 = fopen(file1,"r");
//     FILE* fout2 = fopen(file2,"r");
//     FILE* fin = fopen(mfile,"r");
//     if(!fout1 || !fout2 || !fin){
//         perror("fopen");
//         exit(-1);
//     }
//     int num1,num2;
//     int ret1 = fscanf(fout1,"%d\n",&num1);
//     int ret2 = fscanf(fout2,"%d\n",&num2);
//     while (ret1 != EOF && ret2 != EOF)
//     {
//         if(num1<num2){
//             fprintf(fin,"%d\n",num1);
//             ret1 = fscanf(fout1,"%d\n",&num1);
//         }
//         else{
//             fprintf(fin,"%d\n",num2);
//             ret2 = fscanf(fout2,"%d\n",&num2);
//         }
//     }
//     while (fscanf(fout1,"%d\n",&num1))
//     {
//         fprintf(fin,"%d\n",num1);
//     }
//     while (fscanf(fout2,"%d\n",&num2))
//     {
//         fprintf(fin,"%d\n",num2);
//     }
// }

// int main(){
//     char file[] = "merge_sort.txt";
//     External_sort(file);
// }

void _mergefile(const char* file1,const char* file2,const char* merge_file){
    FILE* fout1 = fopen(file1,"r");
    FILE* fout2 = fopen(file2,"r");
    FILE* fin = fopen(merge_file,"w");
    if(!fout1 || !fout2 || !fin){
        perror("fopen!");
        exit(-1);
    }
    int num1 = 0;
    int num2 = 0;
    int ret1= fscanf(fout1,"%d\n",&num1);
    int ret2= fscanf(fout2,"%d\n",&num2);
    while ( ret1 != EOF && ret2 !=EOF)
    {
        if(num1<num2){
            fprintf(fin,"%d\n",num1);
            ret1= fscanf(fout1,"%d\n",&num1);
        }
        else{
            fprintf(fin,"%d\n",num2);
            ret2= fscanf(fout2,"%d\n",&num2);
        }
    }
    while (ret1 != EOF)
    {
        fprintf(fin,"%d\n",num1);
        ret1= fscanf(fout1,"%d\n",&num1);
    }
    while (ret2 != EOF)
    {
        fprintf(fin,"%d\n",num2);
        ret2= fscanf(fout2,"%d\n",&num2);
    }
    fclose(fout1);
    fclose(fout2);
    fclose(fin);
    
}

void External_Sort(const char* file){
    assert(file);
    FILE* fout = fopen(file,"r");
    if(!fout){
        perror("fopen!");
        exit(-1);
    }
    int num1= 0; //存储读入的数据
    int size = 13;
    char Subfile[20];
    int* arr = (int*) malloc(sizeof(int)*size);
    int filei = 1;int i=0;
    while(fscanf(fout,"%d\n",&num1)!=EOF){ //确保读取数据
        if(i<size-1){
            arr[i++] = num1;   
        }
        else{
            arr[i++] = num1;
            //读取到足够的数据进行排列后再放入子文件
            QuickSort_stack(arr,0,size-1);
            sprintf(Subfile,".//sort_file%d",filei++);
            FILE* fin = fopen(Subfile,"w");
            if(!fin){
                perror("fopen!");
                exit(-1);
            }
            else{
                for(int k =0;k<size;k++){
                    fprintf(fin,"%d\n",arr[k]);
                }
            }
            i = 0;
            fclose(fin);
            memset(arr,0,size);
        }
    }
    //当最后一组数据数量不够，也排序后放入子文件
    if(i>0){
        QuickSort_stack(arr,0,i);
        sprintf(Subfile,".//sort_file%d",filei++);
        FILE* fin = fopen(Subfile,"w");
        for(int k =0;k<i;k++){
            fprintf(fin,"%d\n",arr[k]);
        }
        fclose(fin);
    }
    fclose(fout);

    //合并子文件
    char file1[200] = "sort_file1";
    char file2[200] = "";
    char merge_file[200] = "";
    for(int k = 2;k<filei;k++){
        // sprintf(file1,"sort_file%d",k-1);
        sprintf(file2,"sort_file%d",k);
        sprintf(merge_file,"merge_file%d",k-1);
        _mergefile(file1,file2,merge_file);
        strcpy(file1,merge_file);
    };

}
int main(){
    External_Sort("merge_sort.txt");
}