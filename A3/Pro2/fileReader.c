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

#define BUFF_SIZE 100

//makes copy of proc org
proc * copy(proc * org){
	proc * head = org->next;
	proc  * new_head;
	proc * temp = NULL;
	proc * queue = NULL;
	while(head != NULL){
		temp = malloc(sizeof(proc) * 1);
		temp->id = head->id;
		temp->size = head->size;
		temp->loc = head->loc;
		temp->swap_count = head->swap_count;
		temp->next = NULL;
		if(queue != NULL){
			queue->next = temp;
		}else{
			new_head = temp;
		}
		queue = temp;
		head = head->next;
	}
	return new_head;
}

//read file and insert data into head
int read_file(char * file_name, proc * head){
	FILE * fp = NULL;
	char id = ' ';
	int size = 0;
	int count = 0;
	char string[BUFF_SIZE];
	proc * temp;
	proc * queue = NULL;
	fp = fopen(file_name, "r");
	if(fp!=NULL){
		while(!feof(fp)){	
			if( fgets(string,BUFF_SIZE,fp) != NULL){
				sscanf(string,"%c%d",&id,&size);
				if(id != ' ' && size != 0){
					temp = malloc(sizeof(proc) * 1);
					temp->id = id;
					temp->size = size;
					temp->loc = 0;
					temp->swap_count = 0;
					temp->next = NULL;
					if(queue != NULL){
						queue->next = temp;
					}else{
						head->next = temp;
					}
					queue = temp;
					count++;
				}
				id = ' ';
				size = 0;
				strcpy(string,"");				
			}
		}
		fclose(fp);
	}else{
		return 1;
	}
	return 0;
}
