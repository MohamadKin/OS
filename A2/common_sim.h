/*----------------------------------------------
Name: Mohamad Kanafani                       |
ID: 0702067                                  |
Date: 28/02/2014                             |
Class: CIS 3110                              |
Assignment: Assignment 2: CPU Schuduling     |
----------------------------------------------*/
#ifndef COMMONSIM_H
#define COMMONSIM_H
#include "sim.h"

/*function: add_ready
 *description: this function removes the thread from new to ready queue
*/
void add_ready(proc * new_thread, proc * ready);

/*function: add_ready
 *description: this function removes the thread from ready to blocked queue
*/
void add_blocked(proc * ready, proc * blocked,int * block_time, int time);

/*function: remove_ready
 *description: this function removes the thread from blocked to ready queue
*/
void remove_blocked(proc * ready, proc * blocked, int * block_time, int time);

/*function: add_done
 *description: this function removes the thread from ready to done queue
*/
void add_done(proc * ready, proc * done);

/*function: creat_new
 *description: this function removes the thread from parsed list to new queue
*/
void creat_new(proc * new_thread,sch * list );

#endif
