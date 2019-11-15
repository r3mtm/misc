/*
 * Prorgram showing how to set capability sets.
 * Compile : gcc -lcap cap_aware.c
 * Before execution add capability
 * 	sudo setcap cap_dac_override+p ./a.out
 *
*/

#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/capability.h>
#include<fcntl.h>

#define CAP_NO 1

void modCap(int capability, cap_flag_value_t value){
	cap_t cap_p;
	cap_value_t caps[CAP_NO];
	cap_p = cap_get_proc();
	caps[0] =capability;

	if (cap_p == NULL){
		fprintf(stderr, "Error getting capability\n");
		cap_free(cap_p);
		exit(0);
	}
	if(cap_set_flag(cap_p, CAP_EFFECTIVE, CAP_NO, caps, value) == -1){
		fprintf(stderr, "Error setting capability\n");
		cap_free(cap_p);
		exit(0);
	}
	/*
	if(cap_set_flag(cap_p, CAP_INHERITABLE, CAP_NO, caps, value) == -1){
		fprintf(stderr, "Error setting inheritable set\n");
		cap_free(cap_p);
		exit(0);
	}
	*/
	if(cap_set_proc(cap_p) == -1){
		fprintf(stderr, "Error setting capability\n");
		cap_free(cap_p);
		exit(0);
	}
	cap_free(cap_p);
}

void dropAllCap(){
	cap_t clear;
	clear = cap_init();
	if (clear == NULL){
		fprintf(stderr, "Error");
		exit(0);
	}
	cap_set_proc(clear);
	cap_free(clear);
}

int main(){
	int ret;
	ret = creat("/etc/testfolder/tf1.txt", O_WRONLY);
	if(ret == -1){
		fprintf(stderr, "Tried without setting effective flag, FAILED!\nTrying again...\n");
	}
	modCap(CAP_DAC_OVERRIDE, CAP_SET);
	ret = creat("/etc/testfolder/tf1.txt", O_WRONLY);
	if (ret == -1){
		fprintf(stderr, "Again Failed\n");
	}else{
		printf("Succeeded\n");
	}

	//Clearing effective set.	
	modCap(CAP_DAC_OVERRIDE, CAP_CLEAR);

	//Drop all capabilities from all capabiliy set.
	dropAllCap();
	return 0;
}
