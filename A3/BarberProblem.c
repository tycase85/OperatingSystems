#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<semaphore.h>

void *barber();
void *customer();

sem_t table; 

int numOfCust = 0;
int sleeping = 0;
int numOfChairs = 5;

void main (){
	sem_init(&table,0,1);
		
	pthread_t p_barber;
	pthread_t p_customer0;
	pthread_t p_customer1;
	pthread_t p_customer2;

	
	pthread_create(&p_customer0, NULL, &customer, NULL);
	pthread_create(&p_customer1, NULL, &customer, NULL);
	pthread_create(&p_customer2, NULL, &customer, NULL);		
	pthread_create(&p_barber, NULL, &barber, NULL);	
	
	pthread_join(p_customer0,NULL);
	pthread_join(p_customer1,NULL);
	pthread_join(p_customer2,NULL);
	pthread_join(p_barber,NULL);

	sem_destroy(&table);
	
}

void *barber(){
	
	srand(time(NULL));
	char* item;
	int rand_num;
	printf("\nThe Barber checks the waiting room...\n");
	sleep(2);
	while(1){
		sleeping = 0;
		if(numOfCust != 0){
			sem_wait(&table);
			printf("\nThe Barber brings a client to the chair.\n");
			printf("The Barber is cutting a Customer's hair.\n");
			sleep(2); 
			printf("\nThe Barber is finished cutting the Customer's hair.\n");
			numOfChairs++;
			numOfCust = numOfCust - 1;
			sleep(1); 
			printf("\nCustomer Dismissed.\n");		
			sem_post(&table);
				
			printf("\nThe Barber checks the waiting room...\n");
		}

		else{
			printf("\nSleeping ZZZ\n");
			sleeping = 1;
			sleep(2); 
		}		
	}
	
	
}

void *customer(){

	while(1){

		if(sleeping == 1){
			printf("\nWAKING BARBER!\n");
			sleeping = 0;	
			sem_post(&table);	
		}

		if(numOfChairs != 0 && numOfCust <= 5){
			numOfCust++;
			numOfChairs--;
			printf("\nNUM OF CUST:%d  .... NUM OF CHAIRS: %d\n", numOfCust, numOfChairs);
		}
		else{
			printf("\nThe Waiting room is full. I will leave now.\n");
		}
		sleep(7);
	}
}
