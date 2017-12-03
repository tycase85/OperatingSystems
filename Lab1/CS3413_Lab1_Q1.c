#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *function(){
	int id = pthread_self();
	printf("\n");	
	printf("This is the new pthread id: %u ", id);
	printf("\n");	
}

int main(void){

	pid_t pid;
	int var = 0;
	pid = fork(var);
	pthread_t mythread;		

	if(pid == 0){
		printf("\n");		
		printf("This is a child process: %d", getpid());
		var++;
		printf("  VAR:%d ", var);
		pthread_create(&mythread, NULL, &function, NULL);
		pthread_join(mythread, NULL);
		printf("\n");

	}

	else if(pid > 0){
		printf("\n");
		printf("This is a parent process: %d", getpid());
		var--;
		printf("  VAR:%d ", var);

	}

	else{
		return;
	}

	return var;

}
