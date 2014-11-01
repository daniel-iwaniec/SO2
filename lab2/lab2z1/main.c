#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/unistd.h>

int main() {
    int n = 12;
    int m = 5;
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
            exit(EXIT_SUCCESS);
        }

        if (i >= n) {
            break;
        }
    }

    return EXIT_SUCCESS;
}
