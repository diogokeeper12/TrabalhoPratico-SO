/**
 * @file orchestrator.h
 * @author your name (you@domain.com)
 * @brief Contem informações de estruturas de dados, como "PROCESS" e os protótipos das funções utilizadas no orchestrator.c 
 * @version 0.1
 * @date 2024-03-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef ORCHESTRATOR_H
#define ORCHESTRATOR_H

#define SIZE 1024

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h> 
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h> 




/**
 * @brief Estrutura de um processo TODO: ADICIONAR INFORMAÇÕES DO PID (?)
 * 
 */
typedef struct Process{
    char *command[SIZE];
    int tempoEstimado;
    struct Process *next;
}PROCESS;


/**
//Assinaturas de funções
void addToQueue(char *command[], int tempoEstimado);
void executeQueue();

*/
void runProgram(char *command[], int tempoEstimado);



#endif



