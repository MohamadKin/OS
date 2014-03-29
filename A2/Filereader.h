/*----------------------------------------------
Name: Mohamad Kanafani                       |
ID: 0702067                                  |
Date: 28/02/2014                             |
Class: CIS 3110                              |
Assignment: Assignment 2: CPU Schuduling     |
----------------------------------------------*/
#ifndef FILEREADER_H
#define FILEREADER_H
#include "sim.h"

/*function: read_File
 *FILE : file pointer
 *list: header struct used in simulation
 *description: this function opens test file to read and parses it into proper
 *structs
*/
int read_File(FILE * fp, sch * list);

#endif
