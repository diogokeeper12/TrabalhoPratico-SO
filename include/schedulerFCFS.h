#ifndef SCHEDULER_FCFS_H
#define SCHEDULER_FCFS_H

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


void addToQueueFCFS(char *command[], int tempoEstimado);
void executeQueueFCFS();

#endif