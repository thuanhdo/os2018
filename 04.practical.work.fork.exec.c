#include<stdio.h>
#include<unistd.h>
int main(){
printf("Main before fork()\n");
int pid0 = fork();

if(pid0==0){
	int pid = fork();

	if(pid!=0){
		printf("1st child, launching ps -ef\n");
		char *args[] = {"/bin/ps", "-ef", NULL};
		execvp("/bin/ps", args);
		printf("check1");
	}

	else{
		printf("2nd child, launching free -h\n");
		char *args[] = {"/bin/free","-h", NULL};
		execvp("/bin/free", args);
		printf("check2");
	}
}
}

