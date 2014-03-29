/*----------------------------------------------
Name: Mohamad Kanafani                       |
ID: 0702067                                  |
Date: 28/02/2014                             |
Class: CIS 3110                              |
Assignment: Assignment 2: CPU Schuduling     |
----------------------------------------------*/
#ifndef FCFS_H
#define FCFS_H
#include "sim.h"

/*function: FCFS
 *description: this simulates FCFS schuduling
*/
void FCFS(sch * list, int v, int d);

/*function: print_result
 *description: this function prints the result of the simulation
*/
void print_result(int time,double turnaround, int CPU );

/*function: detial
 *description: this function prints the details of simulation
*/
void detail(thread * temp);

/*function: verbos
 *description: this function prints the steps of simulation if it is active
*/
void verbos(thread * temp, int time, int id,int block);


#endif
