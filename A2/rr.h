/*----------------------------------------------
Name: Mohamad Kanafani                       |
ID: 0702067                                  |
Date: 28/02/2014                             |
Class: CIS 3110                              |
Assignment: Assignment 2: CPU Schuduling     |
----------------------------------------------*/
#ifndef RR_H
#define RR_H
#include "sim.h"

/*function: RR
 *description: this simulates RR schuduling
*/
void RR(sch * list, int v, int d, int r);

/*function: print_result
 *description: this function prints the result of the simulation
*/
void rr_print_result(int time,double turnaround, int CPU, int r );

/*function: detial
 *description: this function prints the details of simulation
*/
void rr_detail(thread * temp);

/*function: verbos
 *description: this function prints the steps of simulation if it is active
*/
void rr_verbos(thread * temp, int time, int id,int block);

/*function: cycle_rr
 *description: this function cycles threads in the ready queue
*/
void cycle_rr(proc * ready);

#endif
