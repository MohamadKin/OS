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

#include "Filereader.h"
#include "sim.h"
#include "queue.h"
#include "fcfs.h"
#include "rr.h"

//parse the input arguments
int check_arg(int argc, char * argv[], int * d,int * v, int * r){
/*check for
* -d
* -v
* -r #*/

	int i;
	if(argc > 1){
		for(i = 0; i < argc; i++){
			if(argv[i] != NULL){
				if(!strcmp(argv[i],"-d")){
					*d = 1;
				}else if(!strcmp(argv[i],"-v")){
					*v = 1;
				}else if(!strcmp(argv[i],"-r")){
					if(argv[++i] != NULL){
						*r = atoi(argv[i]);
						if(*r <= 0){
							return -1;
						}
					}
				}
			}
		} 
	}
	return 0;	
}
int main(int argc,char *argv[]){
	int d = 0;
	int v = 0;
	int r = 0;
	FILE * input = stdin;
	sch list;
	list.head_proc = NULL;
	printf("starting program\n");
	if(check_arg(argc, argv, &d,&v, &r) != -1){
		if(read_File(input,&list) != -1){
			if(r == 0){
				FCFS(&list,v,d);
			}else{
				RR(&list,v,d,r);
			}	
			destroy_list(&list);
		}else{
			printf("ERROR: no file provided!\n");	
		}
	}else{
		printf("ERROR: wrong quantum number!\n");
	}
	return 0;
}
