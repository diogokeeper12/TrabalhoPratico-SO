#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h> 
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h> 
#include "orchestrator.h"

#define SIZE 1024

PROCESS *head = NULL;
PROCESS *tail = NULL;

void runProgram(char *command[], int tempoEstimado) {
    char *buffer = malloc(sizeof(char) * SIZE);  

    struct timeval start, end;                   
    gettimeofday(&start, NULL);                  

    pid_t pid = fork();                          

    if (pid < 0) {                               
        perror("Não foi possível criar um processo filho!");    
    } else if (pid == 0) { 
        execvp(command[0], command);
        write(2, "Error: Exec failed\n", sizeof("Error: Exec failed\n"));
        _exit(1);          
    } else {
        int status;        
        wait(&status);
        if (WIFEXITED(status) == 1) {
            gettimeofday(&end, NULL); 

            double elapsedTime = (end.tv_sec - start.tv_sec) * 1000.0; 
            elapsedTime += (end.tv_usec - start.tv_usec) / 1000.0;      

            int nbytes = sprintf(buffer, "Pid: %d\nProgram: %s\nTempo estimado: %d milissegundos\nTime Elapsed: %.2f milliseconds\n", getpid(), command[0], tempoEstimado, elapsedTime);
            write(1, buffer, nbytes);            
        }
    }
    free(buffer);                                
}

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
        free(current); // Liberar memória alocada para o nó atual
    }
}


int main(int argc, char* argv[]){
    char *buffer = malloc(sizeof(char) * SIZE);     
    if(argc == 1){
        int nbytes = sprintf(buffer,"Não foi encontrado nenhum comando válido!\n");
        write(1,buffer,nbytes);
        return -1;
    }
    
    if(strcmp(argv[1],"execute")==0){
        if(strcmp(argv[3],"-u")==0){
            int time = atoi(argv[2]);
            addToQueue(&argv[4], time);
        }
    }

    executeQueue();
    free(buffer);
    return 0;
}


