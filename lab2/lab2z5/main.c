#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/unistd.h>

int main() {
    pid_t childPid;
    int status;
    char command[100];
    char path[1000];

    while (1) {
        printf("COMMAND: ");
        scanf("%s", command);

        childPid = fork();

        if (childPid != 0) {
            childPid = wait(&status);

            if (strcmp(command, "exit") == 0) {
                exit(EXIT_SUCCESS);
            }

            if (WEXITSTATUS(status) != 0) {
                printf("KOMENDA NIEOBSLUGIWANA\n");
            }
        } else {
            if (access("C:/cygwin64/bin/", F_OK) == 0) {
                strcpy(path, "/cygwin64/bin/");
            } else {
                strcpy(path, "/bin/");
            }
            strcat(path, command);

            if (access(path, F_OK) == 0) {
                execl(path, command, NULL);
                exit(EXIT_SUCCESS);
            } else {
                exit(EXIT_FAILURE);
            }
        }
    }

    return EXIT_SUCCESS;
}
