#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/unistd.h>

int main() {
    int status;
    int n = 2;
    int m = 50;
    int i = 0;

    pid_t ch_pid, ppid, pid;
    ch_pid = fork();

    while (1) {
        sleep(1);

        if (ch_pid != 0 && i < n) {
            ppid = getppid();
            pid = getpid();
            printf("PARENT\t%d\t%d\t%d\n", ch_pid, pid, ppid);
        } else if (ch_pid == 0 && i < m) {
            ppid = getppid();
            pid = getpid();
            printf("CHILD\t%d\t%d\t%d\n", ch_pid, pid, ppid);
        }

        i++;

        if (i >= n && ch_pid != 0) {
            ch_pid = wait(&status);
            printf("CHILD\t%d\t%d\t%d\n", ch_pid, WIFEXITED(status), WEXITSTATUS(status));
            exit(EXIT_SUCCESS);
        }

        if (n > m) {
            if (i >= n) {
                break;
            }
        } else {
            if (i >= m) {
                break;
            }
        }
    }

    return EXIT_SUCCESS;
}

