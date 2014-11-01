#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/unistd.h>

int main(int argc, char** argv) {
    int n = argv[1];
    int i = 0;
    
    pid_t ch_pid, ppid, pid;
    
    ch_pid = fork();
    
    while (1) {
        sleep(1);

        if (ch_pid != 0) {
            ppid = getppid();
            pid = getpid();
            printf("PARENT\t%d\t%d\t%d\n", ch_pid, pid, ppid);
        } else if (ch_pid == 0) {
            ppid = getppid();
            pid = getpid();
            printf("CHILD\t%d\t%d\t%d\n", ch_pid, pid, ppid);
        }

        i++;
    }    

    return EXIT_SUCCESS;
}
