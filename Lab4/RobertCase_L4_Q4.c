#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int *allocate(){
  int *arr = malloc(10000000);

  return arr;

}

void main (){

  int *arr;
  int *arr2;
  while(1){

      arr = allocate();
      arr2 = allocate();
      memset(arr, 123, 10000000);
      memset(arr2, 123, 10000000);
      system("free -m");

//sleep(1);

      //free(arr);
  }



}

/* 4.Keeps filling the allocated space with the 123 values until it uses all free memory and then tries the swap. Eventually get a segmentation fault.
*/
