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
#include <stdio.h>
#include <stdlib.h> 
#include "common.h"

//parse the input arguments
int check_arg(int argc, char * argv[], int * num,int * eat){
/*check for
* -number of philosophers
* -times to eat
*/
	int i;
	int temp;
	if(argc == 3){
		for(i = 1; i < argc; i++){			
			if(argv[i] != NULL){
				temp = atoi(argv[i]);
				if(i == 1 && temp > 1){
					*num = temp;
				}else if(i == 2 && temp >= 1 && temp <= 1000){
					*eat = temp;
				}
			}
		} 
	}else{
		return 1;
	}
	return 0;	
}
int main(int argc, char * argv[]){
	int num_philoshers= 0;
	int eat_times = 0;
	printf("starting program\n");
	//get arguments
	if(check_arg(argc, argv, &num_philoshers,&eat_times) != 1){
		if(eat_times != 0 && num_philoshers != 0){
			//start program
			error(creat(num_philoshers,eat_times));
		}else{
			printf("ERROR: wrong value for arguments!\n");
		}
	}else{
		printf("ERROR: wrong amount of arguments!\n");
	}
	return 0;
}
