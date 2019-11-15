/*
 *Program to fetch the capability of a process and display it in human readable string
 *Compile gcc -lcap disp_cap_text.c
*/

#include<sys/capability.h>
#include<stdlib.h>
#include<stdio.h>

void getCaps(){
	cap_t caps;
	char *caps_str;
	caps = cap_get_proc();
	if (caps == NULL){
		fprintf(stderr, "Error getting capabilities\n");
	}else{
		caps_str = cap_to_text(caps, NULL);
		cap_free(caps);
		printf("Capabilities %s\n", caps_str);
		cap_free(caps_str);
	}
}

int main(){
	getCaps();
	return 0;
}	
