----------------------------------------------
Name: Mohamad Kanafani                       |
ID: 0702067                                  |
Date: 01/31/2014                             |
Class: CIS 3110                              |
Assignment: Assignment 1: Writing a Shell    |
----------------------------------------------

********************************************************************************
|     Allgorithm     |
----------------------
    the program first look for the spacial argument like add, mult, exit, quit
and arg. then the program check if pipe are in the arguments or & to set a flag or 
call the piping function. if no arguments are fun teh program will make child and
check for file operators and then try and run program.



********************************************************************************
|     Assumptions     |
-----------------------
    For the implementation of this program it is assumed that the command line 
arguments will not exceed 10 strings. This is because the 'lex.c' file provided
is limited to an array space of 10 for the arguments.



********************************************************************************
|     How To Run     |
----------------------
    To COMPILE this program the user is required to type 'make all' into the
terminal.
	To RUN the program the user is required to type './shellProgram' into the terminal.

	There are 2 exit commands: 
	
		"exit" 
	  or 
		"quit"
	
	There are 3 user implemented commands:
	1. add - Able to add hexidecimal and decimal integeres
	2. arg - Lists all command line arguments
	3. mul - Able to multiply hexadecimal and decimal numbers
	
	
********************************************************************************
|     Limitations     |
-----------------------
    This program has to limitation according to the assignment outline. The only 
limitation for this program is it can not run more than 3 pipes. When attampting
to run 4 pipes the issue may be that the previews program has not finished which
result wronge output for the third or fourth pipe.



--------------------------------------------------------------------------------
|     bonus    |
-------------------------------------

I was able to run these
   # Redirect both input and output at the same time
    sort < 2.output > bonus1.output
   
    # Multiple pipe chaining (hard: with I/O redirection)
    cat < 2.output | sort | wc > bonus2.output  

	useful function
--------------------------------------------------------------------------------
