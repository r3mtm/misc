/*
 * Create a directory named "testfolder" at /etc/ prior to executing this program.
 * Run this program as root or as set-uid-root.
 * Executing a program without file based capability.
 * Requires CAP_SETUID (for changing the UID) and CAP_DAC_OVERRIDE (to write into folders owned by root)
*/

#include<sys/capability.h>
#include<sys/prctl.h>
#include<linux/securebits.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

#define CAP_COUNT 2

void houseKeep(cap_t *cap_p, const char *str){
	fprintf(stderr, "%s : %s\n", str, strerror(errno));
	cap_free(cap_p);
	exit(0);
}

void dropEffSet(){
	cap_t cap_p;
	const cap_value_t caps[CAP_COUNT] = {CAP_DAC_OVERRIDE, CAP_SETUID};
	cap_p = cap_get_proc();
	if (cap_p == NULL){
		houseKeep(&cap_p, "Error");
	}

	if(cap_clear_flag(cap_p, CAP_EFFECTIVE) == -1){
		houseKeep(&cap_p, "Unable to drop effective capabilities");
	}

	//Setting/Retaining only those required capabilities in the effective set.
	if(cap_set_flag(cap_p, CAP_EFFECTIVE, CAP_COUNT, caps, CAP_SET) == -1){
		houseKeep(&cap_p, "Unable to drop permitted capabilities");
	}

	
	if(cap_set_proc(cap_p) == -1){
		houseKeep(&cap_p, "Unable to drop effective capabilities");
	}

	cap_free(cap_p);
	printf("Effective capabilities dropped\n");
}

void dropPermSet(){
	cap_t cap_p;
	const cap_value_t caps[CAP_COUNT] = {CAP_DAC_OVERRIDE, CAP_SETUID};
	cap_p = cap_get_proc();

	if(cap_p == NULL){
		houseKeep(&cap_p, "Error");	
	}

	//Dropping all capabilities of permitted set in the working storage.
	if(cap_clear_flag(cap_p, CAP_PERMITTED) == -1) {
		houseKeep(&cap_p, "Error dropping permitted capabilities");
	}

	//Setting/Retaining only those required capabilities in the permitted set.
	if(cap_set_flag(cap_p, CAP_PERMITTED, CAP_COUNT, caps, CAP_SET) == -1){
		houseKeep(&cap_p, "Unable to drop permitted capabilities");
	}

	if(cap_set_proc(cap_p) == -1){
		houseKeep(&cap_p, "Unable to drop permitted capabilities");
	}
	cap_free(cap_p);\
	printf("\nDropped all permitted capabilities except CAP_DAC_OVERRIDE\n");
}

void raiseEffCap(){
	cap_t cap_p;
	cap_p = cap_get_proc();
	const cap_value_t caps[1] = { CAP_DAC_OVERRIDE };
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
	int ret;
	uid_t uid = 1000;
	gid_t gid = 1000;
	
	if(prctl(PR_SET_SECUREBITS, SECBIT_KEEP_CAPS) == -1){
		fprintf(stderr, "Error :  %s\n", strerror(errno));
		exit(0);
	}

	dropEffSet();

	//Dropping every capability except CAP_DAC_OVERRIDE, CAP_SETUID in the permitted set
	dropPermSet();

	if(setuid(uid) == -1){
		fprintf(stderr, "Err changing UID : %s\n", strerror(errno));
		exit(0);
	}

	if(setgid(gid) == -1){
		fprintf(stderr, "Err changing GID : %s\n", strerror(errno));
		exit(0);
	}

	//Raising CAP_DAC_OVERRIDE from permitted to effective set.
	raiseEffCap();
	
	ret = creat("/etc/testfolder/tf1.txt", O_WRONLY);
	if (ret == -1){
		fprintf(stderr, "creat() syscall failed\n");
	}else{
		printf("Successful\n");
	}

	
	return 0;
}
