#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/unistd.h>

int main(int argc, char** argv) {
    int n = atoi(argv[1]);
    int chID;
    int i = 0;
    
    pid_t ch_pid = 1;
    pid_t ppid, pid;
    
    for (i = 0; i < n; i++) {
        if (ch_pid != 0) {
            ch_pid = fork();
        }
        chID = i;
    }
    
    while (1) {
        sleep(1);

        if (ch_pid != 0) {
            //ppid = getppid();
            //pid = getpid();
            //printf("PARENT\t%d\t%d\t%d\n", ch_pid, ppid, pid);
        } else if (ch_pid == 0) {
            ppid = getppid();
            pid = getpid();
            printf("CHILD\t%d\t%d\t%d\n", chID, ppid, pid);
        }

        i++;
    }    

    return EXIT_SUCCESS;
}
