/*----------------------------------------------
Name: Mohamad Kanafani                       |
ID: 0702067                                  |
Date: 28/02/2014                             |
Class: CIS 3110                              |
Assignment: Assignment 2: CPU Schuduling     |
----------------------------------------------*/
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#include "sim.h"
#include "queue.h"
#include "rr.h"
#include "common_sim.h"

void RR(sch * list, int v, int d, int r){
	proc ready;
	proc blocked;
	proc done;
	proc new_thread;
	int current_proc = 0;
	int block_time = 0;
	int block_flag = -1;
	long int time = 0;
	long int CPU_time = 0;
	int next_arrival = 0;
	double avg_turnround = 0.0;
	int counter = 0;
	int thread_switch = list->thread_switch;
	int process_switch = list->proc_switch;
	int q_num = r;
	ready.head_thread = NULL;
	done.head_thread = NULL;
	blocked.head_thread = NULL;
	new_thread.head_thread = NULL;	
	creat_new(&new_thread,list);
	current_proc = new_thread.head_thread->proc_Id;
	while(new_thread.head_thread != NULL){
		//get thread				
		if(v == 1){
			rr_verbos(new_thread.head_thread,next_arrival,new_thread.head_thread->proc_Id,-1);
		}
		add_ready(&new_thread, &ready);		
		counter++;
		if(new_thread.head_thread != NULL){
			next_arrival = new_thread.head_thread->arrival_time;
		}else{
			next_arrival = -1;
		}
		while(ready.head_thread != NULL ){
			// ready -> running				
			time += thread_switch;
			CPU_time += thread_switch;
			if(v == 1){
				rr_verbos(ready.head_thread,time,ready.head_thread->proc_Id,block_flag);
			}
			//check if blocked threads are ready
			if(block_time <= time && block_time != 0){
				//check if thread is empty
				if(blocked.head_thread->CPU_burst->next == NULL){							
					blocked.head_thread->complete_time = block_time;
					blocked.head_thread->CPU_burst->IO_time = 0;
					avg_turnround += (block_time - ready.head_thread->arrival_time);
					add_done(&blocked,&done);
					if(v == 1){
						rr_verbos(blocked.head_thread,block_time,blocked.head_thread->proc_Id,0);
					}
				}else{
					if(v == 1){
						rr_verbos(blocked.head_thread,block_time,blocked.head_thread->proc_Id,-1);
					}							
					remove_blocked(&ready,&blocked,&block_time,time);					
				}
			}
			while(ready.head_thread != NULL && ready.head_thread->CPU_burst != NULL && block_flag != 1){
				if(current_proc != ready.head_thread->proc_Id){
					time += process_switch;
					CPU_time += process_switch;
					current_proc = ready.head_thread->proc_Id;
				}
				//do the CPU burst up to r time
				if(q_num > ready.head_thread->CPU_burst->CPU_time){
					//if r is > burst only add that amount of time
					time += ready.head_thread->CPU_burst->CPU_time;
					CPU_time += ready.head_thread->CPU_burst->CPU_time;
					q_num -= ready.head_thread->CPU_burst->CPU_time;
					ready.head_thread->CPU_burst->CPU_time = 0;
					
				}else{
					time += q_num;
					CPU_time += q_num;
					ready.head_thread->CPU_burst->CPU_time -= q_num;
					q_num = r;
				}
				//check if next thread is ready
				while(next_arrival <= time && next_arrival != -1){			
					if(v == 1){
						rr_verbos(new_thread.head_thread,next_arrival,new_thread.head_thread->proc_Id,-1);
					}
					add_ready(&new_thread, &ready);
					counter++;
					//check if threads done
					if(new_thread.head_thread != NULL){
						next_arrival = new_thread.head_thread->arrival_time;
					}else{
						next_arrival = -1;
					}
				}
				if(ready.head_thread->CPU_burst->CPU_time <= 0){					
					//check IO burst if found block thread
					if(ready.head_thread->CPU_burst->IO_time != 0){						
						time += thread_switch;
						CPU_time += thread_switch;
						block_flag = 1;
						if(v == 1){
							rr_verbos(ready.head_thread,time,ready.head_thread->proc_Id,1);
						}
						add_blocked(&ready,&blocked,&block_time,time);
						if(ready.head_thread != NULL){
							current_proc = ready.head_thread->proc_Id;
						}		
					}else{
						//if no IO mean burst is done remove it
						remove_CPU(ready.head_thread, ready.head_thread->CPU_burst);
					}
				}else{
					//cycle ready queue for each r time
					if(v == 1){
						rr_verbos(ready.head_thread,time,ready.head_thread->proc_Id,2);
					}
					time += thread_switch;
					CPU_time += thread_switch;
					cycle_rr(&ready);
					if(v == 1){
						rr_verbos(ready.head_thread,time,ready.head_thread->proc_Id,-1);
					}
					current_proc = ready.head_thread->proc_Id;
				}
			}
			//check if ready is empty and new is not
			if(blocked.head_thread  != NULL && ready.head_thread != NULL){
				//check if blocked or next thread is first
				if(block_time > next_arrival && next_arrival != -1){
					time = next_arrival;
				}else{
					time = block_time;								
					if(v == 1){
						rr_verbos(blocked.head_thread,time,blocked.head_thread->proc_Id,-1);
					}
					remove_blocked(&ready,&blocked,&block_time, time);					
				}
			}
			//reset block flag and check if thread is done
			block_flag = -1;
			if(ready.head_thread != NULL && ready.head_thread->CPU_burst == NULL){
				ready.head_thread->complete_time = time;
				avg_turnround += (time - ready.head_thread->arrival_time);
				if(v == 1){
					rr_verbos(ready.head_thread,time,ready.head_thread->proc_Id,0);
				}
				add_done(&ready,&done);
				if(ready.head_thread != NULL){
					current_proc = ready.head_thread->proc_Id;
				}				
			}
		}
	}
	//CPu utilization and done print stuff
	CPU_time = ((double)CPU_time)/((double)time) * 100;
	rr_print_result(time,(avg_turnround/counter),CPU_time,r);
	if(d == 1){
		rr_detail(done.head_thread);
	}
	list->head_proc->head_thread = done.head_thread;
	done.head_thread = NULL;	
}
void rr_print_result(int time,double turnaround, int CPU , int r){
	printf("\nRound Robin (quantum = %d time units):\n\n",r);
	printf("Total Time required is %d time units\n",time);
	printf("Average Turnaround Time is %.2f time units\n",turnaround);
	printf("CPU Utilization is %d%c\n",CPU,'%');
}
void rr_detail(thread * temp){
	while(temp != NULL){
		printf("\n\nThread %d of Process %d:\n\n",temp->thread_Id,temp->proc_Id);
		printf("arrival time: %d\n",temp->arrival_time);
		printf("service time: %d units\n",temp->total_CPU);
		printf("I/O time: %d units\n",temp->total_IO);
		printf("turnaround time: %d units\n",(temp->complete_time - temp->arrival_time));
		printf("finish time: %d units\n",temp->complete_time);
		temp = temp->next;
	}
}
void rr_verbos(thread * temp, int time, int Id,int block){
	if(block == 0){
		temp->status = 4;
	}else if(block == 2){
		temp->status = 5;
	}
	switch(temp->status){
		case 0: printf("At time %d: Thread {%d} of Process {%d} moves from {%s} to {%s}\n",time,temp->thread_Id,Id,"new","ready");
			temp->status = 1;
			break;
		case 1: printf("At time %d: Thread {%d} of Process {%d} moves from {%s} to {%s}\n",time,temp->thread_Id,Id,"ready","running");
			if(block == 1){
				temp->status = 2;
			} 
			break;
		case 2: printf("At time %d: Thread {%d} of Process {%d} moves from {%s} to {%s}\n",time,temp->thread_Id,Id,"running","blocked");
			temp->status = 3;
			break;
		case 3: printf("At time %d: Thread {%d} of Process {%d} moves from {%s} to {%s}\n",time,temp->thread_Id,Id,"blocked","ready");
			temp->status = 2;
			break;
		case 4: printf("At time %d: Thread {%d} of Process {%d} moves from {%s} to {%s}\n",time,temp->thread_Id,Id,"running","terminated");
			temp->status = 6;
			break;
		case 5: printf("At time %d: Thread {%d} of Process {%d} moves from {%s} to {%s}\n",time,temp->thread_Id,Id,"running","ready");
			temp->status = 1;
			break;
	}
}
void cycle_rr(proc * ready){
	if(ready->head_thread->next != NULL){
		thread * temp = ready->head_thread;
		thread * temp2;
		ready->head_thread = ready->head_thread->next;
		temp2 = ready->head_thread;
		while(temp2->next != NULL){
			temp2 = temp2->next;
		}
		temp2->next = temp;
		temp->next = NULL;
	}
}
