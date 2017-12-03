#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#define MAX_CHAR 100
//By: Robert Tyler Case 3502846
//gcc -o RobertCase_A7_Q1 RobertCase_A7_Q1.c
//./RobertCase_A7_Q1 F 53


int cylReq;
int requestTable[10];
int tableLength = 0;
int total = 0;
int totalHeadMovement = 0;
int firstTime = 0;
int positionArr[10];
int smallestDiff = 10000;
int next = 10000;
int pos;
int changeDir = 0;

void fcfs(){
  int i;
printf("%d\n", requestTable[0]); //prints next character in array
  for(i = 0; i < 9; i++){ //shifting all items down one and removing the 0th item

      requestTable[i] = requestTable[i+1]; //moving the items down in the array

      }
}

void sstf(){
    int i;
    int temp;
    int posHolder;

    printf("%d\n", positionArr[0]);
    for(i=1; i<9; i++){
      if(positionArr[i] == -69){
        continue;
      }


      temp = abs(positionArr[0]-positionArr[i]);
      if(temp < smallestDiff){
        smallestDiff = temp;
        pos = i;
        posHolder = positionArr[i];
      }
      else if(temp == smallestDiff && posHolder != positionArr[i]){ //if they have the same difference
        if(posHolder > positionArr[i]){ //compare the current smallest's address with the new address. if the old one is bigger,
          smallestDiff = temp; //smallest diff will be the temp
          pos = i; //position will be the current one
          posHolder = positionArr[i]; //holder will be the current value

        }
      }
    }

    totalHeadMovement += smallestDiff;
    positionArr[0] = positionArr[pos];
    temp = 0;
    posHolder = 0;
    smallestDiff = 10000;

}


void scan(){
  int i;
  int temp;
  int posHolder;
  if(positionArr[0] != 0){
    printf("%d\n", positionArr[0]);
  }
  for(i=1; i<9; i++){
    if(positionArr[i] == -69){
      continue;
    }
    if(changeDir == 0){
        if(temp == 0 && i == 8){ //if at the end of the comparing list and temp hasnt been changed

          temp = positionArr[0];
          next = temp;
          positionArr[0] = 0;
          temp = positionArr[0];
          pos = 0;
          posHolder = 0;
          changeDir = 1;
        }
      if(positionArr[i] < positionArr[0]){

        temp = abs(positionArr[0]-positionArr[i]);
        if(temp < next){

          next = temp;
          pos = i;
          posHolder = positionArr[i];
        }

      }
    }

    else if(changeDir == 1){

      if(temp == 0 && i == 8){ //if at the end of the comparing list and temp hasnt been changed

        temp = positionArr[0];
        next = temp;
        positionArr[0] = 9999;
        temp = positionArr[0];
        pos = 0;
        posHolder = 0;
        changeDir = 0;
      }

      if(positionArr[i] > positionArr[0]){

        temp = abs(positionArr[i] - positionArr[0]);
        if(temp < next){
          next = temp;
          pos = i;
          posHolder = positionArr[i];
          }

      }
    }
  }
    totalHeadMovement += next;
    positionArr[0] = positionArr[pos];
    temp = 0;
    posHolder = 0;
    next = 10000;

}






void cscan(){
  int i;
  int temp;
  int posHolder;
  if(positionArr[0] != -69){
    printf("%d\n", positionArr[0]);
  }
  for(i=1; i<9; i++){
    if(positionArr[i] == -69){
      continue;
    }

        if(temp == 0 && i == 8){ //if at the end of the comparing list and temp hasnt been changed
printf("WENT FROM 0 TO 9999\n");
totalHeadMovement += positionArr[0];
positionArr[0] = 9999;

          for(i=1; i<9; i++){


          if(positionArr[i] < positionArr[0]){

            temp = abs(positionArr[0]-positionArr[i]);
            if(temp < next){

              next = temp + 1; //For going from 0 to 9999
              pos = i;
              posHolder = positionArr[i];
            }

          }
        }
        }
      if(positionArr[i] < positionArr[0]){

        temp = abs(positionArr[0]-positionArr[i]);
        if(temp < next){

          next = temp;
          pos = i;
          posHolder = positionArr[i];
        }

      }

  }

    totalHeadMovement += next;
    positionArr[0] = positionArr[pos];
    temp = 0;
    posHolder = 0;
    next = 10000;

}



void look(){
  int i;
  int j;
  int temp;
  int posHolder;

printf("%d\n", positionArr[0]);

  for(i=1; i<9; i++){
    if(positionArr[i] == -69){
      continue;
    }
    if(changeDir == 0){
        if(temp == 0 && i == 8){ //if at the end of the comparing list and temp hasnt been changed
          printf("CHANGING DIRECTIONS\n");
          for(j=1; j<9; j++){
            if(positionArr[j] > positionArr[0]){

              temp = abs(positionArr[j] - positionArr[0]);
              if(temp < next){
              next = temp;
              pos = j;
              posHolder = 0;
              changeDir = 1;
              }
            }
          }
        }
      if(positionArr[i] < positionArr[0]){

        temp = abs(positionArr[0]-positionArr[i]);
        if(temp < next){

          next = temp;
          pos = i;
          posHolder = positionArr[i];
        }

      }
    }

    else if(changeDir == 1){

      if(temp == 0 && i == 8){ //if at the end of the comparing list and temp hasnt been changed
        printf("CHANGING DIRECTIONS\n");
        for(j=1; j<9; j++){

          if(positionArr[j] < positionArr[0]){
          temp = abs(positionArr[j] - positionArr[0]);
      if(temp < next){
        next = temp;
        pos = j;
        posHolder = 0;
        changeDir = 0;
      }
      }
      }
    }

      if(positionArr[i] > positionArr[0]){

        temp = abs(positionArr[i] - positionArr[0]);
        if(temp < next){
          next = temp;
          pos = i;
          posHolder = positionArr[i];
          }

      }
    }
  }
    totalHeadMovement += next;
    positionArr[0] = positionArr[pos];
    temp = 0;
    posHolder = 0;
    next = 10000;

}




void main(int argc, char *argv[]){

  char *p;
  long conv = strtol(argv[2], &p, 10);
  int inputStart = conv;
  char inputAlgo = *argv[1];
  int i;
  int headMovementHolder;
  int holder;
  int test = 0;
  int test2 = 0;
  FILE *file = fopen("cylinder_requests.txt", "r");
  requestTable[tableLength] = inputStart;

  if(inputAlgo == 'F'){
    while(!feof(file)){
        if(tableLength < 10){
          fscanf(file, "%d%*[\n]", &cylReq);
          requestTable[tableLength+1] = cylReq;
          tableLength++;
        }
          if(requestTable[i] > requestTable[i+1]){
              headMovementHolder = requestTable[i]-requestTable[i+1];
          }
          else{
              headMovementHolder = requestTable[i+1]-requestTable[i];
          }
          totalHeadMovement += headMovementHolder;

          fcfs();
          tableLength--;

    }
  }


  if(inputAlgo == 'T'){
    positionArr[0] = inputStart;
    for(i=1; i<9; i++){
      fscanf(file, "%d%*[\n]", &cylReq);
      positionArr[i] = cylReq;
    }

    while(!feof(file)){
      sstf();
      fscanf(file, "%d%*[\n]", &cylReq);
      positionArr[pos] = cylReq;
      test++;

    }
    while(test2 < 9){
      sstf();
      positionArr[pos] = -69;
      test2++;
    }
    totalHeadMovement = totalHeadMovement-10000;

  }




  if(inputAlgo == 'S'){
    positionArr[0] = inputStart;

    for(i=1; i<9; i++){
      fscanf(file, "%d%*[\n]", &cylReq);
      positionArr[i] = cylReq;
    }

    while(!feof(file)){
      scan();
      fscanf(file, "%d%*[\n]", &cylReq);
      positionArr[pos] = cylReq;
      test++;

    }
    while(test2 < 9){

      scan();
      positionArr[pos] = -69;
      if(positionArr[0] == -69){
        positionArr[0] = 0;
      }
      test2++;
    }
  }



  if(inputAlgo == 'C'){
    positionArr[0] = inputStart;

    for(i=1; i<9; i++){
      fscanf(file, "%d%*[\n]", &cylReq);
      positionArr[i] = cylReq;
    }

    while(!feof(file)){
      cscan();
      fscanf(file, "%d%*[\n]", &cylReq);
      positionArr[pos] = cylReq;
      test++;

    }
    while(test2 < 9){

      cscan();
      positionArr[pos] = -69;
      test2++;
    }
    totalHeadMovement = totalHeadMovement-10000;

  }




  if(inputAlgo == 'L'){
    positionArr[0] = inputStart;

    for(i=1; i<9; i++){
      fscanf(file, "%d%*[\n]", &cylReq);
      positionArr[i] = cylReq;
    }

    while(!feof(file)){
      look();
      fscanf(file, "%d%*[\n]", &cylReq);
      positionArr[pos] = cylReq;
      test++;

    }
    while(test2 < 9){

      look();
      positionArr[pos] = -69;
      if(positionArr[0] == -69){
        positionArr[0] = 0;
      }
      test2++;
    }
    totalHeadMovement = totalHeadMovement-10000;
}




    printf("Total Head Movement: %d\n", totalHeadMovement);

}
