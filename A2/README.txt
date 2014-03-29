----------------------------------------------
Name: Mohamad Kanafani                       |
ID: 0702067                                  |
Date: 28/02/2014                             |
Class: CIS 3110                              |
Assignment: Assignment 2: CPU Schuduling     |
----------------------------------------------

********************************************************************************
|     Allgorithm     |
----------------------
    the program first look for the spacial argument like -r, -d, -v, quantum 
number. Then the program parses the file from the arguments and saves them into
queue in order of overhead, processes, threads and bursts and cycles. Next the 
programe will check if r is set or not and depanding on it will issue to start
FCFS or Round Robin. During simulation if v is set the step by step prints
are printed. The simulations start with moving all threads into new queue.
Next will move each thread depanding arrival time to ready queue. Then do CPU
burst or quantum burst depanding on sim. After that check if there is IO burst,
if there is then move thread to blocked until done IO time and work on next thread
other wise check repet until all bursts are done and move on next thread. Only 
excaption is RR where after quantum run the threads are cycled in ready queue.
After the simulation is done the results are printed followed by if d is set the
details of each threads. One important note is in this simulation add thread switch
overhead each time threads are switch from ready to running and from running to 
blocked. Also process switch overhead is add each time process is changed expect
at start since it is assumed we start on first process.


********************************************************************************
|     Assumptions     |
-----------------------
    For the implementation of this program it is assumed that the command line 
arguments will be some what valid as in the minimum the file pointer is provided.
Also the file with data is valid and is structered the way it is promised in the
description. Threads that arrive at the same time, the one that was read first is
given priorty and is put in ready/new queue first.

********************************************************************************
|     How To Run     |
----------------------
    To COMPILE this program the user is required to type 'make all' into the
terminal.
	To RUN the program the user is required to type './simProgram < file_path' 
into the terminal.
	
	There are 4 arugments:
	1. -d - details flags
	2. -v - verbos flags
	3. -r - round robin flag
	4. # - quantum number for RR
	these arguments can be added before the "<" symbole
	**note # has to be after "-r" ex: "-r 10"**

	by defualt the programe will run FCFS unless r is set then RR is run

	**note test files t1.txt t2.txt t3.txt from the moodle is included and 
	can be used as is**
	
	
********************************************************************************
|     Limitations     |
-----------------------
    This program has to no limitation according to the assignment outline. The only 
limitation for this program is the computers memory since it can not allocat
more memory than available.

--------------------------------------------------------------------------------
|     questions   |
-------------------

i.Does your simulator include switch overhead for the first ready state to
running state transition? Explain.

	yes, I assumed that regardless of the process status idle or not 
the processor needs to switch stacks and grab the thread stack when going into  
running which is over head.

ii.Does your simulator include switch overhead if a thread moves from ready
state to running state and the CPU is idle? Explain.

	yes, again I assumed that regardless of the process status idle or not 
the processor needs to switch stacks and grab the thread stack when going into  
running which is over head.

iii.Does your simulator include switch overhead if a thread moves from
running state to blocked state and the ready queue is empty? Explain.
	
	yes, since this requires the processor to switch stacks to remove 
the current running one and put it into blocked queue even if there is no
thread in the ready.

iv.Does your simulation include switch overhead if a thread is interrupted
(due to a time slice) and either the ready queue is empty or the thread has
the highest priority? Explain.

	yes because once the time slice is over the thread has to cycle regardles 
of priorty or status of ready queue status to maintain fairness on CPU utilization,
but if the schudular is smarter it would detect that no need to switch and keep 
going to reduce overhead.
--------------------------------------------------------------------------------
