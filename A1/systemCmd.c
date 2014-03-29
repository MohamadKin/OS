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
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include "systemCmd.h"

char ** arg_array(char ** args, int argc, int start){
	char ** arg;
	int i;
	int counter = 0;
	arg = (char **) malloc(sizeof(char *)*(argc-start));
	for(i = start; i < argc; i++) {
		if(args[i] != NULL){
			if(args[i][0] != ' '){
				arg[counter] = (char*) malloc(sizeof(char)* strlen(args[i]));
				strcpy(arg[counter],args[i]);
				counter++;				
			}else if(args[i] == NULL){
				break;
			}
		}
	}
	arg[counter] = NULL;
	return arg;
}
void free_arg(char ** ptr){
	int i;
	for(i = 0; ptr[i] != NULL; i++){
		free(ptr[i]);
	}
	free(ptr);
}
// not used since changeing the signal breaks flex
void termination_handler(){
	printf("\n$ ");
}
int check_file_operators(char ** args, FILE * in, FILE * out){
	int i;
	int ind = 0;
	for(i = 0; args[i] != NULL; i++) {
		if(strcmp(args[i],">") == 0){
			if(strcmp(args[i+1],">") == 0){
				in = change_stream(args[i+2],"a");
				args[i+2][0] = ' ';  
			}else{
				in = change_stream(args[i+1],"w");				
			}
			args[i+1][0] = ' '; 
			ind = 1;
			args[i][0] = ' '; 
		}else if(strcmp(args[i],"<") == 0){
			out = change_stream(args[i+1],"r");
			if(strcmp(args[i+1],"<") == 0){
				args[i+2][0] = ' ';  
			}
			args[i][0] = ' '; 
			args[i+1][0] = ' ';
			ind = 2; 
		}
	}
	return ind;
}
int check_pipe(char ** args, int size,int * old_pipe){
	int i;
	int tmp_pipe[2];
	tmp_pipe[0] = old_pipe[1];
	tmp_pipe[1] = old_pipe[0];
	for(i = 0; args[i] != NULL; i++) {
		if(strcmp(args[i],"|") == 0){
			args[i][0] = ' ';
			do_pipe(arg_array(args,size,i+1),arg_array(args,i+1,0),size-i,i+1, tmp_pipe);
			return -1;
		}
	}
	return 0;
}
int make_child( char ** arg, int par, int size)
{
	int status;
	int ind = 0;
	char ** tmp_arg;
	FILE * in = NULL;
	FILE * out = NULL;
	pid_t child_pid , temp_pid;
	child_pid = fork();
	if( (child_pid) == 0 ){
		ind = check_file_operators(arg,in, out);
		tmp_arg = arg_array(arg, size,0);
		run_cmd(tmp_arg, ind);
		free_arg(tmp_arg);
		if(in != NULL){
			close_file(in);
		}
		if(out != NULL){
			close_file(out);
		}
		exit(0);
	} else if( child_pid < -1){
		printf("ERROR: unable to creat child\n");
	}else{
		if(!par){
			do {
				temp_pid = wait(&status);
				if(temp_pid == -1){ 				
					temp_pid = child_pid;
					printf("ERROR: child did not close properly \n");
					kill(child_pid,SIGTERM);
				}
			} while(temp_pid != child_pid);
		}else{
			/* modifing the signel to handle thtermination of child causes the flex to fail
			 * the precudure is commented out but it will work in the backround
			 * the result is similair to reguler shell
			struct sigaction new_action;
			new_action.sa_handler = termination_handler;
			sigaction (SIGCHLD,&new_action ,NULL );*/
		}
	}
	return 0;
}

int run_cmd(char ** arg, int ind)
{
	int i;
	if (execvp(arg[0], arg) == -1){
		if(!ind){
			printf("ERROR: Unknown command\n");
		}else{
			for(i = 0; arg[i] != NULL; i++){
				printf("%s ", arg[i]);
			}
			
		}
	}
	return 0;
}
FILE * change_stream(char * path,char * type)
{
	static FILE *fp;
	if(strcmp(type,"r") == 0){
		fp = freopen(path, type, stdin);
	}else{
		fp = freopen(path, type, stdout);
	}
	return fp;
}
int close_file(FILE * fp){
	fclose(fp);
	return 0;	
}

void do_pipe(char ** arg_to, char ** arg_from , int size_to, int size_from, int * old_pipe){	
	int my_pipe[2];
	pid_t child2_pid;

	if(pipe(my_pipe) == -1)
	{
		printf("Error: unable to creating pipe\n");
	}

	child2_pid = fork();
	if(child2_pid == -1)
	{
		printf("ERROR: unable to creat child\n");
	}
	else if(child2_pid == 0) // child process
	{
		FILE * in = NULL;
		FILE * out = NULL;
		char ** tmp_arg;
		close(my_pipe[0]); // child doesn't read
		dup2(my_pipe[1], old_pipe[1]); // redirect stdout
		check_file_operators(arg_from,in, out);
		tmp_arg = arg_array(arg_from, size_from,0);						
		run_cmd(tmp_arg, 0);
		free_arg(arg_from);
		free_arg(tmp_arg);
		if(in != NULL){
			close_file(in);
		}
		if(out != NULL){
			close_file(out);
		}					
		exit(0);				
	}
	else
	{	
		int ind = 0;
		char ** tmp_arg;
		FILE * in = NULL;
		FILE * out = NULL;
		close(my_pipe[1]);
		dup2(my_pipe[0], old_pipe[0]);
		ind = check_pipe(arg_to, size_to,my_pipe);	
		if(ind != -1){		
			check_file_operators(arg_to,in, out);
			tmp_arg = arg_array(arg_to, size_to,0);						
			run_cmd(tmp_arg, 0);
			free_arg(arg_to);
			free_arg(tmp_arg);
			if(in != NULL){
				close_file(in);
			}
			if(out != NULL){
				close_file(out);
			}
					
		}else{
			free_arg(arg_to);
		}			
	}
	exit(0);

}
int creat_pipe(char ** arg_to, char ** arg_from , int size_to, int size_from, int * old_pipe)
{		
	
	int status;	
	pid_t child_pid,temp_pid;
	
	child_pid = fork();
	if(child_pid == -1)
	{
		printf("ERROR: unable to creat child\n");
	}
	else if(child_pid == 0) // child process
	{
		
		do_pipe(arg_to,arg_from ,size_to,size_from,old_pipe);
	}
	else
	{		
		do {
			temp_pid = wait(&status);
			if(temp_pid == -1){ 				
				temp_pid = child_pid;
				printf("ERROR: child did not close properly \n");
				kill(child_pid,SIGTERM);
			}
		} while(temp_pid != child_pid);						
	}
	
	return 0;
}
int check_if_num(char ** args){
	int i,j,flag;
	int size = 0;
	for(i = 1; args[i] != NULL; i++){
		size = strlen(args[i]);
		flag = 0;
		for(j = 0; j < size ; j++){
			if(isdigit(args[i][j]) == 0){
				if(args[i][j] == 'x' || args[i][j] == 'X' ){
					flag = 1;
				}else if(isxdigit(args[i][j]) == 0){		
					return 0;
				}else if(flag == 0){
					return 0;
				}
			}
		}
	}
	return 1;
}
int add(char ** args){
	double sum = 0;
	long int hex = 0;
	int i;
	if(check_if_num(args)){
		for(i = 1; args[i] != NULL; i++) {		
			if(args[i + 1] != NULL){		
				printf("%s + ",args[i]);
			}else{
				printf("%s ",args[i]);
			}
			if(strstr(args[i],"0x") != NULL || strstr(args[i],"0X") != NULL){
				hex += strtol(args[i],NULL,0); 
			}else{
				sum += atof(args[i]);
			}
		}
		sum += hex;
		printf("= %lf\n",sum);
	}else{
		printf("ERROR: invalid number(s)\n");
	}
	return 0;
}
int arg(char ** args, int size){
	int i;
	int counter = size - 1;
	printf("argc = %d,args = %s ", counter, args[1]);
	for(i = 2; args[i] != NULL; i++){
		printf(",%s ", args[i]);
	}
	printf("\n");
	return 0;
}
int mult(char ** args){
	double mult = 1;
	long int hex = 1;
	int i;
	if(check_if_num(args)){
		for(i = 1; args[i] != NULL; i++) {		
			if(args[i + 1] != NULL){		
				printf("%s * ",args[i]);
			}else{
				printf("%s ",args[i]);
			}
			if(strstr(args[i],"0x") != NULL || strstr(args[i],"0X") != NULL){
				hex *= strtol(args[i],NULL,0); 
			}else{
				mult *= atof(args[i]);
			}
		}
		mult *= hex;
		printf("= %lf\n",mult);
	}else{
		printf("ERROR: invalid number(s)\n");
	}
	return 0;
}

