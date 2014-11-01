#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/unistd.h>

void recursiveFork(int n, int i, char** argv, int piReq, int childID, pid_t* ch_pid) {
    if (n > 0) {
        piReq = atoi(argv[i + 2]);
        ch_pid = fork();
        if (ch_pid == 0) {
            childID = i;
        }
    } else {
        return;
    }

    i++;
    n--;
    recursiveFork(n, i, argv, &piReq, &childID, &ch_pid);
}

int main(int argc, char** argv) {
    int n = atoi(argv[1]);
    int m = 0;
    volatile int i = 0;
    int rootPID = 0;

    int childID = 0;
    int piNow = 0;
    int piReq = 0;

    int status = 0;

    pid_t ch_pid = 0;
    pid_t ppid, pid;

    if (argc != n + 2) {
        printf("KAZDY PROCES POTOMNY MUSI ZNAC SWOJA ILOSC ITERACJI");
        exit(EXIT_FAILURE);
    }

    printf("ID PARENTA: %d\n", getpid());

    recursiveFork(n, 0, argv, &piReq, &childID, &ch_pid);

    /* Każdy child musi czekać na swojego childa */
    /*if (ch_pid != 0) {
        while (m < n) {
            ch_pid = wait(&status);
            pid = getpid();
            printf("RAPORT Z PROCESU: %d\n", pid);
            printf("POTOMEK O IDENTYFIKATORZE %d ZAKONCZYL DZIALANIE\n", ch_pid);
            printf("STATUS ZAKONCZENIA PROCESU: %d\n", status);

            if (WIFEXITED(status) == 0) {
                printf("PROCES ZAKONCZYL SIE NIEPOPRAWNIE");
            }

            m++;
        }
        exit(EXIT_SUCCESS);
    }*/

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
