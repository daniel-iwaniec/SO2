#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/unistd.h>

int main() {
    int status;
    int n = 5;
    int m = 50;
    int i = 0;

    pid_t ch_pid, ppid, pid;
    ch_pid = fork();
    ppid = getppid();
    pid = getpid();

    while (1) {
        sleep(1);

        if (ch_pid != 0 && i < n) {
            printf("PARENT\t%d\t%d\t%d\n", ch_pid, pid, ppid);
        } else if (ch_pid == 0 && i < m) {
            printf("CHILD\t%d\t%d\t%d\n", ch_pid, pid, ppid);
        }

        i++;

        if (i >= n && ch_pid != 0) {
            ch_pid = wait(&status);
            printf("ZAKONCZONO PROCESS CHILD %d ZE STATUSEM %d\n", ch_pid, status);
            if (WIFEXITED(status) == 0) {
                printf("PROCES ZAKONCZYL SIE NIEPOPRAWNIE\n");
            } else {
                printf("PROCES ZAKONCZYL SIE POPRAWNIE ze statusem %d\n", WEXITSTATUS(status));
            }
            exit(EXIT_SUCCESS);
        }

        if (i >= m) {
            break;
        }
    }

    return EXIT_SUCCESS;
}
