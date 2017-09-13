#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
	char *user;
	char *process;
	int arrival;
	int duration;
	
	struct Node* next;
};
struct Node* head = NULL;
struct Node* tail = NULL;

void initialize(){
	head = NULL;
	tail = NULL;
}

void enqueue(char *newUser, char *newProcess, int newArrival, int newDuration){
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node));

	strcpy(temp->user, newUser);
	strcpy(temp->process, newProcess);
	temp->arrival = newArrival;
	temp->duration = newDuration;
	temp->next = NULL; 

	if(head == NULL && tail == NULL){ 
		head = temp; 
		tail = temp; 
		return;
	}
		tail->next = temp;
		tail = temp;
	


}

void dequeue(){
	struct Node* temp = head;
	if(head == NULL){
		return; 
	}

	if(head == tail){	
		head = NULL; 
		tail = NULL;
	}

	else{
		head = head->next; 
	}
	free(temp); 
	temp = NULL;
}

void display(void)
{
   	struct Node* temp = head;
	while(temp!=NULL){
		printf("\t%d",temp->user);
		printf("\t%d",temp->process);
		printf("\t%d",temp->arrival);
		printf("\t%d",temp->duration);
		temp=temp->next;

	}
	if(head == NULL){
		printf(" queue is empty.");
	}
}
int main(void) {
	initialize();
	char *user, *process;
	int arrival, duration;
	
	char *test = (char*)malloc(100);
	scanf("%c %c %c %c", &user, &process, &arrival, &duration);
	printf("%c %c %c %c", &user, &process, &arrival, &duration);
	free(test);
	

	while(scanf("%c %c %d %d", &user, &process, &arrival, &duration)){
	
		enqueue(user, process, arrival, duration);

		
	}
	display();
}
