/*
 * Driver program which is meant to "exec" cap_stub-pgm.c
 * Program verifies that if F(inheritable) is not set, then just by inheriting the inheritable set won't add it to the effective set.
 * Compile :  gcc -lcap cap_driver-pgm.c
 * Add capability to file : setcap cap_dac_override+p ./a.out  //Run with sudo if no CAP_SETFCAP capability.
 * View /proc/<pid>/status for capability sets.
*/

#include<sys/capability.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>

#define CAP_COUNT 1

void modCaps(){
	cap_t cap_p;
	cap_p = cap_get_proc();
	cap_value_t caps[CAP_COUNT] = {CAP_DAC_OVERRIDE};
	if(cap_set_flag(cap_p, CAP_INHERITABLE, CAP_COUNT, caps, CAP_SET) == -1){
		fprintf(stderr, "Error setting capability flagsi\n");
		cap_free(cap_p);
		exit(0);
	}
	if(cap_set_proc(cap_p) == -1){
		fprintf(stderr, "Error adding capability\n");
		cap_free(cap_p);
		exit(0);
	}
	
	cap_free(cap_p);
	printf("Before exec-ing\n");
	sleep(20);
	printf("Exec-ed\n");
	execv("cap_stub-pgm", NULL);
}

int main(){
	modCaps();
	return 0;
}
