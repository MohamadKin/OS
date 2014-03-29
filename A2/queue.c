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

thread * creat_thread(int id, int time, int CPU){
	thread * temp;
	temp = malloc(sizeof(thread));
	temp->thread_Id = id;
	temp->arrival_time = time;
	temp->number_CPU = CPU;
	temp->total_IO = 0;
	temp->total_CPU = 0;
	temp->status = 0;
	temp->CPU_burst = NULL;
	temp->next = NULL;
	return temp;
}

proc * creat_proc(int id, int number_thread){
	proc * temp;
	temp = malloc(sizeof(proc));
	temp->proc_Id = id;
	temp->number_thread = number_thread;
	temp->total_IO = 0;
	temp->total_CPU = 0;
	temp->head_thread = NULL;
	temp->next = NULL;
	return temp;

}
burst * creat_CPU(int id, int IO_time, int CPU_time){
	burst * temp;
	temp = malloc(sizeof(burst));
	temp->CPU_Id = id;
	temp->IO_time = IO_time;
	temp->CPU_time = CPU_time;
	temp->next = NULL;
	return temp;

}

//add to the overhead list struct the new item
int enqueue_list(sch * list, burst * tm, thread * thrd , proc * prc, int id, int id2){
	//add burst to list
	if(tm != NULL){		
		if(list->head_proc != NULL){
			proc * temp3 = list->head_proc;
			while(temp3 != NULL){
				if(temp3->proc_Id == id2){
					if(temp3->head_thread != NULL){
						thread * temp = temp3->head_thread;
						while(temp != NULL){
							if(temp->thread_Id == id){
								burst * temp2 = temp->CPU_burst;
								if(temp2 != NULL){
									while(temp2->next != NULL){		
										temp2 = temp2->next;
									}
									temp2->next = tm;
								}else{
									temp->CPU_burst = tm;
								}
								temp->total_IO += tm->IO_time;
								temp->total_CPU += tm->CPU_time;
								temp3->total_IO += tm->IO_time;
								temp3->total_CPU += tm->CPU_time;
								return 0;
							}
							temp = temp->next;
						}				
					}
					
				}
				temp3 = temp3->next;
			}
		}
		return 1;
	//add threads to list
	}else if(thrd != NULL){
		thrd->proc_Id = id;		
		if(list->head_proc != NULL){
			proc * temp = list->head_proc;
				while(temp != NULL){
					if(temp->proc_Id == id){
						if(temp->head_thread != NULL){
							thread * temp2 = temp->head_thread;
							thread * temp3 = NULL;
							while(temp2->next != NULL){
								if(temp2->arrival_time > thrd->arrival_time){
									thrd->next = temp2;
									if(temp3 != NULL)
										temp3->next = thrd;
									else
										temp->head_thread = thrd;	
									return 0;
								}
								temp3 = temp2;
								temp2 = temp2->next;
							}
							temp2->next = thrd;
							return 0;
						}else{
							temp->head_thread = thrd;
							return 0;
						}
					}
					temp = temp->next;
				}				
		}
		return 1;
	//add process to list
	}else if(prc != NULL){
		if(list->head_proc != NULL){
			proc * temp = list->head_proc;
			while(temp->next != NULL){				
				temp = temp->next;
			}
			temp->next = prc;
			return 0;
		}else{
			list->head_proc = prc;
			return 0;
		}
	}
	return 1;
}
void remove_proc(sch * head, proc * current){
	if(current != NULL){
		head->head_proc = current->next;
		free(current);
	}else{
		head->head_proc = NULL;
	}
}
void remove_thread(proc * head, thread * current){
	if(current != NULL){
		head->head_thread = current->next;
		free(current);
	}else{
		head->head_thread = NULL;
	}
}
void remove_CPU(thread * head, burst * current){
	if(current != NULL){
		head->CPU_burst = current->next;
		free(current);
		current = NULL;
	}else{
		head->CPU_burst = NULL;
	}
}
//clean up the list free memory
void destroy_list(sch * list){
	if(list->head_proc != NULL){
		proc * temp = list->head_proc;
		while(temp != NULL){
			if(temp->head_thread != NULL){
				thread * temp2 = temp->head_thread;
				while(temp2 != NULL){
					if(temp2->CPU_burst != NULL){
						burst * temp3 = temp2->CPU_burst;
						while(temp3 != NULL){
							
							temp3 = temp3->next;
							remove_CPU(temp2, temp3);
							temp3 = temp2->CPU_burst;
						}
					}
					remove_thread(temp, temp2);
					temp2 = temp->head_thread;
				}
			}
			remove_proc(list, temp);
			temp = list->head_proc;
		}
	}
}

