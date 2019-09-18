/*
    Merge sort
*/

#include<stdio.h>

void merge(int arr[], int l1, int r1, int l2, int r2) {
    int i=l1;
    int j=l2;
    int temp[100], k=0;
    while(i <= r1 && j <= r2) {
        if(arr[i] < arr[j]){
            temp[k++]=arr[i++];
        }else{
            temp[k++]=arr[j++];
        }
    }

    while(i<=r1){
        temp[k++] = arr[i++];
    }

    while(j<=r2){
        temp[k++] = arr[j++];
    }

    for(i=l1,k=0; i<=r2; ++i,++k){
        arr[i] = temp[k];
    }
}

void mergesort(int arr[], int l, int r) {
    int m;
    if (l < r) {
        m = (l+r)/2;
        mergesort(arr, l, m);
        mergesort(arr, m+1, r);
        merge(arr, l, m, m+1, r);
    }
}

void sort(int arr[], int len) {
    int l,r,m;
    l = 0, r = len-1;
    mergesort(arr, l, r);
}

int main(){
    int arr[7] = {5,3,8,4,9,2,10};
    int len = sizeof(arr)/sizeof(int);
    sort(arr, len);
    for(int i=0; i<7; ++i){
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}