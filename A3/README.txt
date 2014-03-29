----------------------------------------------
Name: Mohamad Kanafani                       |
ID: 0702067                                  |
Date: 03/28/2014                             |
Class: CIS 3110                              |
Assignment: Assignment 3: dinning and mem    |
----------------------------------------------

****************************************************************************************
|             Contents              |
--------------------------------
 Compilation/Execution
 Application Overview
 Assumptions
 Known Bugs
 Limitations
 Algorithm
 Conclusion
 
****************************************************************************************
|     Compilation/Execution     |
----------------------------------
COMPILING
**********
To compile both programs type 'make all' into the command line.
or to just compile memory mangment type 'make hole' and to
compile dinning philosophers type 'dine'

Part 1
**********
To run the program for Part 1, type './dinning #ofPhilosophers #timesToEat' in the command line.
	- #ofPhilosophers = an integer greater than 1 and is the number of philosopher.
	- #timesToEat = an integer between 1-1000 and is the number of times each philosopher eats.

Part 2
**********
To run the program for Part 2, type './hole filename' in the command line.
	-	filename = the name of the '<file name>.txt' file.


****************************************************************************************
|      Application Overview      |
----------------------------------
Part 1
**********
	This program simulates the dinning philosophers problem. The problem is there are same number of forks as the
philosophers and are eating in circulier table but to eat the philosopher requires two forks to eat. To eat teh philosopher will take the fork on the right and eat. Next the philosopher goes to think and back to eat. The problem is if the right fork is being used the philosopher needs to wait. To implements this
Mutual Exclusion is used and this is done using the pthreads library.

Part 2
**********
	This program is a Memory Manager Simulation for First Fit, Best Fit, Worst Fit, and Next Fit of memory size of 128. Data provided in a text file. It is first read and put in queues and copied four times. Then the copies are past and ran through the simulation with a output that indicates the memory used, how many holes are in the memory, the number of processes and the average memory usage. After handiling the data using a specific management technique the information is displayed on the terminal.

******************************************************************************************
|            Assumptions           |
---------------------------------
Part 1
**********
	-This program assumes that user has the pthered lib on computer

Part 2
**********
	-This program assumes that user will provide an appropriate input from the command line as mentioned 
under the Compilation/Execution section. It is assumed that the command line argument for the file is a file name and not an input stream for a file.
	-The file must have a process ID (indicated by a letter) and a memory size. These two values are
seperated by one space. EX: 'A 25'.
	-The max memory size is 128
	-It is assumed that the third time the process is removed/swaped from memory the process has 
completed its execution.

****************************************************************************************
|            Known Bugs           |
---------------------------------
Part 1
**********
	No known bugs
Part 2
**********
	No known bugs

****************************************************************************************
|             Limitations            |
---------------------------------
Part 1
**********
	No known limitations.

Part 2
**********
	No known limitations.

****************************************************************************************
|              Algorithm             |
---------------------------------
Part 1
**********
	For this program the first thing it does is parse the command line arguments and checks if they are correct and are in range. If not correct it return an error code that is parsed by error function otherwise it goes to creat. This function creats memory for the philosopher struct that holds id for the forks of right and left and philosopher number and number to eat. It also creats the forks(mutux) as resources next it init everything like mutux and threads. Next the main thread will sleep and the other threads will start the simulation. first they will think for random amount of time and then try to eat for random time. If the forks are not used the philosopher will eat otherwise will wait for them to be free

The outline for this program was obtained from RosettaCode.
	Address: http://rosettacode.org/wiki/Dining_philosophers#C
	Date Accessed: March 18, 2014
	
Information on how to use pthreads was obtained from the following addresses on Mar 18, 2014.
	http://man7.org/linux/man-pages/man7/pthreads.7.html%2Frzahwmutco.htm

Part 2
**********
	The program starts by parseing the command line arguments and attampt to read file inputed as argument. Then it will add the data to queue and call mem_sim functions. This function will call each type of memory mangment in order of best, worst, next and first fit. It will call copy first to pass a copy of orginal queue into the memory mangment functions. The memory mangment function will then go into a loop until all proc in wait are in mem queue and call find to find where to place process in memory and then call add_mem to move process from wait queue to mem queue. The find function will first count the zeros and check if the current whole meets requirments of memory mangment(best or worst) while it counts the holes. If no space found the add_queue is called to remove oldest process from mem and add it back to wait queue. The other memory mangment functions are the same only difference the arguments passed in type and loc for find which will indicate the type it is.

