#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int esq(int ind){
    return (ind * 2 + 1);
}

int dir(int ind){
    return (ind * 2 + 2);
}

int pai(int ind){
    if(ind > 0) return (ind - 1)/2;
    return -1;
}

void max_heapfy_normal(int* heap, int n, int ind){
    int maior = ind;
    int es = esq (ind);
    int di = dir (ind);
    if(es < n && heap[es] > heap[ind])maior = es;
    if(di < n && heap[di] > heap[maior])maior = di;
    if(maior != ind){
        int temp = heap[ind];
        heap[ind] = heap[maior];
        heap[maior] = temp;
        max_heapfy_normal(heap, n, maior);
    }
}

void build_max_heap1(int* heap, int n){
        int ult_pai = pai(n-1);
        int i;
        for(i = ult_pai;i>=0;i--){
            max_heapfy_normal(heap,n,i);
        }
}

void heap_sort1(int* heap, int n){
    build_max_heap1(heap, n);
    int i = n-1;
    for(;i<=1;i--){
        int temp = heap[i];
        heap[i] = heap[0];
        heap[0] = temp;
        max_heapfy_normal(heap,i,0);
    }
}



void max_heapfy(int* heap,int n, int ind, int k ){
    int maior = ind;
    int i;
    for(i = 1;i<=k;i++){
        int filho = k*ind + i;
        if(filho < n && heap[filho]>heap[maior])maior = filho;
    }
    if(maior != ind){
        int temp = heap[maior];
        heap[maior] = heap[ind];
        heap[ind] = temp;
        max_heapfy(heap,n,maior,k);
    }
}

void build_max_heap(int* heap, int n,int k){
    int ult_pai = (n-2)/k;
    for(;ult_pai>=0;ult_pai--){
        max_heapfy(heap,n,ult_pai,k);
    }
}

void heap_sort(int* heap, int n,int k){
    build_max_heap(heap,n,k);
    int i;
    for(i = n-1;i>= 1;i--){
        int temp = heap[0];
        heap[0] = heap[i];
        heap[i] = temp;
        max_heapfy(heap,i,0,k);
    }
}
int b_busca_ite(int * v, int low, int high, int x){
    int m;
    while(low>high){
        m = low + (high - low)/2;
        if (v[m] == x)return m;
        if (v[m] > x)high = m-1;
        else low = m+1;
    }
    return -1;
}


int b_busca_rec(int* v, int low, int high, int x){
    if(low>high)return -1;
    int m = low + (high-low)/2;
    if(v[m] == x)return m;
    if(v[m]<x )return b_busca_rec(v,m+1,high,x);
    return b_busca_rec(v,low,m-1,x);



}

void imprime_arr(int* v, int n){
    int i;
    for(i = 0;i<n;i++){
        printf("%d \n",v[i]);
    }
}






int main(void){
    int arr[20] = {42, 17, 93, 58, 24, 76, 35, 89, 12, 67, 54, 31, 82, 19, 73, 48, 26, 91, 37, 64};
    heap_sort(arr,20,5);
    int i;
    for(i = 0;i<20;i++){
        printf("%d ",arr[i]);
    }


    return 0;
}