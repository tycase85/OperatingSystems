#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<semaphore.h>

void *philosopher();

int chopStick[5] = {1, 1, 1, 1, 1}; 
sem_t table; 
int numOfPhil = 5;

void main (){
	sem_init(&table,0,1);

	int philo1 = 1;
	int philo2 = 2;
	int philo3 = 3;
	int philo4 = 4;
	int philo5 = 5;
		
	pthread_t p_phil1;
	pthread_t p_phil2;
	pthread_t p_phil3;
	pthread_t p_phil4;
	pthread_t p_phil5;

	
	pthread_create(&p_phil1, NULL, &philosopher, (void*)&philo1);
	pthread_create(&p_phil2, NULL, &philosopher, (void*)&philo2);
	pthread_create(&p_phil3, NULL, &philosopher, (void*)&philo3);
	pthread_create(&p_phil4, NULL, &philosopher, (void*)&philo4);
	pthread_create(&p_phil5, NULL, &philosopher, (void*)&philo5);	

	pthread_join(p_phil1,NULL);
	pthread_join(p_phil2,NULL);
	pthread_join(p_phil3,NULL);
	pthread_join(p_phil4,NULL);
	pthread_join(p_phil5,NULL);

	sem_destroy(&table);
	
}

void *philosopher(void *argc){
	
	int philNum = *(int*) argc;
	int i;
	int chopLeft = philNum-1;
	int chopRight = philNum;

	if(chopRight = 5){
		chopRight = 0;
	}


	while(1){
		if(chopStick[chopLeft] == 1 && chopStick[chopRight] == 1){
			sem_wait(&table);
			printf("\nPhilosopher %d is eating.\n", philNum);
			chopStick[chopLeft] = 0; //in use
			chopStick[chopRight] = 0; //in use
			sleep(2);
			printf("\nPhilosopher %d finished eating.\n", philNum);
			chopStick[chopLeft] = 1; //finished using
			chopStick[chopRight] = 1; //finished using
			sem_post(&table);
			
		}

		else{
			printf("\nPhilosopher %d is thinking. \n", philNum);
			sleep(2);
		}
		
		sleep(2);
		
	
	}
	
}
