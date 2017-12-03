#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *getAvg(int a[], int argc){

	int i = 0;
	int avg = 0;
	int sum = 0;

	
	for(i = 1; i<argc; i++){
		if(a[i] != 0){
			sum += a[i];	
		}
		else{
			argc = argc-1;
		}
	}

	avg = (sum/(argc-1));
	printf("The average value is %d", avg);
	printf("\n");
}

void *getMax(int a[], int argc){

	int i = 0;
	int hold = 0;
	int max = 0;
	
	for(i = 1; i<argc; i++){
		if(a[i] > hold){
			hold = a[i];	
		}
	}
	max = hold;
	printf("The maximum value is %d", max);
	printf("\n");
}

void *getMin(int a[], int argc){

	int i = 0;
	int hold = a[1];
	int min = 0;
	
	for(i = 1; i<argc; i++){
		if(a[i] != 0 && a[i] < hold){
			hold = a[i];	
		}
	}
	min = hold;
	printf("The minimum value is %d", min);
	printf("\n");
}

int main(int argc, char *argv[]){

	pid_t pid;
	int n = 0;
	int i = 0;
	int val = 400;
	int a[argc];
	pthread_t pt1;		
	pthread_t pt2;	
	pthread_t pt3;	


 	for (i=1; i<argc; i++){

		a[i] = atoi(argv[i]);	
	}

	pthread_create(&pt1, NULL, getAvg(a, argc), NULL);
	pthread_create(&pt3, NULL, getMin(a, argc), NULL);
	pthread_create(&pt2, NULL, getMax(a, argc), NULL);

	pthread_join(pt1,NULL);
	pthread_join(pt2,NULL);
	pthread_join(pt3,NULL);
	
	return 0;

}
