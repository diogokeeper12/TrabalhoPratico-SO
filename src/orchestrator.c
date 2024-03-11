#include "orchestrator.h"
#include "schedulerFCFS.h"


#define SIZE 1024

/*
PROCESS *head = NULL;
PROCESS *tail = NULL;
*/

//TODO: FIFO PARA LER DO CLIENTE

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

int main(int argc, char* argv[]){
    char *buffer = malloc(sizeof(char) * SIZE);     
    if(argc == 1){
        int nbytes = sprintf(buffer,"Não foi encontrado nenhum comando válido!\n");
        write(1,buffer,nbytes);
        return -1;
    }

    //EXECUTA O SERVIDOR COM O FCFS...
    if(strcmp(argv[1],"FCFS")==0){
        if(strcmp(argv[2],"execute")==0){
        if(strcmp(argv[4],"-u")==0){
            int time = atoi(argv[3]);
            addToQueue(&argv[5], time);
        }
       /* else if(strcmp(argv[3],"-p")==0){
        }*/
    }
    executeQueue();
    free(buffer);
    return 0;
    }

}


