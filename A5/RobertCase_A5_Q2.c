#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>

//By: Robert Tyler Case 3502846
//gcc -o RobertCase_A5_Q2 RobertCase_A5_Q2.c
//./RobertCase_A5_Q2 10 mem.txt F < sample_logical_addr.txt
//./RobertCase_A5_Q2 10 mem.txt L < sample_logical_addr.txt
//./RobertCase_A5_Q2 10 mem.txt O < sample_logical_addr.txt

struct node
  {
  int addrNum;
  int position;
  int count;
  int data;
  struct node *next;
  struct node *prev;
};
struct node *new_node;
struct node *start = NULL;
struct node *end = NULL;

unsigned char memoryStrings[255][255]; //holds 256 char string
int counter = 0;
int iteration = 0;
unsigned char stringHolder[255]; //holds the string at 256 characters
unsigned char logAddr[2];
long framesTotal;
unsigned char physAddr[2];
unsigned short q;
int pageTable[255];
unsigned short r;
int faults = 0;
int frameCounter = -1;
unsigned short holder;
int lruHold = 0;
int optIter = 0;
int position = 0;


void dequeue(){
  new_node = start;

  if(start == NULL){ //if nothing in the queue, return
    return;
  }

  if(start == end){ //if only 1 item in the queue
    start = NULL;
    end = NULL;
  }
  else{ //move it to the next position
    start = start->next;
  }
  frameCounter--;
  free(new_node); //free the node
  new_node = NULL; //reset the node
}



void enqueue(unsigned short logValue){
  new_node = (struct node*)malloc(sizeof(struct node));

  new_node->count = frameCounter;


  new_node->addrNum = logValue;
  new_node->next = NULL;
  if(start == NULL && end == NULL){
    position = new_node->position;
    start = new_node;
    end = new_node;
    return;
  }
  //printf("frame count: %d", frameCounter);
  end->next = new_node;
  frameCounter++;
  end = new_node;
}

void fifo(unsigned short logValue, int frameAmt){

  int i;
  if(pageTable[logValue] == -1){ //if its invalid (-1)
    //printf("HERE");
    if(counter < frameAmt){ //for the first set of frame amounts

      enqueue(logValue); //insert it on next frame

      pageTable[logValue] = frameCounter; //resetting

      physAddr[0] = pageTable[logValue]; //setting page
      counter++;
    }

    else{
      dequeue(); //remove it
      enqueue(logValue); //insert it on next frame

      pageTable[logValue] = frameCounter; //resetting
      physAddr[0] = pageTable[logValue];  //setting page

      faults++;
    }
  }

  else{
    physAddr[0] = pageTable[logValue]; //setting page
  }
}

void lru(unsigned short logValue, int frameAmt){
  int i;
  int nextHolder = 0;
  int least = 0;
  if(iteration > counter){ //past initial frames
    least = logAddr[iteration-(frameAmt-1)];

    if(logAddr[0] == least){
      faults++;
      logAddr[0] = logAddr[1];
    }
  }
  iteration++;

  if(pageTable[logValue] == -1){ //if its invalid (-1)
    if(counter < frameAmt){ //for the first set of frame amounts
      //printf("Position: %d", position);
      enqueue(logValue); //insert it

      pageTable[logValue] = frameCounter; //resetting

      physAddr[0] = pageTable[logValue]; //setting page
      counter++;

    }

    else{

      dequeue(); //remove it

      enqueue(logValue); //insert the value

      pageTable[logValue] = frameCounter; //resetting
      physAddr[0] = pageTable[logValue];  //setting page

      faults++;
    }
  }

  else{
    physAddr[0] = pageTable[logValue]; //setting page
    faults--;
  }
  lruHold = 1;
}

void opt(unsigned short logValue, int frameAmt){
  int i;
  optIter++;
  int z;
  for(z = optIter; z<100; z++){
    if(physAddr[0] == pageTable[logValue]){
      faults--;
      optIter++; //in the future so we will cycle through next to check if it is
      break;
    }
    else{
      physAddr[0] = pageTable[logValue];
      if(z == 99){
        break; //not in rest of future so replace and break out of loop
      }
    }
  }

  if(pageTable[logValue] == -1){ //if its invalid (-1)
    if(counter < frameAmt){ //for the first set of frame amounts

      enqueue(logValue); //insert it

      pageTable[logValue] = frameCounter; //resetting

      physAddr[0] = pageTable[logValue]; //setting page
      counter++;
      faults--;
    }

    else{
      dequeue(); //remove it
      enqueue(logValue); //insert the value

      pageTable[logValue] = frameCounter; //resetting
      physAddr[0] = pageTable[logValue];  //setting page

      faults++;
    }
  }

  else{
    physAddr[0] = pageTable[logValue]; //setting page

  }
  lruHold = 1;
}


void main(int argc, char *argv[]){
  int invalid = 0;
  char *p; //used for frame amount
  long frameAmt = strtol(argv[1], &p, 10); //for the input amount of frames

  char algoType = *argv[3];

  //printf("TYPE: %c\n", algoType);

    FILE *memory = fopen("mem.txt", "r"); //mem file

    int iter = 0; //iteration for while loop below


    while(iter != 255){

      fscanf(memory, "%255[^\n]%*c", &stringHolder); //scan the file and put strings of 255 characters into stringHolder
      strcpy(memoryStrings[iter], stringHolder); //copy string holder over to memoryStrings array
      pageTable[iter] = -1; //setting each frame as -1 for invalid
      //printf("%d\n", pageTable[iter]);
      iter++; //iteration to cycle through


    }
    if(algoType == 'F'){
      printf("First In First Out\n");
    }

    else if(algoType == 'L'){
      printf("Least Recently Used\n");
    }

    else if(algoType == 'O'){
      printf("Optimal\n");
    }
    else{
      printf("Invalid argument: %c\n", algoType);
      invalid = 1;
    }

    if(invalid == 0){
    while(scanf("%hu", (unsigned short*)logAddr) != EOF){



      q = *(unsigned short*)logAddr;

      holder = logAddr[0];

      logAddr[0] = logAddr[1];
      logAddr[1] = holder;
  //printf("%d\t%d\n", logAddr[0], frameAmt);
    if(algoType == 'F'){
      fifo(logAddr[0], frameAmt);
    }

    else if(algoType == 'L'){
      lru(logAddr[0], frameAmt);
    }

    else if(algoType == 'O'){
      opt(logAddr[0], frameAmt);
    }
    else{
    }


      physAddr[1] = logAddr[1]; //setting the offset for the physical address

      r = *(unsigned short*)physAddr;
      printf("%hu \t-> \t%hu \t-> \t%c\n", q, r, memoryStrings[logAddr[0]][logAddr[1]]);
    }
    printf("Faults: %d\n", faults);
  }
}
