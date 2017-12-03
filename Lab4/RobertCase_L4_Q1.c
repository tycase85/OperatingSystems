#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int *allocate(){
  int *arr = malloc(1000);

  return arr;

}

void main (){

  int *arr;

  while(1){

      arr = allocate();

      printf("%d\n", arr);
      sleep();
      //free(arr);
  }



}

/* 1. The memory usage before the program was running and after it was ran are very similar.
When using the free command while the program is running, the memory used was increased by a large amount.
Before:	1271940 Memory Used
During:	5093596 Memory Used
After:	1270368 Memory Used
The amount of memory used during depends on how long the actual program has been running.
Used Free in another terminal to make checks
*/
