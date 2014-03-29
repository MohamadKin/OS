/*----------------------------------------------
Name: Mohamad Kanafani                       |
ID: 0702067                                  |
Date: 28/02/2014                             |
Class: CIS 3110                              |
Assignment: Assignment 2: CPU Schuduling     |
----------------------------------------------*/
#ifndef SIM_H
#define SIM_H

//burst stuct
struct burst
{
	int CPU_Id;
	int IO_time;
	int CPU_time;
	struct burst * next;
};
//thread struct
struct thread
{
	int thread_Id;
	int proc_Id;
	int arrival_time;
	int number_CPU;
	int total_IO;
	int total_CPU;
	int status;
	int complete_time;
	struct burst * CPU_burst;
	struct thread * next;
	
};
//process struct
struct proc
{
	int proc_Id;
	int number_thread;
	int total_IO;
	int total_CPU;
	struct thread * head_thread;
	struct proc * next;
};
//overhead struct
struct sch
{
	int number_proc;
	int thread_switch;
	int proc_switch;
	struct proc * head_proc;
};

typedef struct sch sch;
typedef struct proc proc;
typedef struct thread thread;
typedef struct burst burst;
#endif
