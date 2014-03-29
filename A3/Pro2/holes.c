/*----------------------------------------------
Name: Mohamad Kanafani                       |
ID: 0702067                                  |
Date: 03/28/2014                             |
Class: CIS 3110                              |
Assignment: Assignment 3: memory mangment    |
----------------------------------------------*/
#include <stdio.h>
#include <stdlib.h> 
#include "commonSim.h"
#include "fileReader.h"

int main(int argc, char * argv[]){
	proc head;
	if(argc == 2){
		if(read_file(argv[1], &head) == 0){
			sim_mem(&head);
		}else{
			printf("Error unable to read file %s !\n",argv[1]);
		}
	}else{
		printf("Error incorrect arguments where provided !\n");
	}
	return 0;
}


