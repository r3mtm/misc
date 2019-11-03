#include<stdio.h>
#include<stdlib.h>

int filecopy(FILE *, FILE *);

int main(int arg, char *argv[])
{
	FILE *fp;
	int wrote_char;
	if (arg > 1) {
		while (--arg > 0) {
			fp = fdopen(*++argv, "r");
			if(!fp){
				//Uses standard functions.
				perror("Error ");
				exit(1);
			} else{
				//wrote_char = filecopy(fp, stdout);
				wrote_char = filecopy(fp, stdin);
				printf("\n=================================\n");
				printf("Wrote %d characters to stdout", wrote_char);
				printf("\n=================================\n\n");
				if(fclose(fp)){
					perror("Fatal Error ");
				}
			 }
		}
	}else{
		filecopy(stdin, stdout);
	}
	return 0;
}

int filecopy(FILE *ip, FILE *op){
	char c;
	int count = 0;
	while((c = getc(ip)) != EOF){
		if((putc(c, op)) == EOF){
			printf("\n=================================\n");
			perror("Fatal error ");
			printf("=================================\n");
			break;
		}
		else{
			++count;
		}
	}
	return count;
}
