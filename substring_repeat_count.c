/*
	Minimum number of times string A has to be repeated such that string B is a substring of it
*/

#include<stdio.h>
#include<string.h>

int main(){
    char A[5]="acdc";
    char B[9]="cac";
    int occr[100];
    int lena = strlen(A);
    int lenb = strlen(B);
    int count = -1, times=0;

    for(int j=0; j<lena; ++j){
            if(B[0] == A[j]){
                occr[++count]=j;
            }
    }
    int match;
    for(int x=0; x<=count; ++x){
        int index = occr[x];
        match = 1;
        times = 1;
        for(int i=0; i<lenb; ++i){
            if(A[index++] == B[i]){
                //do nothing
            }else{
                match = 0;
                break;
            }
            if(index == lena){
                ++times;
                index=0;
            }
        }
        if(match == 1){
            break;
        }
    }

    if(match == 1){
        printf("Times %d\n", times);
    }else{
        printf("Not found\n");
    }
    return 0;
}
