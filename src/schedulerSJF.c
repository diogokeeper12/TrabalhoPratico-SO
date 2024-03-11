/**
 * @file schedulerSJF.c
 * @author your name (you@domain.com)
 * @brief Implementação da politica de escalonamento Shortest Job First  
 * @version 0.1
 * @date 2024-03-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#include "orchestrator.h"  
#include "schedulerSJF.h"


//WARNING -> NAO FUNCIONA

void addToQueueSJF(char *command[], int tempoEstimado) {
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
        if (tempoEstimado < head->tempoEstimado) {
            newProcess->next = head;
            head = newProcess;
        } else {
            struct Process *current = head;
            struct Process *prev = NULL;
            while (current != NULL && tempoEstimado >= current->tempoEstimado) {
                prev = current;
                current = current->next;
            }
            prev->next = newProcess;
            newProcess->next = current;
            if (current == NULL) {
                tail = newProcess;
            }
        }
    }
}



void executeQueueSJF() {
    while (head != NULL) {
        struct Process *current = head;
        head = head->next;
        runProgram(current->command, current->tempoEstimado);
        free(current); 
    }
}

