#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<semaphore.h>

void *arriveBridge();
void *exitBridge();

sem_t table; 


int northBound = 0; //amount going north
int southBound = 0; //amount going south

char carName[1024]; //for input
char direction[1024]; //for input
int arrival; //for input

int arr[100]; //holds all arrival times
int direct[100]; //holds all directions converted to integer
char *names[1024]; //holds all car names

int cars = 0; //amount of cars
int carsOnBridge = 0; //cars currently on bridge
int currDirection;//current direction of traffic

int iteration = 0; //iteration for arriveBridge
int getOffBridge = 0;

void main (){
	sem_init(&table,0,1);
	int i;

	char buffer[1024];
	fgets(buffer, sizeof(buffer), stdin);

	while(scanf("%s %s %d", carName, direction, &arrival) != EOF){
		
		if(strcmp(direction, "N") == 0){
			direct[cars] = 0;
		}
		else{
			direct[cars] = 1;
		}
		printf("\n");
		arr[cars] = arrival;
		names[cars] = malloc(sizeof(char*)*strlen(carName));
		strcpy(names[cars], carName);
		
		pthread_t p_car[cars];
		pthread_create(&p_car[cars], NULL, &arriveBridge, (void*)&cars);
		
		pthread_join(p_car[cars],NULL);

		while(getOffBridge == 0){
			sleep(3);
		} 
		pthread_create(&p_car[cars], NULL, &exitBridge, (void*)&cars);
		pthread_join(p_car[cars],NULL);
		cars++;
		
	}


	sem_destroy(&table);

}

void *arriveBridge(void *argc){
	int carNum = *(int*) argc;//the car in the array


	while(iteration < cars+1){ //run for how many cars there are.	

		sem_wait(&table);
		if(carNum == 0){ //for first car
			currDirection = direct[carNum];
			if(direct[carNum] == 0){
				printf("\n");
				printf("Direction: North\n");
				printf("%s", names[carNum]);
				carsOnBridge++;
				sleep(5);
				getOffBridge = 1;
			}			
			else{
				printf("\n");
				printf("Direction: South\n");
				printf("%s", names[carNum]);
				carsOnBridge++;
				sleep(5);
				getOffBridge = 1;
			}
		}


		else if(direct[carNum] == currDirection){ //car arrives and their direction is crossing
					
			if(carsOnBridge != 3){ //if bridge isnt full, car gets on	
				printf("%s", names[carNum]);		
				carsOnBridge++;
				sleep(5);
					getOffBridge = 1;
			}
			else{ //if bridge is full, sleep loop until a free spot appears
				while(carsOnBridge == 3){
					sleep(3);
				}
				printf("%s", names[carNum]);		
				carsOnBridge++;
				sleep(5);
						getOffBridge = 1;
			}
		}

		else if(direct[carNum] != currDirection){ //if not currently your direction
				while(carsOnBridge != 0){ //if there are still cars on the bridge					
					sem_post(&table);
					sleep(3);
				}
		
				currDirection = direct[carNum];
				if(direct[carNum] == 0){
					printf("\n");
					printf("Direction: North\n");
					printf("%s", names[carNum]);
					carsOnBridge++;
					sleep(5);
					getOffBridge = 1;
				}			
				else{
					printf("\n");
					printf("Direction: South\n");
					printf("%s", names[carNum]);
					carsOnBridge++;
					sleep(5);
					getOffBridge = 1;
				}
			
		}
		
		iteration++;
		sem_post(&table);
	}

}

void *exitBridge(void *argc){
	int carNum = *(int*) argc;//the car in the array

	//printf("Car %d got off the bridge.", carNum);
	carsOnBridge--;



}
