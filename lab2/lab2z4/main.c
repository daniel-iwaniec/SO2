#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/unistd.h>

void recursiveFork(int argc, char** argv, int childID, int childN, int rootPID) {
    int n = atoi(argv[1]);

    int piNow = 0;
    int piReq = 0;

    int status = 0;

    pid_t ch_pid = 1;
    pid_t ppid, pid;

    if (argc != n + 2) {
        printf("KAZDY PROCES POTOMNY MUSI ZNAC SWOJA ILOSC ITERACJI");
        exit(EXIT_FAILURE);
    }

    piReq = atoi(argv[childID + 2]);
    ch_pid = fork();

    if (ch_pid == 0 && childID < childN - 1) {
        recursiveFork(argc, argv, childID + 1, childN, rootPID);
    }

    if (ch_pid != 0) {
        ch_pid = wait(&status);
        pid = getpid();
        printf("RAPORT Z PROCESU: %d\n", pid);
        printf("POTOMEK O IDENTYFIKATORZE %d ZAKONCZYL DZIALANIE\n", ch_pid);
        printf("STATUS ZAKONCZENIA PROCESU: %d\n", status);

        if (WIFEXITED(status) == 0) {
            printf("PROCES ZAKONCZYL SIE NIEPOPRAWNIE");
        }

        if (rootPID == getpid()) {
            exit(EXIT_SUCCESS);
        }
    } else {
        while (1) {
            sleep(1);

            ppid = getppid();
            pid = getpid();
            printf("C[%d, %d, %d]\tPPID: %d\tPID: %d\n", childID, piReq, piNow, ppid, pid);

            if (piNow >= piReq) {
                exit(EXIT_SUCCESS);
            }

            piNow++;
        }
    }
}

int main(int argc, char** argv) {
    recursiveFork(argc, argv, 0, atoi(argv[1]), getpid());
}
