#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#define MAX_CHAR 100
//By: Robert Tyler Case 3502846
//gcc -o RobertCase_A6_Q1 RobertCase_A6_Q1.c
//./RobertCase_A6_Q1 10 mem.txt < sample_logical_input6.txt

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
unsigned char logAddrArr[100][100];
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
char *firstChar;
char *secondChar;
int fifoHolder = 0;
int dirtyCounter = 0;

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
      faults++;
    }

    else{
      if(fifoHolder == 1){

        dirtyCounter++;
        //set new character using write on that position with second char!!!!


        //printf("%c\n", memoryStrings[logAddr[0]][logAddr[1]]);
      }
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


void main(int argc, char *argv[]){

  int stringCounter = 0;
  int invalid = 0;
  char *p; //used for frame amount
  long frameAmt = strtol(argv[1], &p, 10); //for the input amount of frames

  //char algoType = *argv[3];

  //printf("TYPE: %c\n", algoType);

    FILE *memory = fopen("mem.txt", "r+"); //mem file
    int iter = 0; //iteration for while loop below
    char string[MAX_CHAR];
    int lineCount = 0;


    while(iter != 255){

      fscanf(memory, "%255[^\n]%*c", &stringHolder); //scan the file and put strings of 255 characters into stringHolder
      strcpy(memoryStrings[iter], stringHolder); //copy string holder over to memoryStrings array
      pageTable[iter] = -1; //setting each frame as -1 for invalid
      //printf("%d\n", pageTable[iter]);
      iter++; //iteration to cycle through


    }

    while(scanf("%hu", (unsigned short*)logAddr) != EOF){

      scanf(" %c", &firstChar);
      //printf("first: %c\n", firstChar);

      if(firstChar == 'W'){
        scanf(" %hu", (unsigned short*)logAddr);
        scanf(" %c", &secondChar);

        //printf("first: %c\n", firstChar);
        //printf("Second: %c\n", secondChar);

        fifoHolder = 1;

        q = *(unsigned short*)logAddr;
              lineCount++;

        //printf("%hu -> [0]::%hu   [1]::%c\n", q, logAddr[0], logAddr[2]);

              holder = logAddr[0];

              logAddr[0] = logAddr[1];
              logAddr[1] = holder;
          //printf("%d\t%d\n", logAddr[0], logAddr[1]);
              fifo(logAddr[0], frameAmt);
              //printf("Second: %c\n", secondChar);

              physAddr[1] = logAddr[1]; //setting the offset for the physical address

              r = *(unsigned short*)physAddr;
              //memoryStrings[logAddr[0]][logAddr[1]] = secondChar;
              //fseek(memory, logAddr, SEEK_SET);

              fseek(memory, q, SEEK_SET);
              fwrite(&secondChar, sizeof(char), 1, memory);
              memoryStrings[logAddr[0]][logAddr[1]] = secondChar;
              printf("%hu \t-> \t%hu \t-> \t%c\n", q, r, secondChar);

      }
      else if(firstChar == 'R'){
        //printf("first: %c\n", firstChar);
        scanf(" %hu", (unsigned short*)logAddr);

        q = *(unsigned short*)logAddr;
              lineCount++;

        //printf("%hu -> [0]::%hu   [1]::%c\n", q, logAddr[0], logAddr[2]);

              holder = logAddr[0];

              logAddr[0] = logAddr[1];
              logAddr[1] = holder;
          //printf("%d\t%d\n", logAddr[0], logAddr[1]);
              fifo(logAddr[0], frameAmt);


              physAddr[1] = logAddr[1]; //setting the offset for the physical address

              r = *(unsigned short*)physAddr;
              printf("%hu \t-> \t%hu \t-> \t%c\n", q, r, memoryStrings[logAddr[0]][logAddr[1]]);

      }


    }
    printf("Faults: %d\n", faults);
    printf("Dirty Pages: %d\n", dirtyCounter);


}
