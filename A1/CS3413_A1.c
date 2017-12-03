#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
	char *user;
	char *process;
	int arrival;
	int duration;
	int final_time;
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
	temp->user = malloc(sizeof(char)*(strlen(newUser)+1));
	temp->process = malloc(sizeof(char)*(strlen(newProcess)+1));
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
	free(temp->user); //used for the mallocs in enqueue.
	free(temp->process);  
	free(temp); 
	temp = NULL;
}

void display(void)
{
   	struct Node* temp = head;

	int time = temp->arrival;

	while(temp!=NULL){
		printf("%d", time);	
		printf("\t");
		printf("%s", temp->process);
		time = time + temp->duration;	
		temp = temp->next;
		printf("\n");

	}
	printf("%d\tIDLE", time);

	if(head == NULL){
		printf(" queue is empty.");
	}
}

void summary(int i){
	struct Node* temp = head;

	char *names[100];
	int l, m;
	int space = 0;
	int amntNewList = 0;
	int dupe = 0;
	int finish[100];
	int tTime = 0;
	int dupeHold = 0;

	//sets 100 spaces as 0 for future time input
	for(space = 0; space<100; space++){
		finish[space] = 0;
	} 
	
	printf("\nSummary");
	//while node has values
	while(temp!=NULL){
	dupe = 0; 
	//used for first case when tTime is still 0
	if(tTime < temp->arrival){
		tTime = temp->arrival;
	}
		//adding unique entries to new array
		for(l = 0; l < amntNewList; l++){
			//comparing entries with other entries in new array.
			//if a duplicate is found
			if(strcmp(temp->user, names[l]) == 0){
				//so that a smaller time value doesnt overwrite later on
				if(finish[l] < tTime + temp->duration){
					finish[l] = tTime + temp->duration;
					dupeHold = tTime + temp->duration;
				}
				dupe = 1;
			}
		}
		//if this isnt a duplicate
		if(dupe == 0){
			//creating new time
			finish[amntNewList] = tTime + temp->duration;
			//adding new name to array
			names[amntNewList] = temp->user;
			//moving to next position
			amntNewList++;		
			//holder for previous total time value
			tTime = finish[amntNewList-1];	
		}
		else if(dupe == 1){
			tTime = dupeHold;
		}
		//moving forward on node
		temp = temp->next;
	}
	//loop for printing
	for(m = 0; m < amntNewList; m++){	
		printf("\n%s\t%d", names[m], finish[m]);
	}

}
int main(void) {
	initialize();
	char user[1024], process[1024];
	int arrival, duration;
	char buffer[1024];
	
	int iteration = 0;
	fgets(buffer, sizeof(buffer), stdin);
	//scanf("%s %s %s %s", user, process, arrival, duration);
	//printf("%s %s %s %s", &user, &process, &arrival, &duration);
	
	//printf("%s", buffer);

	while(scanf("%s %s %d %d", user, process, &arrival, &duration) != EOF){
		
		iteration++;
		//printf("\n %s %s %d %d", user, process, arrival, duration);
		enqueue(user, process, arrival, duration);
		
	}
	printf("\n");
	printf("\nTime\tJob\n");
	display();
	printf("\n");
	summary(iteration);

}
