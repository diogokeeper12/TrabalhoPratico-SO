#ifndef SCHEDULER_SJF_H
#define SCHEDULER_SJF_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h> 
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h> 

extern PROCESS *head;
extern PROCESS *tail;



void addToQueueSJF (char *command[], int tempoEstimado);
void executeQueueSJF();


#endif