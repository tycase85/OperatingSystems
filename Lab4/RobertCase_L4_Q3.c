#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int *allocate(){
  int *arr = malloc(1000);

  return arr;

}

void main (){

  int *arr;
  int count = 0;
  int someCounter = 4;
  while(count != 100){

      arr = allocate();

      printf("%d", arr);
      sleep();
      if(count%10 == someCounter){
        printf(" - Not Freed\n");
      }
      else{
        free(arr);
        printf(" - Freed\n");
      }
      count++;
  }



}

/* 1. Yes it gets reallocated. Each time that there is a malloc there is a free called in the while loop and this creates
space at this block for the next memory allocation. It is continually the same memory address over and over.
*/
