/*----------------------------------------------
Name: Mohamad Kanafani                       |
ID: 0702067                                  |
Date: 31/01/2013                             |
Class: CIS 3110                              |
Assignment: Assignment 1: Writing a Shell    |
----------------------------------------------*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "systemCmd.h"

extern char **getln();

int main() {
	int i;
	int argc = 0;
	int old_pipe[] = {0,1};
	char **args; 
	while(1) {
		printf("$ ");
		args = getln(&argc);
		if(argc > 0){
			if(args != NULL && strcmp(args[0],"") && args[0] != NULL ){
				for(i = 0; i < strlen(args[0]); i++){
				  args[0][i] = tolower(args[0][i]);
				}
				if(strcmp(args[0],"exit") == 0 || strcmp(args[0],"quit") == 0 ){
					printf("exiting program\n");
					exit(0);
				}else if(strcmp(args[0],"arg") == 0){
					arg(args,argc);
				}else if(strcmp(args[0],"add") == 0){
					add(args);
				}else if(strcmp(args[0],"mult") == 0){
					mult(args);
				}else{
					for(i = 0; args[i] != NULL; i++) {
						if(strcmp(args[i],"|") == 0){
							args[i][0]=' ';
							creat_pipe(arg_array(args,argc,i+1),arg_array(args,i+1,0),argc-i,i+1, old_pipe);
							i = 0;
							break;
						}else if(strcmp(args[i],"&") == 0){
							args[i][0]=' ';
							i = -1;
							break; 
						}
					}
					if(i == -1){
						make_child(args,1,argc);
					}else if(i != 0){
						make_child(args,0, argc);
					}				
				}
			}
		}
	}
	return 0;
}

