#include <stdio.h>
#include <stdlib.h>

struct Node{
	int data;
	struct Node* next;
};
struct Node* head = NULL;
struct Node* tail = NULL;

void initialize(){
	head = NULL;
	tail = NULL;
}

void enqueue(int value){
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node)); //allocating memory for the dynamic size of the queue.
	temp->data = value; //data that temp is pointing to will be set to the value.
	temp->next = NULL; //temp pointing to address is originally set to null

	if(head == NULL && tail == NULL){ //if there are no nodes in the queue
		head = temp; //head will be linked to the only node
		tail = temp; //tail will also be linked to the only node
		return;
	}
		tail->next = temp; //current tail takes the memory address of the new tail to connect them
		tail = temp; //tail now points to the new end of the queue
	


}

void dequeue(){
	struct Node* temp = head;
	if(head == NULL){
		return; // if the queue is empty, return
	}

	if(head == tail){ //if there is only 1 node in the queue		
		head = NULL; // head will point to nothing since the only node was dequeued
		tail = NULL; // same with tail
	}

	else{
		head = head->next; //otherwise head is pointing to the next node in the queue
	}
	free(temp); //regardless of outcome, the node at head that temp is pointing to need to be removed.
	temp = NULL;
}

void display(void)
{
   	struct Node* temp = head;
	while(temp!=NULL){
		printf("\t%d",temp->data);
		temp=temp->next;

	}
	if(head == NULL){
		printf(" queue is empty.");
	}
}
int main(void) {
	initialize();

	int num = 0;

	while(scanf("%d,", &num) > 0){
	
		enqueue(num);

		display();
	}

		dequeue();
		display();
		dequeue();
		display();
		dequeue();
		display();
		dequeue();
		display();
}
