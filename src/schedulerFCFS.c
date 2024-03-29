/**
 * @file schedulerFCFS.c
 * @author your name (you@domain.com)
 * @brief Implementação da politica de escalonamento First-Come, First-Served   
 * @version 0.1
 * @date 2024-03-11
 *  
 * @copyright Copyright (c) 2024
 * 
 */

#include "orchestrator.h"  
#include "schedulerFCFS.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h> 
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h> 


PROCESS *head = NULL;
PROCESS *tail = NULL;

void addToQueue(char *command[], int tempoEstimado) {
    struct Process *newProcess = (struct Process *)malloc(sizeof(struct Process));
    if (newProcess == NULL) {
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; command[i] != NULL; ++i) {
        newProcess->command[i] = strdup(command[i]);
    }
    newProcess->tempoEstimado = tempoEstimado;
    newProcess->next = NULL;

    if (head == NULL) {
        head = newProcess;
        tail = newProcess;
    } else {
        tail->next = newProcess;
        tail = newProcess;
    }
}



void executeQueue() {
    while (head != NULL) {
        struct Process *current = head;
        head = head->next;
        runProgram(current->command, current->tempoEstimado);
        free(current); 
    }
}
