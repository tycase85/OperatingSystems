#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<semaphore.h>

void *agent();
void *smoker();

sem_t table; 

char* smoker_types[3] = {"Tobacco", "Paper", "Matches"};
int missing_item = 0;
int busy_table = 1;
int on_table1;
int on_table2;

void main (){
	

	sem_init(&table,0,1);

	int smokes0 = 0;
	int smokes1 = 1;
	int smokes2 = 2;

	int i;
		
	pthread_t p_agent;
	pthread_t p_smoker0;
	pthread_t p_smoker1;
	pthread_t p_smoker2;

	pthread_create(&p_agent, NULL, &agent, NULL);
	pthread_create(&p_smoker0, NULL, &smoker, (void*)&smokes0);
	pthread_create(&p_smoker1, NULL, &smoker, (void*)&smokes1);
	pthread_create(&p_smoker2, NULL, &smoker, (void*)&smokes2);
			
		
	
	pthread_join(p_agent,NULL);
	pthread_join(p_smoker0,NULL);
	pthread_join(p_smoker1,NULL);
	pthread_join(p_smoker2,NULL);

	sem_destroy(&table);
	
}

void *agent(){
	
	srand(time(NULL));
	char* item;
	int rand_num;

	while(1){
		busy_table = 1;
		rand_num = rand()%3;
		item = smoker_types[rand_num];

		if(rand_num == 0){
			on_table1 = 1;
			on_table2 = 2;
		}
		else if(rand_num == 1){
			on_table1 = 0;
			on_table2 = 2;
		}
		else{
			on_table1 = 0;
			on_table2 = 1;
		}

		sem_wait(&table);

		item = smoker_types[rand_num];
	
		printf("\nThe items on the table are: %s, %s\n", smoker_types[on_table1], smoker_types[on_table2]);
		 
	
		sem_post(&table);
		busy_table = 0;
		missing_item = rand_num;		
		sleep(5);

		
	}

	
}

void *smoker(void *argc){

	int arg = *(int*) argc;

	srand(time(NULL));
	int rand_sleep;

	while(1){


		rand_sleep = rand()%10 + 6;

		if(busy_table == 0){
			sem_wait(&table);
				if((arg != on_table1) && (arg != on_table2)){
				printf("The smoker adds %s and starts smoking.", smoker_types[missing_item]);  
				printf("\n");
				}
			sem_post(&table);
			sleep(6);
		}
	}
}
