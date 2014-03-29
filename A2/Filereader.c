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
#include "Filereader.h"
#include "queue.h"

#define BUFF_SIZE 100
int read_File(FILE * fp,sch * list) {
	char string[BUFF_SIZE];
	int temp = 0, temp2 = 0, temp3 = 0;
	int thread_id = 0;
	int proc_id = 0;
	int num_thread = 0;
	int num_CPU = 0;
	int counter = 0;
	int thread_counter = 0;
	int CPU_counter = 0;
	int flag = 0;
	if(fp!=NULL){
		while(!feof(fp)){			
			if( fgets(string,BUFF_SIZE,fp) != NULL){
				if(counter == 0){
					sscanf(string,"%d%d%d",&temp,&temp2,&temp3);
					list->number_proc = temp;
					list->thread_switch = temp2;
					list->proc_switch = temp3;
					//creat procs
				}else if(thread_counter == num_thread && flag == 0){
					sscanf(string,"%d%d",&temp,&temp2);
					num_thread = temp2;
					proc_id = temp;
					thread_counter = 0;
					if(enqueue_list(list,NULL,NULL, creat_proc(temp,temp2),0,0) == 1){
						printf("error: proc\n");
						exit(1);
					}
					//creat threads
				}else if(CPU_counter == num_CPU){
					sscanf(string,"%d%d%d",&temp,&temp2,&temp3);
					num_CPU = temp3;
					thread_id = temp;
					thread_counter++;
					CPU_counter = 0;
					if(thread_counter == num_thread){
						flag = 1;
					}
					if(enqueue_list(list,NULL,creat_thread(temp,temp2,temp3),NULL,proc_id,0) == 1){
						printf("error: thread\n");
						exit(1);
					}
				}else{
					//creat burst
					sscanf(string,"%d%d%d",&temp,&temp2,&temp3);
					CPU_counter++;
					if(flag == 1 && CPU_counter == num_CPU){
						flag = 0;
					}
					if(enqueue_list(list,creat_CPU(temp,temp3,temp2),NULL,NULL,thread_id,proc_id) == 1){
						printf("error: CPU\n");
						exit(1);
					}
				}
				temp = 0;
				temp2 = 0;
				temp3  = 0;
				counter++;
			}
		}
		fclose(fp);
	}else{
		return -1;
	}

	return 0; 
}

