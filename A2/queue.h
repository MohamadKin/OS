/*----------------------------------------------
Name: Mohamad Kanafani                       |
ID: 0702067                                  |
Date: 28/02/2014                             |
Class: CIS 3110                              |
Assignment: Assignment 2: CPU Schuduling     |
----------------------------------------------*/
#ifndef QUEUE_H
#define QUEUE_H
#include "sim.h"

/*function: creat_thread
 *description: this function creats thread and init it, returns thread
*/
thread * creat_thread(int id, int time, int CPU);

/*function: creat_proc
 *description: this function creats proc and init it, returns proc
*/
proc * creat_proc(int id, int number_thread);

/*function: creat_CPU
 *description: this function creats CPU and init it, returns cpu
*/
burst * creat_CPU(int id, int IO_time, int CPU_time);

/*function: enqueue_list
 *id : used for proc or thread id when adding cpu or thread
 *id2: used for proc id when adding cpu only
 *description: this function adds thread, proc , cpu to the master list with priority
 *returns 1 on fail and 0 successful
*/
int enqueue_list(sch * list, burst * tm, thread * thrd , proc * prc, int id, int id2);

/*function: remove_proc
 *description: this function frees the first process and move head pointer to next process
*/
void remove_proc(sch * head, proc * current);

/*function: remove_thread
 *description: this function frees the first first thread and move head pointer to next thread
*/
void remove_thread(proc * head, thread * current);

/*function: remove_CPU
 *description: this function frees the first first burst and move head pointer to next burst
*/
void remove_CPU(thread * head, burst * current);

/*function: destroy_list
 *description: this function frees the list elements bursts,threads,processes
*/
void destroy_list(sch * list);
#endif
