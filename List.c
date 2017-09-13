#include <stdio.h>
#include <stdlib.h>

struct Node{
	int data;
	struct Node* next;
	struct Node* prev;
};
struct Node* head = NULL;
struct Node* tail = NULL;
struct Node* current = NULL;
struct Node* previous = NULL;

void initialize(){
	head = NULL;
	tail = NULL;
}

void add(int value){
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node)); 
	

	temp->data = value;
	temp->next = NULL;

	if(head == NULL && tail == NULL){ 
		head = temp;
		tail = temp;
		current = head;
		previous = NULL;
		return;
	}

	else{
		current = head;
		previous = head->next;

		while(value >= current->data){
			previous = current;
			current = current->next;
		}

		previous->next = temp;
		temp->next = current;
		

	}
		
			if(head->data == tail->data){
				if(temp->data < head->data){
					temp->next = head;
					head = temp;		
				}
				else{
					tail->next = temp;
					tail = temp;
				}
			}

		
	
	


}

void removes(void){
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
		printf("\t%d",temp->data);
		temp=temp->next;

	}
	if(head == NULL){
		printf(" list is empty.");
	}
}
int main(void) {
	initialize();

	int num = 0;

	while(scanf("%d,", &num) > 0){
	
		add(num);

		display();
	}

}
