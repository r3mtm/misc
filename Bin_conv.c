//Decimal to binary.
#include<stdio.h>
#include<math.h>

int main(){
	unsigned int num,mask,size,i;
	size = sizeof(int) * 8;
	mask = pow(2, size-1);
	printf("=> ");
	scanf("%d",&num);
	for(i=size; i > 0 ; --i){
		printf("%d", (mask & num) >> i-1);
		mask = mask >> 1;
	}
	return 0;
}
