#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#define MAX_CHAR 100
//By: Robert Tyler Case 3502846
//gcc -o RobertCase_A8_Q1 RobertCase_A8_Q1.c
//./RobertCase_A8_Q1 F 12 disk_layout.txt


int cylReq;
int requestTable[10];
int tableLength = 0;
int total = 0;
int totalHeadMovement = 0;
int totalHeadHolder = 0;
int firstTime = 0;
int positionArr[10];
int smallestDiff = 10000;
int next = 10000;
int pos;
int changeDir = 0;
int diskLayoutArr[10000];
int diskLayoutArr2[10000];
int in = 0;
int holder = 0;



void fcfs(){

  int currIndex = positionArr[0];
  //currIndex is the number in the array so at 5249 it is 5249
  //diskLayoutArr2[currIndex] gets the second number of the layout file
  if(diskLayoutArr2[currIndex] == -1){
    printf("\n%d\n", positionArr[0]);
    printf("\n");
    totalHeadHolder = abs(positionArr[0] - diskLayoutArr2[currIndex]);
    totalHeadMovement += totalHeadHolder;
  }
  while(diskLayoutArr2[currIndex] != -1){
    printf("%d -> %d\n", positionArr[0], diskLayoutArr2[currIndex]);
    totalHeadHolder = abs(positionArr[0] - diskLayoutArr2[currIndex]);
    totalHeadMovement += totalHeadHolder;
    positionArr[0] = diskLayoutArr2[currIndex];
    currIndex = positionArr[0];

  }


}

void sstf(){

  int currIndex = positionArr[0];
  if(diskLayoutArr2[currIndex] == -1){
    printf("\n%d\n", positionArr[0]);
    printf("\n");
    totalHeadHolder = abs(positionArr[0] - diskLayoutArr2[currIndex]);
    totalHeadMovement += totalHeadHolder;
  }
  while(diskLayoutArr2[currIndex] != -1){
    printf("%d -> %d\n", positionArr[0], diskLayoutArr2[currIndex]);
    totalHeadHolder = abs(positionArr[0] - diskLayoutArr2[currIndex]);
    totalHeadMovement += totalHeadHolder;
    positionArr[0] = diskLayoutArr2[currIndex];
    currIndex = positionArr[0];

  }

}


void scan(){

  int currIndex = positionArr[0];
  if(diskLayoutArr2[currIndex] == -1){
    printf("\n%d\n", positionArr[0]);
    printf("\n");
    totalHeadHolder = abs(positionArr[0] - diskLayoutArr2[currIndex]);
    totalHeadMovement += totalHeadHolder;
  }
  while(diskLayoutArr2[currIndex] != -1){
    printf("%d -> %d\n", positionArr[0], diskLayoutArr2[currIndex]);
    totalHeadHolder = abs(positionArr[0] - diskLayoutArr2[currIndex]);
    totalHeadMovement += totalHeadHolder;
    positionArr[0] = diskLayoutArr2[currIndex];
    currIndex = positionArr[0];

  }

}






void cscan(){

  int currIndex = positionArr[0];
  if(diskLayoutArr2[currIndex] == -1){
    printf("\n%d\n", positionArr[0]);
    printf("\n");
    totalHeadHolder = abs(positionArr[0] - diskLayoutArr2[currIndex]);
    totalHeadMovement += totalHeadHolder;
  }
  while(diskLayoutArr2[currIndex] != -1){

    if(abs(9999-diskLayoutArr2[currIndex]) < abs(positionArr[0]-diskLayoutArr2[currIndex])){
      printf("Went past 9999 to restart at 0.\n"); //overlapped at 9999
      totalHeadHolder = abs(9999-diskLayoutArr2[currIndex]);
      totalHeadMovement += totalHeadHolder;
      printf("%d -> %d\n", positionArr[0], diskLayoutArr2[currIndex]);
    }

    else{
      totalHeadHolder = abs(positionArr[0] - diskLayoutArr2[currIndex]);
      totalHeadMovement += totalHeadHolder;
      printf("%d -> %d\n", positionArr[0], diskLayoutArr2[currIndex]);
    }

    positionArr[0] = diskLayoutArr2[currIndex];
    currIndex = positionArr[0];

  }

}



void look(){

  int currIndex = positionArr[0];
  if(diskLayoutArr2[currIndex] == -1){
    printf("\n%d\n", positionArr[0]);
    printf("\n");
    totalHeadHolder = abs(positionArr[0] - diskLayoutArr2[currIndex]);
    totalHeadMovement += totalHeadHolder;
  }
  while(diskLayoutArr2[currIndex] != -1){
    printf("%d -> %d\n", positionArr[0], diskLayoutArr2[currIndex]);
    totalHeadHolder = abs(positionArr[0] - diskLayoutArr2[currIndex]);
    totalHeadMovement += totalHeadHolder;
    positionArr[0] = diskLayoutArr2[currIndex];
    currIndex = positionArr[0];

  }
}




void main(int argc, char *argv[]){


  char *p;
  long conv = strtol(argv[2], &p, 10);
  int inputStart = conv;

  char inputAlgo = *argv[1];
  char inputFile[50];
  strcpy(inputFile, argv[3]);
  int i;
  int headMovementHolder;
  int holder;
  int first = 0;
  int test = 0;
  int test2 = 0;
  FILE *file = fopen("files_requested.txt", "r");
  FILE *file2 = fopen(inputFile, "r");


  while(!feof(file2)){
    fscanf(file2, "%d%*[\n]", &diskLayoutArr[in]);
    fscanf(file2, "%d%*[\n]", &diskLayoutArr2[in]);
    in++;
  }

  if(inputAlgo == 'F'){
    while(!feof(file)){
        if(first != 1){
          positionArr[0] = inputStart;
          tableLength++;
          first = 1;
        }
        else if(tableLength < 1){
          fscanf(file, "%d%*[\n]", &cylReq);
          positionArr[0] = cylReq;
          tableLength++;
        }

          fcfs();
          tableLength--;

    }
    printf("Total Head Movements: %d\n", totalHeadMovement);
  }


  if(inputAlgo == 'T'){
    //positionArr[0] = inputStart;
    while(!feof(file)){
        if(first != 1){
          positionArr[0] = inputStart;
          tableLength++;
          first = 1;
        }
        else if(tableLength < 1){
          fscanf(file, "%d%*[\n]", &cylReq);
          positionArr[0] = cylReq;
          tableLength++;
        }

          sstf();
          tableLength--;

    }
    printf("Total Head Movements: %d\n", totalHeadMovement);

  }




  if(inputAlgo == 'S'){
    while(!feof(file)){
        if(first != 1){
          positionArr[0] = inputStart;
          tableLength++;
          first = 1;
        }
        else if(tableLength < 1){
          fscanf(file, "%d%*[\n]", &cylReq);
          positionArr[0] = cylReq;
          tableLength++;
        }

          scan();
          tableLength--;

    }
    printf("Total Head Movements: %d\n", totalHeadMovement);
  }



  if(inputAlgo == 'C'){
    printf("Direction: Right");
    while(!feof(file)){
        if(first != 1){
          positionArr[0] = inputStart;
          tableLength++;
          first = 1;
        }
        else if(tableLength < 1){
          fscanf(file, "%d%*[\n]", &cylReq);
          positionArr[0] = cylReq;
          tableLength++;
        }

          cscan();
          tableLength--;

    }
    printf("Total Head Movements: %d\n", totalHeadMovement);
  }




  if(inputAlgo == 'L'){
    while(!feof(file)){
        if(first != 1){
          positionArr[0] = inputStart;
          tableLength++;
          first = 1;
        }
        else if(tableLength < 1){
          fscanf(file, "%d%*[\n]", &cylReq);
          positionArr[0] = cylReq;
          tableLength++;
        }

          look();
          tableLength--;

    }
    printf("Total Head Movements: %d\n", totalHeadMovement);
}


}
