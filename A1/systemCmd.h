/*----------------------------------------------
Name: Mohamad Kanafani                       |
ID: 0702067                                  |
Date: 31/01/2013                             |
Class: CIS 3110                              |
Assignment: Assignment 1: Writing a Shell    |
----------------------------------------------*/
#ifndef SYSTEMCMD_H
#define SYSTEMCMD_H

/*function: make_child
 *arg : the 2d array of command line arguments
 *par: flag that indicates to run child in paralle
 *size: size of arg
 *description: this function makes a child checks for
 *file operators and then run the arguments in arg
*/
	int make_child( char ** arg, int par, int size);

/*function: run_cmd
 *arg : the 2d array of command line arguments
 *ind: flag that indicates file stream is changed
 *description: this function run the arguments in arg
*/
	int run_cmd(char ** arg, int ind);

/*function: change_stream
 *path : file location
 *type: flag that indicates type of stream
 *description: this function changes the streams to
 *files
*/
	FILE * change_stream(char * path,char * type);

/*function: close_file
 *fp : file pointer
 *description: this function closes the stream of a file
*/
	int close_file(FILE * fp);

/*function: creat_pipe
 *arg_to : 2d array command line argument for child
 *arg_from: 2d array command line argument for  grand child
 *size_to: size of arg_to 
 *size_from: size of arg_from 
 *old_pipe: pointer to current stream/pipes
 *description: this function creats a child and waits for it to pipe and output
*/
	int creat_pipe(char ** arg_to, char ** arg_from , int size_to, int size_from, int * old_pipe);

/*function: add
 *args : 2d array command line argument 
 *description: this function adds hex and decimal integer numbers
*/
	int add(char ** args);

/*function: arg
 *args : 2d array command line argument 
 *size: size of arg
 *description: this function counts and prints arg
*/
	int arg(char ** args, int size);

/*function: mult
 *args : 2d array command line argument 
 *description: this function adds hex and decimal integer numbers
*/
	int mult(char ** args);

/*function: check_file_operators
 *args : the 2d array of command line arguments
 *in: file pointer to save the opened file stream(input) in to close later
 *out: file pointer to save the opened file stream(output) in to close later
 *description: this function checks for "> , >> , < , <<" and open a stream
 *depanding on sign
*/
	int check_file_operators(char ** args, FILE * in, FILE * out);

/*function: check_pipe
 *args : the 2d array of command line arguments
 *size: size of args
 *oldpipe: current streams/pipes
 *description: this function checks for "|" and reverse the pipe and call do_pipe
 *when "|" is found to run the next pipe
*/
	int check_pipe(char ** args, int size,int * old_pipe);

/*function: free_arg
 *ptr : 2d array command line argument 
 *description: this function frees the dynamic array created in arg_array
*/
	void free_arg(char ** ptr);

/*function: arg_array
 *args : the 2d array of command line arguments
 *argc: size of args to be copyied
 *start: starting point of where to copy
 *description: this function creats a 2d array of char of the same size and contant 
 *of args depanding on the start and argc
*/
	char ** arg_array(char ** args, int argc, int start);

/*function: do_pipe
 *arg_to : 2d array command line argument for child
 *arg_from: 2d array command line argument for  grand child
 *size_to: size of arg_to 
 *size_from: size of arg_from 
 *old_pipe: pointer to current stream/pipes
 *description: this function creats a child and creats pipe between perant and child
 *then runs the two arguments in the arg arrays
*/
	void do_pipe(char ** arg_to, char ** arg_from , int size_to, int size_from, int * old_pipe);

/*function: check_if_num
 *args : 2d array command line argument 
 *description: this function checks if array is number of
 *type decimal of hex(0xa)
 *returns: 0 if fail and 1 if pass
*/
	int check_if_num(char ** args);

#endif
