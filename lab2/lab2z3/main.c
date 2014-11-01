#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/unistd.h>

int main(int argc, char** argv) {
    int n = atoi(argv[1]);
    volatile int i = 0;
    
    int childID = 0;
    int piNow = 0;
    int piReq = 0;
    
    pid_t ch_pid = 1;
    pid_t ppid, pid;
    
    for (i = 0; i < n; i++) {
        if (ch_pid != 0) {
            piReq = atoi(argv[i+2]);
            ch_pid = fork();
        } else {
            childID = i;
            break;
        }
    }
    
    while (1) {
        sleep(1);

        if (ch_pid == 0) {
            ppid = getppid();
            pid = getpid();
            printf("C[%d, %d, %d]\tPPID: %d\tPID: %d\n", childID, piReq, piNow, ppid, pid);
        }
        
        if (piNow >= piReq && ch_pid == 0) {
            exit(EXIT_SUCCESS);
        }
        
        piNow++;
    }    

    return EXIT_SUCCESS;
}
