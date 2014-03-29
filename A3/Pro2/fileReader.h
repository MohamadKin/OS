/*----------------------------------------------
Name: Mohamad Kanafani                       |
ID: 0702067                                  |
Date: 03/28/2014                             |
Class: CIS 3110                              |
Assignment: Assignment 3: memory mangment    |
----------------------------------------------*/
#ifndef FILEREADER_H
#define FILEREADER_H

/*function: copy
 *org : queue of processes to be loaded in memory
 *description : this function makes copy of org
 *return : copy of org(proc)
*/
proc * copy(proc * org);

/*function: read_file
 *file_name : file going to be read 
 *head : pointer to queue to add the read proc into
 *description: this function reads file and insertedd the data
 *into proc struct
*/
int read_file(char * file_name, proc * head);

#endif
