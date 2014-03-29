/*----------------------------------------------
Name: Mohamad Kanafani                       |
ID: 0702067                                  |
Date: 28/02/2014                             |
Class: CIS 3110                              |
Assignment: Assignment 2: CPU Schuduling     |
----------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

#include "sim.h"
#include "queue.h"
#include "common_sim.h"

//moves threads from new to ready queue
void add_ready(proc * new_thread, proc * ready){
	if(new_thread->head_thread != NULL){
		if(ready->head_thread == NULL){
			ready->head_thread = new_thread->head_thread;
			new_thread->head_thread = new_thread->head_thread->next;
			ready->head_thread->next = NULL;
		}else{
			thread * temp = ready->head_thread;
			while(temp->next != NULL){
				temp = temp->next;
			}
			temp->next = new_thread->head_thread;
			new_thread->head_thread = new_thread->head_thread->next;
			temp->next->next = NULL;
		}
	}
}
//add thread to the blocked queue from ready/running queue
void add_blocked(proc * ready, proc * blocked,int * block_time, int time){
	if(ready->head_thread != NULL){
		if(blocked->head_thread == NULL){
			blocked->head_thread = ready->head_thread;
			ready->head_thread = ready->head_thread->next;
			blocked->head_thread->next = NULL;
			*block_time = blocked->head_thread->CPU_burst->IO_time + time;			
		}else{
			thread * temp = blocked->head_thread;
			while(temp->next != NULL){
				temp = temp->next;
			}
			temp->next = ready->head_thread;
			ready->head_thread = ready->head_thread->next;
			temp->next->next = NULL;
		}
	}
}
//removes thread from blocked queue to ready queue
void remove_blocked(proc * ready, proc * blocked, int * block_time, int time){
	if(blocked->head_thread != NULL){
		blocked->head_thread->CPU_burst->IO_time = 0;
		remove_CPU(blocked->head_thread, blocked->head_thread->CPU_burst);
		if(ready->head_thread == NULL){
			ready->head_thread = blocked->head_thread;
			blocked->head_thread = blocked->head_thread->next;
			ready->head_thread->next = NULL;			
		}else{
			thread * temp = ready->head_thread;
			while(temp->next != NULL){
				temp = temp->next;
			}
			temp->next = blocked->head_thread;
			blocked->head_thread = blocked->head_thread->next;
			temp->next->next = NULL;
		}
		if(blocked->head_thread == NULL){
			*block_time = 0;
		}else{
			*block_time = blocked->head_thread->CPU_burst->IO_time + *block_time;
		}
	}
}
//moves thread from ready queue to done queue 
void add_done(proc * ready, proc * done){
	if(ready->head_thread != NULL){
		if(done->head_thread == NULL){
			done->head_thread = ready->head_thread;
			ready->head_thread = ready->head_thread->next;
			done->head_thread->next = NULL;
		}else{
			thread * temp = done->head_thread;
			while(temp->next != NULL){
				temp = temp->next;
			}
			temp->next = ready->head_thread;
			ready->head_thread = ready->head_thread->next;
			temp->next->next = NULL;
		}
	}
}
//moves all threads in list struct into new queue
void creat_new(proc * new_thread,sch * list ){
	if(list->head_proc != NULL){
		proc * temp = list->head_proc;
			while(temp != NULL){
				while(temp->head_thread != NULL){
					if(new_thread->head_thread != NULL){
						thread * temp2 = new_thread->head_thread;
						thread * temp3 = NULL;				
						while(temp2 != NULL){
							if(temp2->arrival_time > temp->head_thread->arrival_time){
								thread * temp4 = temp->head_thread;
								temp->head_thread = temp->head_thread->next;
								temp4->next = temp2;
								if(temp3 != NULL){
									temp3->next = temp4;
								}else{
									new_thread->head_thread = temp4;
								}
								break;
							}
							temp3 = temp2;
							temp2 = temp2->next;
						}
						if(temp2 == NULL){
							temp2 = temp->head_thread;
							temp->head_thread = temp->head_thread->next;
							temp2->next = NULL;
							temp3->next = temp2;
						}
					}else{
						new_thread->head_thread = temp->head_thread;
						temp->head_thread = temp->head_thread->next;
						new_thread->head_thread->next = NULL;					
					}
				}
				temp = temp->next;
			}				
	}
}
