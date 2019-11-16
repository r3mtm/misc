/*
 * Stub program which is meant to be exec-ed by cap_driver-pgm.c
 * Program verifies that if F(inheritable) is not set, then just by inheriting the inheritable set won't add it to the effective set.
 * Try with and without setting the file inheritable set.
 * Compile : gcc -lcap cap_stub-pgm.c -o cap_stub-pgm
 * View /proc/<pid>/status for capability sets.
*/

#include<sys/capability.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#define CAP_COUNT 1

void modCap(){
	cap_t cap_p;
	cap_p = cap_get_proc();
	cap_value_t caps[CAP_COUNT] = { CAP_DAC_OVERRIDE  };
	if(cap_set_flag(cap_p, CAP_EFFECTIVE, 1, caps, CAP_SET) == -1){
		printf("Error setting effective capabilities\n");
		cap_free(cap_p);
		exit(0);
	}
	if(cap_set_proc(cap_p) == -1){
		printf("Failed to add effective capabilities\n");
		cap_free(cap_p);
		exit(0);
	}
	cap_free(cap_p);
}

int main(){
	printf("On stub program\n");
	modCap();
	sleep(30);
	int ret;
	ret = creat("/etc/testfolder/tf1.txt", O_WRONLY);
	if (ret == -1){
		fprintf(stderr, "creat() syscall failed\n");
	}else{
		printf("Successful\n");
	}
	return 0;
}
