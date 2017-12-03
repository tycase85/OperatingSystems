#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int *allocate(){
	int *arr = malloc(1000);

	return arr;

}

void main (){
	int iter = 0;
	int *arr;
	int *arr2;
	int hundThou;
	while(iter != 100000){

		arr = allocate();
		arr2 = allocate();
		//printf("arr: %d\n", arr);
		//printf("allocate: %d\n", arr2);
		int diff = (arr2 - arr)*4;
		printf("%d\n", diff);




		sleep();
		hundThou += diff;
		iter++;
		//free(arr);
	}

int average = hundThou/100000;
printf("The average: %d\n", average);

}

/* 2. I noticed that the difference in the addresses when shown on the screen differs of about 1008 addresses but when
the average is computed, it only takes 1/4 of that amount. It tells me that there are 4 bytes being allocated per memory
address.
*/
