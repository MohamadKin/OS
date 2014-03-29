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
#ifndef COMMON_H
#define COMMON_H
//struct represent each phil
typedef struct data {
    pthread_mutex_t * left, * right;
    pthread_t thread;
	int eat;
	int id;
} Philosopher;

/*function: start
 *phil : the struct of Philosopher casted to void
 *description: this function runs all threads
*/
void * start(void * phil);
/*function: creat
 *num : number of philosopher and forks
 *eat_times: number of times the philosopher eats
 *description: this function inits the threads and mutux 
 *and calls clean up after waitng for 10s
*/
int creat(int num,int eat_times);
/*function: Clean_up
 *temp: the struct of philosopher that has all threads
 *fork: the resource that needs to be destroyed
 *num: the amount of philosophers and mutux
 *description: joins all threads and destroys the mutux and free mem
*/
int Clean_up(Philosopher * temp,pthread_mutex_t *  fork, int num);
/*function: eat
 *temp:the struct of philosopher that has all threads
 *description: this function simulates eating the phil waits for forks
 *then sleep for rand number of time
*/
int eat(Philosopher * temp);
/*function: think
 *temp:the struct of philosopher that has all threads
 *description: this function simulates thinkng the phil
 *it sleeps for rand number of time
*/
int think(Philosopher * temp);
/*function: error
 *error : error code
 *description: this function takes error code and prints
 *out the decoded error
*/
void error(int error);
/*function: check_arg
 *argv : the 2d array of command line arguments
 *argc: number of command line arguments
 *num: var to hold the number of philosophers
 *eat: var that will hold the amount of times to eat
 *description: this function checks the command line arguments 
 * if correct will update teh eat and num values
*/
int check_arg(int argc, char * argv[], int * num,int * eat);

#endif
