/*----------------------------------------------
Name: Mohamad Kanafani                       |
ID: 0702067                                  |
Date: 03/28/2014                             |
Class: CIS 3110                              |
Assignment: Assignment 3: memory mangment    |
----------------------------------------------*/
#ifndef COMMONSIM_H
#define COMMONSIM_H

//proc specs
typedef struct proc {
	char id;
	int size;
	struct proc * next;
	int swap_count;
	int loc;
} proc;

/*function: sim_mem
 *queue : queue of processes to be put in memory
 *description: this function calls copy then the 
 *memory magment one by one the order is best, worst
 *next and first fit
*/
int sim_mem(proc * queue);

/*function: best_fit
 *queue : queue of processes to be put in memory(copy)
 *description: this function does best fit memory mangment simulation
*/
int best_fit(proc * queue);

/*function: worst_fit
 *queue : queue of processes to be put in memory(copy)
 *description: this function does worst fit memory mangment simulation
*/
int worst_fit(proc * queue);

/*function: next_fit
 *queue : queue of processes to be put in memory(copy)
 *description: this function does next fit memory mangment simulation
*/
int next_fit(proc * queue);

/*function: first_fit
 *queue : queue of processes to be put in memory(copy)
 *description: this function does first fit memory mangment simulation
*/
int first_fit(proc * queue);

/*function: find
 *mem : pointer to array that represent the memory
 *size : size of proc that is being loaded
 *type : type of memory magment
 *last : loction to start looking for holes in memory(only used for next fit)
 *usally its just 0
 *queue : queue of proc waiting to be loaded
 *in_mem : queue of proc in memory
 *holes : var that counts # of holes in memory
 *processes : var that counts the # of processes in memory
 *used : var that counts the total amount of memory used
 *description: this function finds the holes in momery and fits the proc that
 *is being loaded into memory, it also remove proc from memory if no space found
 *return : location of where the proc is loaded in memory
*/
int find(int * mem,int size,int type, int last ,proc * queue, proc * in_mem,int  * holes,int * processes,int * used);

/*function: add_mem
 *temp2 : queue of processes to be put in memory
 *tmep1 : queue of processes in memory
 *description: this function takes the proc in wait queue and insert it in 
 *memory queue
*/
void add_mem(proc * temp2, proc * temp1);

/*function: add_queue
 *new_thread : proc be removed from memory
 *tmep1 : queue of processes waiting to be loaded in memory
 *description: this function takes the proc in memory and insert it in 
 *wait queue
*/
void add_queue(proc * new_thread, proc * temp1);

/*function: clean_up
 *temp : queue of processes to be freed
 *description: this function frees the memory used by queues
*/
void clean_up(proc * temp);

/*function: last_used
 *mem : queue of processes in memory
 *used : var that counts the total memory used
 *description: this function finds the oldest proc in memory and remove it
 *return : the oldest proc in memory 
*/
proc * last_used(proc * mem, int * used);

/*function: set_mem
 *mem : int array of simulated memory (just 1  and 0)
 *loc : location in memory where the proc is inserted
 *size: size of proc being inserted
 *var : type of set(0 for removeing, 1 for adding)
 *description: this function set the simulated memory to 1 or 0
 *from the location tell location + size
*/
void set_mem(int * mem, int loc, int size , int var);

/*function: check
 *count : size of holes
 *type : type of memory mangment
 *best : best hole size found before(only used for best and worst fit)
 *i : current location in memory
 *size : size of proc being loaded
 *loc : var that will have the location in memory where proc is inserted in
 *description: this function checks if the hole is best or worst fit or
 *even the hole fits the proc
*/
void check(int count, int type, int * best, int i, int size, int * loc);

/*function: print
 *done : flag indicating what type of printing (end or during sim)
 *id : proc id
 *processes : proc number in memory
 *holes : # of holes in memory
 *totalHoles : total # of holes in simulation
 *used : current usage of memory
 *totalLoads : amount of proc loaded in memory
 *totalProcess : total # of proc in memory 
 *totalAverage : total average usage
 *description: this function prints the details of simulations
*/
void print(int done, char id, int processes, int holes,int totalHoles,int used,int totalLoads,int totalProcess,double totalAverage);

#endif
