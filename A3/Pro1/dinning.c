/*------------------------------------------------------------------------------------------------------
Name: Mohamad Kanafani                       								|
ID: 0702067                                  								|
Date: 28/03/2014                             								|
Class: CIS 3110                              								|
Assignment: Assignment 3: dinning phil     								|
 *The outline for this program was obtained from RosettaCode.						|
 *				Address: http://rosettacode.org/wiki/Dining_philosophers#C              |
 *				Date Accessed: March 18, 2014						|
-------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <pthread.h>
#include "common.h"

void * start(void * phil){
	Philosopher * temp = (Philosopher*) phil;//uncast teh struct
	do{//main loop until done eating
		think(temp);
		error(eat(temp));
	}while(temp->eat > 0);
	printf("Philosopher %d is done.\n", temp->id+1);
	pthread_exit(NULL);
}

int creat(int num,int eat_times){
	//creat memory for struct and forks
	pthread_mutex_t * fork = malloc(sizeof(pthread_mutex_t) * num);
	Philosopher * philosophers = malloc(sizeof(Philosopher) * num);
	int i;
	//init mutux
	for(i = 0; i< num; i++){
		if(pthread_mutex_init(&fork[i],NULL) != 0){
			return 1;
		}
	}
	//init the struct for philosophers
	for(i =0; i < num; i++){
		philosophers[i].left = &fork[i];
		if((i+1)>=num){
			philosophers[i].right = &fork[0];
		}else{
			philosophers[i].right = &fork[i+1];
		}
		philosophers[i].eat = eat_times;
		philosophers[i].id = i;
		//creat the thread and pass the start function
		if(pthread_create( &philosophers[i].thread, NULL, &start, (void*)&philosophers[i]) != 0){
			return 2;
		}
	}
	//wait 10s for simulation to go or finish
	sleep(10);
	return Clean_up( philosophers,fork,num);
}
int Clean_up(Philosopher * temp,pthread_mutex_t *  fork, int num){
	int i;
	//join the threads
	for(i = 0; i < num; i++){
		if(pthread_join(temp[i].thread,NULL) != 0){
			return 3;
		}else{
			//if join is good destroy the mutux attached to it
			if(pthread_mutex_destroy(&fork[i]) != 0){
				return 4;
			}
		}	
	}
	//free memory
	free(temp);
	free(fork);
	return 0;
}

int eat(Philosopher * temp){
	//check if done eating
	if(temp->eat > 0){
		//try getting left fork first
		if(pthread_mutex_lock(temp->left) == 0){
			//get right fork
			if(pthread_mutex_lock(temp->right) == 0){
				printf("Philosopher %d is eating.\n", temp->id+1);
				temp->eat -= 1;
				//go to sleep to simulate eating
				usleep(250000 + rand()%500000);
				//release forks same way accuried to avoid deadlock
				pthread_mutex_unlock(temp->left);
			}else{
				return 5;
			}
			pthread_mutex_unlock(temp->right);
		}else{
			return 5;
		}
	}
	return 0;
}
int think(Philosopher * temp){
	//sleep to simulate thinking
	printf("Philosopher %d is thinking.\n", temp->id+1);
	usleep(2500000+ rand()%5000000);
	return 0;
}
void error(int error){
	switch(error){
		case 0:
		break;
		case 1:printf("ERROR mutex failed to init!\n");
				exit(1);
		break;
		case 2:printf("ERROR threads failed to creat!\n");
				exit(1);
		break;
		case 3:printf("ERROR threads failed to close!\n");
				exit(1);
		break;
		case 4:printf("ERROR mutex failed to destroy!\n");
				exit(1);
		break;
		case 5:printf("ERROR mutex failed to lock!\n");
				exit(1);
		break;
		default:printf("no error!\n");
		break;			
	}
}
