#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>

//By: Robert Tyler Case 3502846
//gcc -o RobertCase_A4_Q1 RobertCase_A4_Q1.c
//./RobertCase_A4_Q1 12 mem.txt < sample_logical_addr.txt


unsigned char page[100];  //page table
int pageFaultAmt = 0; //holder for page faults
unsigned short *frame[100] = { NULL }; //setting up frames
int firstIn = 0; //for FIFO
int logLength = 0; //Logical address length
int count = 0; //counter used in FIFO
unsigned char memoryStrings[256][256]; //holds 256 char string
unsigned short logAddr; //for conversion later

void main (int argc, char * argv[]){

  unsigned char pageTable; //first half of logical address
  unsigned char offset; //second half of logical address

  int iter = 0; //iteration for while loop below

  char *p; //used for frame amount
  long frameAmt = strtol(argv[1], &p, 10); //for the input amount of frames


  FILE *memory = fopen("mem.txt", "r"); //mem file
  FILE *logical = fopen("sample_logical_addr.txt", "r"); //logical address file
  unsigned char memFile[256][256]; //will hold the memory file's string


  unsigned char stringHolder[255]; //holds the string at 256 characters

  while(iter != 255){

    fscanf(memory, "%255[^\n]%*c", &stringHolder); //scan the file and put strings of 255 characters into stringHolder
    strcpy(memoryStrings[iter], stringHolder); //copy string holder over to memoryStrings array


    page[iter] = 'i'; //setting each page as i for invalid
    iter++; //iteration to cycle through


  }

  	while(scanf("%d", &logAddr) != EOF){ //going through all the logical addresses in the file
      logLength++; //holds the amount of addresses
      fscanf(logical, "%d %*[\n]", &logAddr);
      pageTable = (logAddr & 0xFF00) >> 8; //setting binary value for page table for later
      offset = (logAddr & 0x00FF); //setting binary value for offset for later
      pageTableLookup(pageTable, frameAmt, offset); //looking up values in page table
    }
    pageFaultAmt = pageFaultAmt - frameAmt;
    printf(" \nPage Faults: %d\n", pageFaultAmt); //amount of page faults at the end

}

int frames(int pageTable, long frameAmt, int offset){

  int holder = 0; //holder for resetting the loop
  unsigned char physAddr[2]; //for conversion from binary number to address
  unsigned short q; //for print statement later

  while(frame[firstIn] != NULL && logLength != 0){ //while this frame does not equal null and it hasn't cycled through all logical addresses

    if(firstIn+1 == frameAmt){ //check for when it gets to the end of the frame amount
      count++; //counter for the amount of frames cycles
      frame[firstIn+1] = NULL; //reseting the value stored in that frame
      firstIn++; //setting next first value
      holder = 1; //only hits this the first time of each loop to do the if down below
      break;
    }
    else{ //otherwise go to the next frame
      firstIn++;
    }

  }

  logLength--; //each time remove the amount of addresses
  if(holder == 1){ //when this is hit at the start of each frame cycle
    if(count == frameAmt){ //if at the end of the amount of allotted frames
      count = 0; //reset counter
      firstIn = 0; //reset the first in for FIFO
    }
  }
  page[pageTable] = firstIn; //setting value into page table to overwrite i
  frame[firstIn] = pageTable; //frame now holds the pagetable number

  //printf(" \nLogical Address: %d - %d", pageTable, offset);
  //printf(" \tPhysical Address: %d - %d", firstIn, offset);
  //printf(" \tChar: %c\n", memoryStrings[pageTable][0]);

  physAddr[0] = firstIn;
  physAddr[1] = offset;
  q = *(unsigned short*) physAddr;
  printf("%d \t-> \t%hu \t-> \t%c\n", logAddr, q, memoryStrings[pageTable][offset]);
  //printf("%d%d \t-> \t%d%d \t-> \t%c\n", pageTable, offset, firstIn, offset, memoryStrings[pageTable][offset]);
}

void pageTableLookup(int pageTable, long frameAmt, int offset){

  if(page[pageTable] == 'i'){ //after looking up in page table if its invalid
    pageFaultAmt++; //increase holder for page fault
    frames(pageTable, frameAmt, offset); //doing all the fifo stuff in the next method
  }

}
