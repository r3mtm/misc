/*
 * Program to verify the values of EUID, SUID, RUID while escalting its privileges. Check /proc/[proc-id]/status to view the IDs. Set the setuid bit with root ownership before execution to view the expected result. Also create a folder(here it is  "/etc/testfolder") 
*/

#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>

int main(){
	pid_t pid = getpid();
	printf("Process id %d\n", pid);
	printf("Verify EUID, RUID, SUID now\n");
	sleep(20);
	//If ran(as a normal user) according to the conditions specified above, RUID will be 1000 or something like that, EUID will be 0, SUID will be 0
	printf("Creating a new file...\n");
	int ret=seteuid(1000);
	//SUID will retain 0, every other ID changes to 1000(in this case).
	printf("%d\n", ret);
	ret=creat("/etc/testfolder/tf1.txt", O_WRONLY);
	if (ret==-1){
		printf("File creation failed. Err : %s\n", strerror(errno));
		printf("Changing EUID\n");
		sleep(20);
		ret = seteuid(0);
		//Changes to the initial values. RUID=1000(in this case), SUID, EUID=0
		printf("Status : %d\n", ret);
	}
	sleep(50);	
	return 0;
}
