/*----------------------------------------------
Name: Mohamad Kanafani                       |
ID: 0702067                                  |
Date: 03/28/2014                             |
Class: CIS 3110                              |
Assignment: Assignment 3: memory mangment    |
----------------------------------------------*/
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "commonSim.h"
#include "fileReader.h"

#define MAX_MEM 128

//frees memory for the queues
void clean_up(proc * temp){
	proc * temp1 = temp->next;
	proc * hold;
	if(temp1 != NULL){
		while(temp1 != NULL){
			hold = temp1->next;
			free(temp1);
			temp1 = hold;
		}
	}
}

//prints the required output
void print(int done, char id, int processes, int holes,int totalHoles,int used,int totalLoads,int totalProcess,double totalAverage){
	if(!done){
		printf("Process %c loaded, #processes = %d, ",id, processes);
		printf("#holes = %d, %%memUsage = %.2lf, ", holes,((double)used/MAX_MEM)*100);
		printf("cumulative %%memUsage = %.2lf\n", totalAverage/totalLoads);
	}else{
		printf("Total Loads = %d, average #processes = %.2f, ", totalLoads, (double)totalProcess/totalLoads);
		printf("average #holes = %.2f, cumulative %%memUsage = %.2f\n\n", ((double)totalHoles/totalLoads),(double)(totalAverage/totalLoads));
	}
}
int sim_mem(proc * queue){
//make 3 copy of proc
/*to do
*1.best fit
*	- need look function
*2.worst fit
*	- need look up function(can use same)
*3.next fit
*	-need pointer to current location in mem
*4.first fit
*	-need look up function(same as 2 and 3)*/
	printf("Starting Simulation For Best Fit\n******************************************************\n");
	best_fit(copy(queue));
	printf("Starting Simulation For Worst Fit\n******************************************************\n");
	worst_fit(copy(queue));
	printf("Starting Simulation For Next Fit\n******************************************************\n");
	next_fit(copy(queue));
	printf("Starting Simulation For First Fit\n******************************************************\n");
	first_fit(copy(queue));	
	clean_up(queue);
	return 0;
}
int best_fit(proc * temp){
	int mem[MAX_MEM] = {0};
	proc in_mem; 
	proc queue;
	int loc = 0;
	int processes = 0;
	int used = 0;
	int holes = 0;
	int totalProcess = 0;
	int totalHoles = 0;
	int totalLoads = 0;
	double totalAverage = 0.0;
	in_mem.next = NULL;
	queue.next = temp;
	while(queue.next != NULL){
		loc = find(mem,queue.next->size,0, 0 ,&queue,&in_mem,&holes,&processes,&used );
		queue.next->loc = loc;
		totalHoles += holes;
		totalAverage += (((double)used/MAX_MEM)*100);
		totalLoads++;
		totalProcess+=processes;
		print(0, queue.next->id,processes,holes,totalHoles,used,totalLoads,totalProcess,totalAverage);
		add_mem(&queue, &in_mem);
		holes = 0;
	}
	print(1,'.',processes,holes,totalHoles,used,totalLoads,totalProcess,totalAverage);
	clean_up(&in_mem);
	clean_up(&queue);
	return 0;
}
int worst_fit(proc * temp){
	int mem[MAX_MEM] = {0};
	proc in_mem; 
	proc queue;
	int loc = 0;
	int processes = 0;
	int used = 0;
	int holes = 0;
	int totalProcess = 0;
	int totalHoles = 0;
	int totalLoads = 0;
	double totalAverage = 0.0;
	in_mem.next = NULL;
	queue.next = temp;
	while(queue.next != NULL){
		loc = find(mem,queue.next->size,1, 0 ,&queue,&in_mem,&holes,&processes,&used );
		queue.next->loc = loc;
		totalHoles += holes;
		totalAverage += (((double)used/MAX_MEM)*100);
		totalLoads++;
		totalProcess+=processes;
		print(0, queue.next->id,processes,holes,totalHoles,used,totalLoads,totalProcess,totalAverage);
		add_mem(&queue, &in_mem);
		holes = 0;
	}
	print(1,'.',processes,holes,totalHoles,used,totalLoads,totalProcess,totalAverage);
	clean_up(&in_mem);
	clean_up(&queue);
	return 0;
}
int next_fit(proc * temp){
	int mem[MAX_MEM] = {0};
	proc in_mem; 
	proc queue;
	int loc = 0;
	int processes = 0;
	int used = 0;
	int holes = 0;
	int totalProcess = 0;
	int totalHoles = 0;
	int totalLoads = 0;
	double totalAverage = 0.0;
	in_mem.next = NULL;
	queue.next = temp;
	while(queue.next != NULL){
		loc = find(mem,queue.next->size,2, loc ,&queue,&in_mem,&holes,&processes,&used );
		queue.next->loc = loc;
		totalHoles += holes;
		totalAverage += (((double)used/MAX_MEM)*100);
		totalLoads++;
		totalProcess+=processes;
		print(0, queue.next->id,processes,holes,totalHoles,used,totalLoads,totalProcess,totalAverage);
		add_mem(&queue, &in_mem);
		holes = 0;
	}
	print(1,'.',processes,holes,totalHoles,used,totalLoads,totalProcess,totalAverage);
	clean_up(&in_mem);
	clean_up(&queue);
	return 0;
}
int first_fit(proc * temp){
	int mem[MAX_MEM] = {0};
	proc in_mem; 
	proc queue;
	int loc = 0;
	int processes = 0;
	int used = 0;
	int holes = 0;
	int totalProcess = 0;
	int totalHoles = 0;
	int totalLoads = 0;
	double totalAverage = 0.0;
	in_mem.next = NULL;
	queue.next = temp;
	while(queue.next != NULL){
		loc = find(mem,queue.next->size,3, 0 ,&queue,&in_mem,&holes,&processes,&used );
		queue.next->loc = loc;
		totalHoles += holes;
		totalAverage += (((double)used/MAX_MEM)*100);
		totalLoads++;
		totalProcess+=processes;
		print(0, queue.next->id,processes,holes,totalHoles,used,totalLoads,totalProcess,totalAverage);
		add_mem(&queue, &in_mem);
		holes = 0;
	}
	print(1,'.',processes,holes,totalHoles,used,totalLoads,totalProcess,totalAverage);
	clean_up(&in_mem);
	clean_up(&queue);
	return 0;
}
//check if hole is best or worst fit
void check(int count, int type, int * best, int i, int size, int * loc){
	if(count >= size){	
		if(*best == 0){
			*best = count;
			*loc = i-count;
		}else{
			switch(type){
				case 0: if(count < *best){
						*best = count;
						*loc = i-count;
					}
				break;
				case 1: if(count > *best){
						*best = count;
						*loc = i-count;
					}
				break;
			}	
		}
	}
}

//counts the holes and finds where to place proc in memory
int find(int * mem,int size,int type, int last ,proc * queue, proc * in_mem,int  * holes,int * processes,int * used){
	int i = 0;
	int count = 0;
	int best = 0;
	int start = 0;
	int loc = -1;
	if(type == 2){
		start = last;
	}
	//look for zeros
	for(i = start;i < MAX_MEM; i++){		
		if(mem[i] == 0){
			count++;
		}else if(count > 0){
			*holes = *holes + 1;
			check(count,type,&best,i,size,&loc);
			count = 0;
		}
	}
	check(count,type,&best,i,size,&loc);
	//check hole at end of memory
	if(count > 0){
		*holes = *holes + 1;
	}
	//if hole is same size hole is removed
	if(best == size){
		*holes = *holes - 1;
	}
	if(loc == -1){
		proc * temp = last_used(in_mem, used);
		//remove old one and recheck
		if(temp != NULL){
			set_mem(mem,temp->loc,temp->size+temp->loc,0);
			temp->loc = 0;
			add_queue(temp,queue);
			*processes = *processes - 1;
			*holes = 0;
			return find(mem, size, type, 0,queue,in_mem,holes,processes,used);
		}else{

			return 0;
		}
	}else{		
		//found hole set it
		set_mem(mem,loc,size+loc,1);
		*used = *used + size;
		*processes = *processes +1;
		return loc;
	}
}

//sets the simuated memory to 1 or 0
void set_mem(int * mem, int loc, int size , int var){
	int i;
	for(i = loc; i < size; i++){
		mem[i] = var;
	}
}

//remove from front(oldest) of mem queue and returns it
proc * last_used(proc * mem, int * used){
	proc * temp = mem->next;
	proc * hold = NULL;
	if(temp != NULL){
		hold = temp;
		mem->next = temp->next;
		hold->next = NULL;		
		*used = *used - hold->size;
		return hold;
	}
	return NULL;
}
//moves proc from wait to in memory queue
void add_mem(proc * temp2, proc * temp1){
	proc * ready = temp1->next;
	proc * new_thread = temp2->next;
	new_thread->swap_count++;	
	if(new_thread != NULL){
		if(ready == NULL){
			temp1->next = new_thread;
			temp2->next = new_thread->next;
			new_thread->next = NULL;			
		}else{
			while(ready->next != NULL){
				ready = ready->next;
			}
			ready->next = new_thread;
			temp2->next = new_thread->next;
			new_thread->next = NULL;
		}
	}	
}
//adds the proc to wait queue
void add_queue(proc * new_thread, proc * temp1){
	proc * ready = temp1->next;
	if(new_thread->swap_count < 3){
		if(new_thread != NULL){
			if(ready == NULL){
				temp1->next = new_thread;
			}else{
				while(ready->next != NULL){
					ready = ready->next;
				}
				ready->next = new_thread;
			}
		}
	}else{
		free(new_thread);
		new_thread = NULL;
	}
}
